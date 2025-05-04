/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:34:16 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/04 13:39:14 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
    long elapse;
    long t_to_die;
    long last_meal_time;
    
    if (get_bool(&philo->philo_mtx, &philo->full))
        return false;
    last_meal_time = get_long(&philo->philo_mtx, &philo->last_meal);
    elapse = gettime(MILLISECOND) - last_meal_time;
    t_to_die = philo->table->time_to_die;
    if (DEBUG_MODE && elapse > t_to_die - 10)
        printf("Philosopher %d: time since last meal: %ld ms (limit: %ld ms)\n", 
               philo->id, elapse, t_to_die);
    
    return (elapse > t_to_die);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mtx, &table->threads_running_nbr,
			table->philosophers))
		;
	while (!simulation_finish(table))
	{
		i = -1;
		while (++i < table->philosophers)
		{
			if (philo_died(table->philo + i) && !simulation_finish(table))
			{
				set_bool(&table->table_mtx, &table->ende_program, true);
				write_status(DIED, table->philo + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
