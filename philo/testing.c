/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:57:42 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/03 19:42:52 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


t_fork	*init_forks(void)
{
	t_fork *fork;
	t_fork *new_fork;

	fork = malloc(sizeof(t_fork *) * 2);
	new_fork = malloc(sizeof(t_fork *) * 2);
	if (!fork || ! new_fork)
		return (NULL);
	fork->in_use = 0;
	fork->nr = 1;
	new_fork->in_use = 1;
	new_fork->nr = 2;
	fork->next = new_fork;
	new_fork->next = fork;
	return (fork);
}

void	*test(void *input_fork)
{
	t_fork *fork;
	pthread_mutex_t mutex;
	struct timeval start;
	struct timeval waiting;
	unsigned long time;
	
	fork = input_fork;
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&start, NULL);
	time = 0;
	gettimeofday(&waiting, NULL);
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (!fork->next->in_use)
		{
			time += get_mil_time(waiting);
			printf("have been waiting for fork %i for %lu ms\n", fork->nr, time);
			fork->in_use = 1;
			printf("fork %i used at %lu ms\n", fork->nr, get_mil_time(start));
			time = 0;
			gettimeofday(&waiting, NULL);
			while (get_mil_time(waiting) < 10000);
			fork->in_use = 0;
			time = 0;
			gettimeofday(&waiting, NULL);
			while (time < 1000)
				time = get_mil_time(waiting);
		}
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(void)
{
	t_fork *fork;
	pthread_t hi;
	pthread_t bye;
	
	fork = init_forks();
	if (pthread_create(&hi, NULL, &test, fork))
	{
		printf("couldn't create thread 1\n");
		exit(1);
	}
	if (pthread_create(&bye, NULL, &test,fork->next))
	{
		printf("couldn't create thread 2\n");
		exit(1);
	}
	pthread_join(hi, NULL);
	pthread_join(bye, NULL);
	return (0);
}