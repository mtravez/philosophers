/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:43:28 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/05 14:27:19 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*phil_do(void *philo)
{
	pthread_mutex_t	mutex;
	t_phil			*phil;
	int				ate;

	phil = philo;
	ate = 0;
	pthread_mutex_init(&mutex, NULL);
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (!phil->fork->in_use && !phil->fork->next->in_use)
		{
			eat(phil);
			phil_ate(phil, ++ate);
			if (!sleep_phil(phil))
				exit(1);
			printf("%lu %i is thinking\n", get_mil_time(phil->start), phil->phil_id);
		}
		if (get_mil_time(phil->last_ate) > phil->dead_time->time_starve)
		{
			printf("%lu %i died\n", get_mil_time(phil->start), phil->phil_id);
			break ;
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_destroy(&mutex);
	exit(1);
	return (NULL);
}

t_dead_time	*set_death(void)
{
	t_dead_time	*dead;
	
	dead = malloc(sizeof(t_dead_time *) + (sizeof(unsigned long) * 3) + sizeof(int) * 3);
	if (!dead)
		return (NULL);
	dead->max_eat = 4;
	dead->nr_phil = 5;
	dead->phil_ate_max = 0;
	dead->time_eat = 150;
	dead->time_sleep = 100;
	dead->time_starve = 500;
	return (dead);
}


int	main(int argc, char **argv)
{
	struct timeval	start_time;
	// pthread_mutex_t	*mutex_test;
	pthread_t		philos[5];
	t_fork			*fork;
	t_fork			*temp;
	t_dead_time		*dead;
	int				i;
	// long int		time;
	
	gettimeofday(&start_time, NULL);
	dead = set_death();
	fork = set_forks(dead->nr_phil);
	temp = fork;
	i = 0;
	while (i < dead->nr_phil)
	{
		pthread_create(&(philos[i]), NULL, &phil_do, init_phil(temp, start_time, dead));
		temp = temp->next;
		i++;
	}
	i = 0;
	while (i < dead->nr_phil)
	{
		pthread_join(philos[i], NULL);
		i++;;
	}
	
	// while (i < dead->nr_phil)
	// {
	// 	printf("fork %i\n", temp->nr);
	// 	temp = temp->next;
	// 	i++;
	// }
	
	
	// while (time < 1000)
	// 	time = get_mil_time(start_time);
	// printf("took %lu ms\n", get_mil_time(start_time));
	
	return (0);
}
