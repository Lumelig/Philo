/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:52:52 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/06 20:49:51 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_philo_status(char *msg, t_philo *philo)
{
	long	time;

	time = time_now() - philo->table->start;
	pthread_mutex_lock(&philo->table->table_mtx);
	if (!philo->table->ende_program)
		printf(M "%-6ld" C "%d %s\n" RST, time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->table_mtx);
}
