/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/03 18:54:46 by aggrigor         ###   ########.fr       */
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

struct s_vars;
typedef struct timeval t_timeval;
typedef	void * t_philo_handler;

// DEFINITIONS
typedef struct s_philo
{
	int			id;
	pthread_t	tid;

	long long		last_eat_time;
	int				eaten_amount;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	eaten_amount_mutex;
	struct s_vars	*vars;
	bool			*is_dead;
}	t_philo;

typedef struct s_vars
{
	int				philos_num;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				meals_amount;
	bool			is_dead;
	
}	t_vars;



// FUNCTIONS PROTOTYPES

// main.c
bool		validate_input(int argc, char **argv, t_vars *vars);

// init_vars.c
bool		init_vars(t_vars *vars);
void		init_mutex(t_vars *vars);

// utils.c
void		mut_print(t_philo *philo, t_timeval *cur_time, int id, char *action);
long long	time_in_ms(struct timeval *starttime);
long long	my_get_time(void);
void		my_usleep(long long ms, t_philo *philo);
bool		is_dead(t_philo *philo);
bool	check_die(t_vars *vars);
bool	check_eaten_amount(t_vars *vars);
// ft_atoi.c
int			ft_atoi(const char *nptr);

// UTILS
int			ft_strlen(const char *s);

#endif