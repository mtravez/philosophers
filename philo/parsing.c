/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:31:43 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/22 16:56:43 by mtravez          ###   ########.fr       */
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
	if (!table->phils)
	{
		free(table);
		return (NULL);
	}
	table->philo = malloc(sizeof(pthread_t *) * dead->nr_phil);
	if (!table->philo)
	{
		free(table->phils);
		free(table);
		return (NULL);
	}
	table->dead_time = dead;
	table->fork = fork;
	gettimeofday(&(table->start), NULL);
	return (table);
}

/*This function initializes the philosophers inside the table.*/
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
	{
		free_dead(dead);
		return (NULL);
	}
	table = set_table(fork, dead);
	if (!table)
	{
		free_forks(fork, dead->nr_phil);
		free_dead(dead);
	}
	return (table);
}
