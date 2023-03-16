/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:43:28 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/16 18:52:09 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*This function prints a message inside a thread and uses mutex
so the printing is synched apropiately*/
void	print_mute(char *str, t_phil *phil)
{
	pthread_mutex_lock(&phil->dead_time->mutex_print);
	printf("%lu %i %s\n", get_mil_time(phil->start), \
	phil->phil_id, str);
	pthread_mutex_unlock(&phil->dead_time->mutex_print);
}

/*This is the main function for the philosophers to be running*/
void	*phil_do(void *philo)
{
	t_phil			*phil;
	unsigned long	ate;

	phil = philo;
	ate = 3;
	pthread_mutex_lock(&phil->fork->mutex);
	while (!check_floor(phil->dead_time))
	{
		phil->action(phil);
		if ((ate / 3) == phil->dead_time->max_eat && (ate % 3) == 0)
			phil_ate(phil, ate);
		ate++;
	}
	free(phil);
	return (NULL);
}

/*This function initiates the threads and mutexes used in them*/
int	start_phils(t_table *table)
{
	t_fork	*temp;
	int		i;

	temp = table->fork;
	i = 0;
	pthread_mutex_init(&table->dead_time->mutex_ate, NULL);
	pthread_mutex_init(&table->dead_time->mutex_print, NULL);
	pthread_mutex_init(&table->dead_time->mutex_dead, NULL);
	gettimeofday(&table->start, NULL);
	sit_phils(table);
	while (i < table->dead_time->nr_phil)
	{
		if (pthread_create(&((table->philo)[i]), NULL, \
		&phil_do, table->phils[i]) != 0)
			return (0);
		temp = temp->next;
		i++;
		usleep(100);
	}
	i = death_bringer(table);
	return (i);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = threading(argc, argv);
	if (!table)
		return (1);
	if (table->dead_time->max_eat == 0)
		return (0);
	i = start_phils(table);
	if (!i)
		return (1);
	i = 0;
	while (i < table->dead_time->nr_phil)
	{
		pthread_join((table->philo)[i], NULL);
		i++;
	}
	if (table->dead_time->someone_dead)
	{
		free_table(table);
		return (1);
	}
	free_table(table);
	return (0);
}
