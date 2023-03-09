/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:43:28 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/09 15:40:06 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_forks(t_phil *phil)
{
	return (!phil->fork->in_use && !phil->fork->next->in_use);
}

void	*phil_do(void *philo)
{
	t_phil			*phil;
	// pthread_mutex_t	mute;
	int				ate;

	phil = philo;
	ate = 0;
	// pthread_mutex_init(&mute, NULL);
	while (1)
	{
		// if (check_forks(phil))
		// {
		pthread_mutex_lock(&phil->fork->mutex);
		pthread_mutex_lock(&(phil->fork->next->mutex));
			eat(phil);
		pthread_mutex_unlock(&phil->fork->next->mutex);
		pthread_mutex_unlock(&phil->fork->mutex);
			// printf("phil %i finished eating\n", phil->phil_id);
			if (++ate == phil->dead_time->max_eat)
			{
				if (phil_ate(phil, ate))
					break ;
			}
			// printf("phil %i is going to sleep\n", phil->phil_id);
			if (!sleep_phil(phil))
				break ;
			printf("%lu %i is thinking\n", get_mil_time(phil->start), \
			phil->phil_id);
		// }
		check_hunger(phil);
	}
	pthread_mutex_destroy(&(phil->fork->mutex));
	exit(1);
	return (NULL);
}
// t_dead_time	*set_death(void)
// {
// 	t_dead_time	*dead;

// 	dead = malloc(sizeof(t_dead_time *) + (sizeof(unsigned long) * 3) \
// 	+ sizeof(int) * 3);
// 	if (!dead)
// 		return (NULL);
// 	dead->max_eat = 0;
// 	dead->nr_phil = 5;
// 	dead->phil_ate_max = 0;
// 	dead->time_eat = 200;
// 	dead->time_sleep = 200;
// 	dead->time_starve = 500;
// 	return (dead);
// }

/*NEED TO FIX: can't use exit() in this proyect*/
int	main(int argc, char **argv)
{
	t_table	*table;
	t_fork	*temp;
	int		i;

	table = threading(argc, argv);
	if (!table)
		return (1);
	temp = table->fork;
	i = 0;
	pthread_mutex_init(&table->dead_time->mutex_ate, NULL);
	while (i < table->dead_time->nr_phil)
	{
		pthread_create(&((table->philo)[i]), NULL, &phil_do, init_phil(temp, table->start, table->dead_time));
		temp = temp->next;
		i++;
	}
	i = 0;
	while (i < table->dead_time->nr_phil)
	{
		pthread_join((table->philo)[i], NULL);
		i++;
	}
	return (0);
}
