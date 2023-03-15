/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:31:43 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/14 19:47:56 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*This function initializes a table structure with the parameters
fork and dead*/
t_table	*set_table(t_fork *fork, t_dead_time *dead)
{
	t_table		*table;

	table = malloc (sizeof(fork) + sizeof(dead) + sizeof(t_table *) \
	+ sizeof(struct timeval) + sizeof(t_phil *) * dead->nr_phil);
	if (!table)
		return (NULL);
	table->phils = malloc(sizeof(t_phil *) * dead->nr_phil);
	table->philo = malloc(sizeof(pthread_t *) * dead->nr_phil);
	if (!table->philo || !table->phils)
		return (NULL);
	table->dead_time = dead;
	table->fork = fork;
	gettimeofday(&(table->start), NULL);
	return (table);
}

void	sit_phils(t_table	*table)
{
	int		i;
	t_fork	*temp;

	i = 0;
	temp = table->fork;
	while (i < table->dead_time->nr_phil)
	{
		table->phils[i] = init_phil(temp, table->start, table->dead_time);
		i++;
		temp = temp->next;
	}
}

int	check_floor(t_dead_time *dead)
{
	pthread_mutex_lock(&dead->mutex_ate);
	if (dead->finished_eating || dead->someone_dead)
	{
		pthread_mutex_unlock(&dead->mutex_ate);
		return (1);
	}
	pthread_mutex_unlock(&dead->mutex_ate);
	return (0);
}

/*This function initializes the fork, common dead_time and table
with the input of the user*/
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
