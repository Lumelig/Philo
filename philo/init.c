/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:32:20 by jpflegha          #+#    #+#             */
/*   Updated: 2025/05/14 17:24:11 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;
	int	left_fork;
	int	right_fork;

	philo_nbr = philo->table->philosophers;
	left_fork = position;
	right_fork = (position + 1) % philo_nbr;
	if (position % 2 == 0)
	{
		philo->first_fork = &forks[left_fork];
		philo->second_fork = &forks[right_fork];
	}
	else
	{
		philo->first_fork = &forks[right_fork];
		philo->second_fork = &forks[left_fork];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philosophers)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		safe_mtx(&philo->philo_mtx, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->ende_program = false;
	table->thread_ready = false;
	table->threads_running_nbr = 0;
	safe_mtx(&table->table_mtx, INIT);
	table->philo = safe_malloc(sizeof(t_philo) * table->philosophers);
	table->forks = safe_malloc(sizeof(t_fork) * table->philosophers);
	while (++i < table->philosophers)
	{
		safe_mtx(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
