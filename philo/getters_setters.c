/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:32:07 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/01 12:32:09 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_mtx(mtx, LOCK);
	*dest = value;
	safe_mtx(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mtx(mtx, LOCK);
	ret = *value;
	safe_mtx(mtx, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mtx(mtx, LOCK);
	ret = *value;
	safe_mtx(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	safe_mtx(mtx, LOCK);
	*dest = value;
	safe_mtx(mtx, UNLOCK);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->ende_program));
}
