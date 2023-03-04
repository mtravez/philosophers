/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:59:57 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/04 17:05:50 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*new_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork *) * 2);
	if (!fork)
		return (NULL);
	fork->in_use = 0;
	fork->next = NULL;
	return (fork);
}

t_fork	*set_forks(int nr)
{
	t_fork	*fork;
	t_fork	*temp;
	int		i;

	fork = new_fork();
	temp = fork;
	i = 1;
	fork->nr = i;
	while (++i <= nr)
	{
		temp->next = new_fork();
		temp = temp->next;
		temp->nr = i;
	}
	temp->next = fork;
	return (fork);
}

t_phil	*init_phil(t_fork *fork, struct timeval start, t_dead_time *dead_time)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil *) + sizeof(dead_time) + (sizeof(struct timeval) * 2) + sizeof(fork));
	if (!phil)
	{
		return (NULL);
	}
	phil->fork = fork;
	phil->start = start;
	phil->last_ate = start;
	phil->dead_time = dead_time;
	phil->phil_id = fork->nr;
	return (phil);
}