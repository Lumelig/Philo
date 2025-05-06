/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:52:52 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/06 17:53:47 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_philo_status(char *msg, t_philo *philo)
{
	long	time;

	if (simulation_finish(philo->table))
		return ;
	time = gettime(MILLISECOND) - philo->table->start;
	pthread_mutex_lock(&philo->table->write_mtx);
	printf(M "%-6ld" C "%d %s\n" RST, time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
