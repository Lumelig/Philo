/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:34:16 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/07 19:46:07 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapse;
	long	t_to_die;
	long	last_meal_time;
	bool	is_full;

	pthread_mutex_lock(&philo->philo_mtx);
	is_full = philo->full;
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->philo_mtx);
	if (is_full)
		return (false);
	elapse = time_now() - last_meal_time;
	t_to_die = philo->table->time_to_die;
	if (elapse > t_to_die)
	{
		return (true);
	}
	return (false);
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
				printf(M "%-6ld" RED "%d died\n" RST, (time_now()
						- table->start), (table->philo)[i].id);
			}
		}
	}
	return (NULL);
}
