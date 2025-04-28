# include "philo.h"

void    wait_philo(t_table *table)
{
    while (!get_bool(&table->table_mtx, &table->thread_ready))
        ;
    
}