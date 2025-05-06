/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:32:07 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/06 17:18:33 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->ende_program));
}
