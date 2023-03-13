/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:59:57 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/13 20:07:00 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*new_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork *) * 2 + sizeof(pthread_mutex_t));
	if (!fork)
		return (NULL);
	fork->in_use = 0;
	pthread_mutex_init(&(fork->mutex), NULL);
	fork->next = NULL;
	return (fork);
}

t_fork	*set_forks(int nr)
{
	t_fork	*fork;
	t_fork	*temp;
	int		i;

	fork = new_fork();
	if (!fork)
	{
		return (NULL);
	}
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

	phil = malloc(sizeof(t_phil *) + sizeof(dead_time) + \
	(sizeof(struct timeval) * 2) + sizeof(fork));
	if (!phil)
	{
		return (NULL);
	}
	phil->fork = fork;
	phil->start = start;
	gettimeofday(&phil->last_ate, NULL);
	phil->dead_time = dead_time;
	phil->phil_id = fork->nr;
	phil->action = &eat;
	return (phil);
}

int	check_valid(char **argv)
{
	int			i;
	int			j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]))
				return (0);
	}
	return (1);
}

t_dead_time	*init_death(int argc, char **argv)
{
	t_dead_time	*death;

	if (!check_valid(argv))
		return (NULL);
	death = malloc(sizeof(t_dead_time *) + (sizeof(unsigned long) * 3) \
	+ sizeof(int) * 5 + sizeof(pthread_mutex_t) * 3);
	if (!death)
		return (NULL);
	death->nr_phil = ft_atoi(argv[1]);
	death->time_starve = ft_atoi(argv[2]);
	death->time_eat = ft_atoi(argv[3]);
	death->time_sleep = ft_atoi(argv[4]);
	death->phil_ate_max = 0;
	death->max_eat = 0;
	death->someone_dead = 0;
	death->finished_eating = 0;
	if (argc == 6)
		death->max_eat = ft_atoi(argv[5]);
	return (death);
}
