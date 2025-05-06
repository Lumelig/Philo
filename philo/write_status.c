/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:52:52 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/06 17:12:48 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_philo_status(char *msg, t_philo *philo)
{
	if (!simulation_finish(philo->table))
	{
		safe_mtx(&philo->table->write_mtx, LOCK);
		printf(M "%-6ld" C "%d %s\n" RST, gettime(MILLISECOND)
			- philo->table->start, philo->id, msg);
		safe_mtx(&philo->table->write_mtx, UNLOCK);
	}
}
