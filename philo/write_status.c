/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:52:52 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/03 15:45:14 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (simulation_finish(philo->table))
		return ;
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !simulation_finish(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finish(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finish(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finish(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	safe_mtx(&philo->table->write_mtx, LOCK);
	if (debug)
		write_status_debug(status, philo,
			gettime(MILLISECOND) - philo->table->start);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finish(philo->table))
			printf(M "%-6ld" C "%d has taken a fork\n" RST,
				gettime(MILLISECOND) - philo->table->start, philo->id);
		else if (EATING == status && !simulation_finish(philo->table))
			printf(M "%-6ld" G "%d is eating\n" RST,
				gettime(MILLISECOND) - philo->table->start, philo->id);
		else if (SLEEPING == status && !simulation_finish(philo->table))
			printf(M "%-6ld" B "%d is sleeping\n" RST,
				gettime(MILLISECOND) - philo->table->start, philo->id);
		else if (THINKING == status && !simulation_finish(philo->table))
			printf(M "%-6ld" Y "%d is thinking\n" RST,
				gettime(MILLISECOND) - philo->table->start, philo->id);
		else if (DIED == status)
			printf(M "%-6ld" RED "%d died\n" RST,
				gettime(MILLISECOND) - philo->table->start, philo->id);
	}
	safe_mtx(&philo->table->write_mtx, UNLOCK);
}
