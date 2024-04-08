/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:45:16 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/08 18:55:25 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	pick_forks(t_timeval *time, t_vars *vars)
{
	sem_wait(vars->forks);
	mut_print(vars, time, "has taken a fork");
	sem_wait(vars->forks);
	mut_print(vars, time, "has taken a fork");
}

void	put_forks(t_vars *vars)
{
	sem_post(vars->forks);
	sem_post(vars->forks);
}

void	eat_process(t_vars *vars, t_timeval *time)
{
	if (is_dead(vars) == true)
		return ;
	mut_print(vars, time, "is eating");
	sem_wait(vars->last_eat_sem);
	vars->last_eat_time = time_in_ms(time);
	sem_post(vars->last_eat_sem);
	my_usleep(vars->time_to_eat, vars);
	sem_wait(vars->eaten_amount_sem);
	vars->eaten_amount++;
	sem_post(vars->eaten_amount_sem);
}

void	sleep_process(t_vars *vars, t_timeval *time)
{
	if (is_dead(vars) == true)
		return ;
	mut_print(vars, time, "is sleeping");
	my_usleep(vars->time_to_sleep, vars);
}

void	*philo_sim(t_vars *vars)
{
	t_timeval		time;

	sem_wait(vars->last_eat_sem);
	vars->last_eat_time = time_in_ms(&time);
	sem_post(vars->last_eat_sem);
	if (pthread_create(&vars->checker_tid, NULL,
			(void *)philo_checker, vars) != 0)
		exit(1);
	while (true)
	{
		mut_print(vars, &time, "is thinking");
		pick_forks(&time, vars);
		eat_process(vars, &time);
		put_forks(vars);
		sleep_process(vars, &time);
	}
	return (NULL);
}
