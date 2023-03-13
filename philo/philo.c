/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:43:28 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/13 20:35:32 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_mute(char *str, t_phil *phil)
{
	pthread_mutex_lock(&phil->dead_time->mutex_print);
	printf("%lu %i %s\n", get_mil_time(phil->start), \
	phil->phil_id, str);
	pthread_mutex_unlock(&phil->dead_time->mutex_print);
}

void	*phil_do(void *philo)
{
	t_phil	*phil;
	int		ate;

	phil = philo;
	ate = 3;
	pthread_mutex_lock(&phil->fork->mutex);
	pthread_mutex_lock(&phil->dead_time->mutex_ate);
	while (!phil->dead_time->someone_dead && !phil->dead_time->finished_eating)
	{
		pthread_mutex_unlock(&phil->dead_time->mutex_ate);
		phil->action(phil);
		if ((ate / 3) == phil->dead_time->max_eat && (ate % 3) == 0)
			phil_ate(phil, ate);
		ate++;
		pthread_mutex_lock(&phil->dead_time->mutex_ate);
	}
	pthread_mutex_unlock(&phil->dead_time->mutex_ate);
	free(phil);
	return (NULL);
}

int	sit_phils(t_table *table)
{
	t_fork	*temp;
	int		i;

	temp = table->fork;
	i = 0;
	pthread_mutex_init(&table->dead_time->mutex_ate, NULL);
	pthread_mutex_init(&table->dead_time->mutex_print, NULL);
	pthread_mutex_init(&table->dead_time->mutex_dead, NULL);
	gettimeofday(&table->start, NULL);
	while (i < table->dead_time->nr_phil)
	{
		if (pthread_create(&((table->philo)[i]), NULL, \
		&phil_do, init_phil(temp, table->start, table->dead_time)) != 0)
			return (0);
		temp = temp->next;
		i++;
		usleep(100);
	}
	return (i);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = threading(argc, argv);
	if (!table)
		return (1);
	i = sit_phils(table);
	if (!i)
		return (0);
	i = 0;
	while (i < table->dead_time->nr_phil)
	{
		pthread_join((table->philo)[i], NULL);
		i++;
	}
	system("leaks philo");
	return (0);
}
