/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:27:36 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/05 22:37:47 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

bool	is_dead(t_vars *vars)
{
	bool	is_philo_dead;

	sem_lock(vars->dead_sem);
	is_philo_dead = *(philo->is_dead);
	sem_unlock(vars->dead_sem);
	return (is_philo_dead);
}

bool	check_die(t_vars *vars)
{
	t_timeval	time;
	int			i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_lock(&vars->philos[i].last_eat_mutex);
		if (time_in_ms(&time) - vars->philos[i].last_eat_time
			> vars->time_to_die)
		{
			mut_print(vars->philos + i, &time, vars->philos[i].id, "died");
			pthread_mutex_lock(&vars->dead_mutex);
			vars->is_dead = true;
			pthread_mutex_unlock(&vars->dead_mutex);
			pthread_mutex_unlock(&vars->philos[i].last_eat_mutex);
			return (true);
		}
		pthread_mutex_unlock(&vars->philos[i].last_eat_mutex);
		i++;
	}
	return (false);
}

bool	check_eaten_amount(t_vars *vars)
{
	int	already_eaten;
	int	i;

	if (vars->meals_amount == -1)
		return (false);
	i = 0;
	already_eaten = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_lock(&vars->philos[i].eaten_amount_mutex);
		if (vars->philos[i].eaten_amount >= vars->meals_amount)
			already_eaten++;
		pthread_mutex_unlock(&vars->philos[i].eaten_amount_mutex);
		i++;
	}
	if (already_eaten == vars->philos_num)
	{
		pthread_mutex_lock(&vars->dead_mutex);
		vars->is_dead = true;
		pthread_mutex_unlock(&vars->dead_mutex);
		return (true);
	}
	return (false);
}
