/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:36:41 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/18 20:36:09 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*This function destroys every mutex in a dead_time and
then frees the dead_time.*/
void	free_dead(t_dead_time *dead)
{
	pthread_mutex_destroy(&dead->mutex_ate);
	pthread_mutex_destroy(&dead->mutex_print);
	pthread_mutex_destroy(&dead->mutex_dead);
	free(dead);
}

/*This function destroys every mutex in every fork
connected to by fork and frees them.*/
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

/*This function frees the table from forks, deadtime, threads and
philososphers*/
void	free_table(t_table *table)
{
	free_forks(table->fork, table->dead_time->nr_phil);
	free_dead(table->dead_time);
	free(table->phils);
	free(table->philo);
	free(table);
}
