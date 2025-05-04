/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:28:40 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/04 13:46:07 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thinking(t_philo *philo, bool pre_sim)
{
    long time_since_meal;
    long think_time;
    
    write_status(THINKING, philo, DEBUG_MODE);
    
    // Don't adjust if it's pre-simulation
    if (pre_sim)
        return;
        
    // Calculate how long since last meal
    time_since_meal = gettime(MILLISECOND) - 
                     get_long(&philo->philo_mtx, &philo->last_meal);
    
    // The hungrier a philosopher is, the less they think
    // This gives hungry philosophers priority
    think_time = philo->table->time_to_die / 4 - time_since_meal / 4;
    
    // Ensure think_time is reasonable
    if (think_time > 0 && think_time < philo->table->time_to_die / 2)
        my_usleep(think_time * 1000, philo->table);  // Convert to microseconds
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finish(philo->table))
	{
		usleep(200);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
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

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->table_mtx);
	pthread_mutex_unlock(&philo->table->table_mtx);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_nbr);
	de_sync_philo(philo);
	while (!simulation_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		my_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void start_procces(t_table *table)
{
    int i;

    i = -1;
    if (0 == table->meals_limit)
        return;
    pthread_mutex_lock(&table->table_mtx);
    if (1 == table->philosophers)
        safe_thread(&table->philo[0].thread_id, one_philo, &table->philo[0], CREATE);
    else
    {
        while (++i < table->philosophers)
            safe_thread(&table->philo[i].thread_id, dinner_simulation,
                &table->philo[i], CREATE);
    }
    
    safe_thread(&table->monitor, monitor_dinner, table, CREATE);
    table->start = gettime(MILLISECOND);
    pthread_mutex_unlock(&table->table_mtx);
    i = -1;
    while (++i < table->philosophers)
        safe_thread(&table->philo[i].thread_id, NULL, NULL, JOIN);
    set_bool(&table->table_mtx, &table->ende_program, true);
    safe_thread(&table->monitor, NULL, NULL, JOIN);
}
