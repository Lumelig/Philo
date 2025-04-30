# include "philo.h"

void    wait_philo(t_table *table)
{
    while (!get_bool(&table->table_mtx, &table->thread_ready))
        ;
    
}

bool    all_threads_running(t_mtx *mtx, long *threads, long philos)
{
    bool    ret;

    ret = false;
    safe_mtx(mtx, LOCK);
    if (*threads == philos)
        ret = true;
    safe_mtx(mtx, UNLOCK);
    return (ret);
}

void    increase_long(t_mtx *mtx, long *value)
{
    safe_mtx(mtx, LOCK);
    (*value)++;
    safe_mtx(mtx, UNLOCK);
}

void de_sync_philo(t_philo *philo)
{
    if(philo->table->philosophers % 2 == 0)
    {
        if (philo->id % 2 == 0)
            my_usleep(3e4, philo->table);
    }
    else
    {
        if (philo->id % 2)
            thinking(philo, true);
    }
}