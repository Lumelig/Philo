/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:36:56 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/07 19:50:47 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philo(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->thread_ready))
		;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philos)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mtx);
	if (*threads == philos)
		ret = true;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	increase_long(t_mtx *mtx, long *value)
{
	pthread_mutex_lock(mtx);
	(*value)++;
	pthread_mutex_unlock(mtx);
}

void	de_sync_philo(t_philo *philo)
{
	if (!philo->id % 2 == 0)
		write_philo_status(G"is thinking", philo);
	else
	{
		write_philo_status(G"is thinking", philo);
		ft_usleep(philo->table->time_to_eat / 2);
	}
}
