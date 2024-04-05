/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/05 22:31:56 by aggrigor         ###   ########.fr       */
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

// write, usleep, fork
# include <unistd.h>

// malloc, free  
# include <stdlib.h>

// gettimeofday
# include <sys/time.h>

// waitpid
# include <sys/wait.h>

// pthread_create, pthread_detach, pthread_join,
# include <pthread.h>

// sem_open, sem_close,
// sem_post, sem_wait, sem_unlink
# include <semaphore.h>

struct					s_vars;
typedef struct timeval	t_timeval;
typedef sem_wait		sem_lock;
typedef sem_post		sem_unlock;

// DEFINITIONS
typedef struct s_philo
{
	int				id;
	pid_t			pid;

	long long		last_eat_time;
	int				eaten_amount;
	sem_t			*last_eat_sem;
	sem_t			*eaten_amount_sem;
	struct s_vars	*vars;
	bool			is_dead;
}	t_philo;

typedef struct s_vars
{
	int				philos_num;
	t_philo			philo;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*forks;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				meals_amount;
	// bool			is_dead; 
}	t_vars;

// FUNCTIONS PROTOTYPES
// main.c
bool		start_simulation(t_vars *vars);

// init_vars.c
bool		validate_input(int argc, char **argv, t_vars *vars);
bool		init_vars(t_vars *vars);

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