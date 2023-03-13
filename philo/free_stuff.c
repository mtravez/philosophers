/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:36:41 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/13 20:33:39 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_dead(t_dead_time *dead)
{
	pthread_mutex_destroy(&dead->mutex_ate);
	pthread_mutex_destroy(&dead->mutex_print);
	pthread_mutex_destroy(&dead->mutex_dead);
	free(dead);
}

void	free_forks(t_fork *fork, int nr)
{
	int		i;
	t_fork	*temp;

	i = 0;
	temp = fork;
	while (i < nr)
	{
		fork = temp->next;
		pthread_mutex_destroy(&temp->mutex);
		free(temp);
		temp = fork;
		i++;
	}
}

void	free_phil(t_phil *phil)
{
	free(phil);
}

void	free_table(t_table *table)
{
	free(table->philo);
	free(table);
}
