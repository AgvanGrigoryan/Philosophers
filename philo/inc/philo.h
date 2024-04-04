/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/04 19:06:12 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// type bool
# include <stdbool.h>

// limtis
# include <limits.h>

// memset
# include <string.h>

// printf
# include <stdio.h>

// write, usleep
# include <unistd.h>

// malloc, free  
# include <stdlib.h>

// gettimeofday
# include <sys/time.h>

// pthread_create, pthread_detach, pthread_join,
// pthread_mutex_init, pthread_mutex_destroy,
// pthread_mutex_lock, pthread_mutex_unlock
# include <pthread.h>

struct					s_vars;
typedef struct timeval	t_timeval;
typedef void *			t_philo_handler;
typedef pthread_mutex_t	t_fork_mutex;

// DEFINITIONS
typedef struct s_philo
{
	int				id;//
	pthread_t		tid;

	long long		last_eat_time;
	int				eaten_amount;//
	pthread_mutex_t	last_eat_mutex;//
	pthread_mutex_t	eaten_amount_mutex;//
	struct s_vars	*vars;//
	bool			*is_dead;//
}	t_philo;

typedef struct s_vars
{
	int				philos_num;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	int				time_to_sleep;//
	int				time_to_eat;//
	int				time_to_die;//
	int				meals_amount;//
	bool			is_dead;//
}	t_vars;

// FUNCTIONS PROTOTYPES
// main.c
void		start_simulation(t_vars *vars);

// init_vars.c
bool		validate_input(int argc, char **argv, t_vars *vars);
bool		init_vars(t_vars *vars);
void		init_mutex(t_vars *vars);

// simulation.c
void		*philo_sim(t_philo *philo);
void		sleep_process(t_philo *philo, t_timeval *time);
void		eat_process(t_philo *philo, t_timeval *time);
void		put_forks(t_fork_mutex *l_fork, t_fork_mutex *r_fork);
void		pick_forks(t_fork_mutex *l_fork, t_fork_mutex *r_fork,
				t_timeval *time, t_philo *philo);

// checks.c
bool		is_dead(t_philo *philo);
bool		check_die(t_vars *vars);
bool		check_eaten_amount(t_vars *vars);

// utils.c
void		mut_print(t_philo *philo, t_timeval *cur_time,
				int id, char *action);
long long	time_in_ms(struct timeval *starttime);
void		my_usleep(long long ms, t_philo *philo);
int			ft_strlen(const char *s);
int			ft_atoi(const char *nptr);

#endif