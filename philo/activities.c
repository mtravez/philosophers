/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:37:45 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/05 14:30:02 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *phil)
{
	phil->fork->in_use = 1;
	phil->fork->next->in_use = 1;
	printf("%lu %i has taken a fork\n", get_mil_time(phil->start), phil->phil_id);
	gettimeofday(&(phil->last_ate), NULL);
	printf("%lu %i is eating\n", get_mil_time(phil->start), phil->phil_id);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_eat);
	phil->fork->in_use = 0;
	phil->fork->next->in_use = 0;
}

int	sleep_phil(t_phil *phil)
{
	printf("%lu %i is sleeping\n", get_mil_time(phil->start), phil->phil_id);
	gettimeofday(&(phil->last_ate), NULL);
	while (get_mil_time(phil->last_ate) < phil->dead_time->time_sleep)
	{
		if (get_mil_time(phil->last_ate) >= phil->dead_time->time_starve)
		{
			printf("%lu %i died\n", get_mil_time(phil->start), phil->phil_id);
			return (0) ;
		}
	}
	return (1);
}