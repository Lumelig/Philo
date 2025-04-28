# include "philo.h"

static void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);

}

static void eat(t_philo *philo)
{
    safe_mtx(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mtx(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
    philo->meals++;
    write_status(EATING, philo, DEBUG_MODE);
    my_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->meals_limit > 0
        && philo->meals == philo->table->meals_limit)
        set_bool(&philo->philo_mtx, &philo->full, true);

    safe_mtx(&philo->first_fork->fork, UNLOCK);
    safe_mtx(&philo->second_fork->fork, UNLOCK);
}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    while (!simulation_finish(philo->table))
    {
        if (philo->full)
            break;
        eat(philo);
        write_status(SLEEPING, philo, DEBUG_MODE);
        my_usleep(philo->table->time_to_sleep, philo->table);
    }   
    
    wait_philo(philo->table);
    return (NULL);
}

void start_procces(t_table *table)
{
    int i;

    i = -1;
    if (0 == table->meals_limit)
        return;
    else if (1 == table->philosophers)
        ;//to do
    else
        while (++i < table->philosophers)
        {
            safe_thread(&table->philo[i].thread_id, dinner_simulation, &table->philo[i], CREATE);
        }
    table->start = gettime(MILLISECOND);
    set_bool(&table->table_mtx, &table->thread_ready, true);
    i = -1;
    while (++i < table->philosophers)
        safe_thread(&table->philo[i].thread_id, NULL, NULL, JOIN);
    
    }
