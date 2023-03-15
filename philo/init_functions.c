/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:59:57 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/14 15:59:40 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*This function initiates a new fork structure and returns it if the
memory allocation did not fail*/
t_fork	*new_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork *) * 2 + sizeof(pthread_mutex_t));
	if (!fork)
		return (NULL);
	pthread_mutex_init(&(fork->mutex), NULL);
	fork->next = NULL;
	return (fork);
}

/*This function initiates as many forks as the given parameter says.
It then will link them to each other so the first fork is connected to the last
and then returns the address to the first fork*/
t_fork	*set_forks(int nr)
{
	t_fork	*fork;
	t_fork	*temp;
	int		i;

	fork = new_fork();
	if (!fork)
		return (NULL);
	temp = fork;
	i = 1;
	fork->nr = i;
	while (++i <= nr)
	{
		temp->next = new_fork();
		temp = temp->next;
		if (!temp)
			return (NULL);
		temp->nr = i;
	}
	temp->next = fork;
	return (fork);
}

/*This function initiates a new phil structure and returns it if the
memory allocation did not fail
@param fork the fork assigned to this phil
@param start the imeval structure containing the time at which the
program started
@param dead_time the common values needed to run the program
stored ina structure*/
t_phil	*init_phil(t_fork *fork, struct timeval start, t_dead_time *dead_time)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil *) + sizeof(dead_time) + \
	(sizeof(struct timeval) * 2) + sizeof(fork) + sizeof(t_philo_action));
	if (!phil)
		return (NULL);
	phil->fork = fork;
	phil->start = start;
	gettimeofday(&phil->last_ate, NULL);
	phil->dead_time = dead_time;
	phil->phil_id = fork->nr;
	phil->action = &eat;
	return (phil);
}

/*This function checks every character in a string array and returns false
if there is a non-digit character*/
int	check_valid(char **argv)
{
	int	i;
	int	j;

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

/*This function initiates the dead_time structure from a string array and
parses the strings to long integers and initialize the necessary variables.*/
t_dead_time	*init_death(int argc, char **argv)
{
	t_dead_time	*death;

	if (!check_valid(argv))
		return (NULL);
	death = malloc(sizeof(t_dead_time *) + (sizeof(unsigned long) * 3) \
	+ sizeof(pthread_mutex_t) * 3 + sizeof(int) * 5);
	if (!death)
		return (NULL);
	death->nr_phil = ft_atoi(argv[1]);
	death->time_starve = ft_atoi(argv[2]);
	death->time_eat = ft_atoi(argv[3]);
	death->time_sleep = ft_atoi(argv[4]);
	death->phil_ate_max = 0;
	death->max_eat = -1;
	death->someone_dead = 0;
	death->finished_eating = 0;
	if (argc == 6)
		death->max_eat = ft_atoi(argv[5]);
	return (death);
}
