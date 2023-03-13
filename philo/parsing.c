/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:31:43 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/13 19:21:43 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*malloc_table(t_fork *fork, t_dead_time *dead)
{
	t_table		*table;

	table = malloc (sizeof(fork) + sizeof(dead) + sizeof(t_table *) \
	+ sizeof(struct timeval));
	if (!table)
		return (NULL);
	return (table);
}

t_table	*set_table(t_fork *fork, t_dead_time *dead)
{
	t_table		*table;

	table = malloc_table(fork, dead);
	if (!table)
		return (NULL);
	table->philo = malloc(sizeof(pthread_t *) * dead->nr_phil);
	if (!table->philo)
		return (NULL);
	table->dead_time = dead;
	table->fork = fork;
	gettimeofday(&(table->start), NULL);
	return (table);
}

t_table	*threading(int argc, char **argv)
{
	t_dead_time	*dead;
	t_fork		*fork;
	t_table		*table;

	if (argc < 5 || argc > 6)
		return (NULL);
	dead = init_death(argc, argv);
	if (!dead)
		return (NULL);
	fork = set_forks(dead->nr_phil);
	if (!fork)
		return (NULL);
	table = set_table(fork, dead);
	return (table);
}
