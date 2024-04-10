/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/10 14:18:54 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

// kill
# include <signal.h>

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

# define FORKS_SEM "/forks"
# define PRINT_SEM "/print_sem"
# define DEAD_SEM "/dead_sem"
# define EATEN_AMOUNT_SEM "/eaten_amount"
# define LAST_EAT_SEM "/last_eat"

// DEFINITIONS
typedef struct s_vars
{
	pthread_t		checker_tid;
	pid_t			*philos_pids;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*eaten_amount_sem;
	sem_t			*last_eat_sem;
	int				philos_num;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				id;
	int				must_eat_amount;
	int				eaten_amount;
	long long		last_eat_time;
	bool			is_dead;
}	t_vars;

// FUNCTIONS PROTOTYPES
// main.c
bool		start_simulation(t_vars *vars);

// init_vars.c
void		close_sems_and_unlink(t_vars *vars);
bool		validate_input(int argc, char **argv, t_vars *vars);
bool		init_vars(t_vars *vars);

// simulation.c
void		philo_sim(t_vars *vars);
void		sleep_process(t_vars *vars, t_timeval *time);
void		eat_process(t_vars *vars, t_timeval *time);
void		put_forks(t_vars *vars);
void		pick_forks(t_timeval *time, t_vars *vars);

// checks.c
bool		is_dead(t_vars *vars);
void		*philo_checker(t_vars *vars);
bool		check_die(t_vars *vars);
bool		check_eaten_amount(t_vars *vars);

// utils.c
void		mut_print(t_vars *vars, t_timeval *cur_time, char *action);
long long	time_in_ms(struct timeval *starttime);
void		my_usleep(long long ms, t_vars *vars);
int			ft_strlen(const char *s);
int			ft_atoi(const char *nptr);

#endif