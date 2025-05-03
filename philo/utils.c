/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:21:58 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/03 15:09:44 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remain;

	(void)table;
	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		elapsed = gettime(MICROSECOND);
		remain = usec - elapsed;
		if (remain > 1e3)
			usleep(remain / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_and_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_and_exit("Wrong input to gettime");
	return (0);
}

void	error_and_exit(const char *error)
{
	printf(RED "%s\n" RST, error);
	exit(EXIT_FAILURE);
}

void	clean_all(t_table *tabel)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < tabel->philosophers)
	{
		philo = tabel->philo + i;
		safe_mtx(&philo->philo_mtx, DESTROY);
	}
	i = -1;
	safe_mtx(&tabel->table_mtx, DESTROY);
	safe_mtx(&tabel->write_mtx, DESTROY);
	free(tabel->forks);
	free(tabel->philo);
}
