/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:02:01 by mtravez           #+#    #+#             */
/*   Updated: 2023/03/16 18:56:07 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_phil	t_phil;
typedef void			(*t_philo_action) (t_phil *phil);

/*
@param nr the identifying number for this fork
@param next the fork set next to this one*/
typedef struct s_fork
{
	int				nr;
	pthread_mutex_t	mutex;
	struct s_fork	*next;
}	t_fork;

/*
@param mutex_ate the mutex to modify the max_ate and the finished_eating values
@param mutex_print the mutex to print something to the output
@param mutex_dead the mutex to modify the someone_dead value
@param somone_dead whether a philosopher has died
@param finished_eating whether all philosophers have eaten the
minimum required amount of times
@param max_eat how many times each philosopher has to eat for the program to end
@param nr_phil how many philosophers there are at the table
@param phil_ate_max how many philosophers hae eaten the required amount of times
@param time_eat the time in milliseconds it takes for a philosopher to eat
@param time_sleep the time it takes a philosopher to sleep
@param time_starve the time it takes a philosopher to starve to death*/
typedef struct s_dead_time
{
	pthread_mutex_t	mutex_ate;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	int				someone_dead;
	int				finished_eating;
	int				max_eat;
	int				nr_phil;
	int				phil_ate_max;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	time_starve;
}	t_dead_time;

/*
@param fork the fork to the left of the philosopher
@param start the time at which the program first started
@param last_ate the time at which the philosopher last ate
@param dead_time the structure holding all the important details
for every philosopher
@param phil_id the identifying number of the philosopher
@param action the address of the function the philosopher should do next
*/
typedef struct s_phil
{
	t_fork			*fork;
	struct timeval	start;
	struct timeval	last_ate;
	t_dead_time		*dead_time;
	int				phil_id;
	t_philo_action	action;
}	t_phil;

/*
@param fork the forks that are on the table
@param dead_time the structure holding all the values intended for 
common use between the philosophers
@parma start the time at which the program first started
@param philo the array of threads for the philosophers
*/
typedef struct s_table
{
	t_fork			*fork;
	t_dead_time		*dead_time;
	struct timeval	start;
	pthread_t		*philo;
	t_phil			**phils;
}	t_table;

unsigned long	get_mil_time(struct timeval start);
t_fork			*set_forks(int nr);
t_phil			*init_phil(t_fork *fork, struct timeval start, \
t_dead_time *dead_time);
t_dead_time		*init_death(int argc, char **argv);
void			eat(t_phil *phil);
void			sleep_phil(t_phil *phil);
void			phil_ate(t_phil *phil, int ate);
int				check_hunger(t_phil *phil);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
t_table			*threading(int argc, char **argv);
void			print_mute(char *str, t_phil *phil);
void			think(t_phil *phil);
void			free_dead(t_dead_time *dead);
void			free_forks(t_fork *fork, int nr);
void			free_table(t_table *table);
void			sit_phils(t_table	*table);
int				check_floor(t_dead_time *dead);
int				death_bringer(t_table *table);

#endif