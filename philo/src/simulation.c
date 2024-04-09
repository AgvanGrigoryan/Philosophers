/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:45:16 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/09 15:01:07 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	pick_forks(t_fork_mutex *l_fork, t_fork_mutex *r_fork,
	t_timeval *time, t_philo *philo)
{
	pthread_mutex_lock(l_fork);
	mut_print(philo, time, philo->id, "has taken a fork");
	if (l_fork == r_fork)
	{
		while (is_dead(philo) == false)
			;
		return ;
	}
	pthread_mutex_lock(r_fork);
	mut_print(philo, time, philo->id, "has taken a fork");
}

void	put_forks(t_fork_mutex *l_fork, t_fork_mutex *r_fork)
{
	pthread_mutex_unlock(l_fork);
	if (l_fork == r_fork)
		return ;
	pthread_mutex_unlock(r_fork);
}

void	eat_process(t_philo *philo, t_timeval *time)
{
	if (is_dead(philo) == true)
		return ;
	mut_print(philo, time, philo->id, "is eating");
	my_usleep(philo->vars->time_to_eat, philo);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat_time = time_in_ms(time);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (philo->vars->meals_amount != -1)
	{
		pthread_mutex_lock(&philo->eaten_amount_mutex);
		philo->eaten_amount++;
		pthread_mutex_unlock(&philo->eaten_amount_mutex);
	}
}

void	sleep_process(t_philo *philo, t_timeval *time)
{
	if (is_dead(philo) == true)
		return ;
	mut_print(philo, time, philo->id, "is sleeping");
	my_usleep(philo->vars->time_to_sleep, philo);
}

void	*philo_sim(t_philo *philo)
{
	t_timeval		time;
	t_fork_mutex	*l_fork;
	t_fork_mutex	*r_fork;

	l_fork = &philo->vars->forks[philo->id];
	r_fork = &philo->vars->forks[(philo->id + 1) % philo->vars->philos_num];
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat_time = time_in_ms(&time);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if ((philo->id + 1) % 2 == 0)
		my_usleep(philo->vars->time_to_eat, philo);
	while (is_dead(philo) == false)
	{
		mut_print(philo, &time, philo->id, "is thinking");
		pick_forks(l_fork, r_fork, &time, philo);
		eat_process(philo, &time);
		put_forks(l_fork, r_fork);
		sleep_process(philo, &time);
	}
	return (NULL);
}
