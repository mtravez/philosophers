/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:02:01 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/04 17:16:20 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

/*
@param nr the identifying number for this fork
@param in_use whether oor not this fork is in use
@param next the fork set next to this one*/
typedef struct	s_fork
{
	int				nr;
	int				in_use;
	struct s_fork	*next;
}	t_fork;

typedef struct	s_dead_time
{
	int				max_eat;
	int				nr_phil;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	time_starve;
}	t_dead_time;

typedef struct	s_phil
{
	t_fork			*fork;
	struct timeval	start;
	struct timeval	last_ate;
	t_dead_time		*dead_time;
	int				phil_id;
}	t_phil;

long int	get_mil_time(struct timeval start);
t_fork	*set_forks(int nr);
t_phil	*init_phil(t_fork *fork, struct timeval start, t_dead_time *dead_time);

#endif