/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:27:36 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/10 14:56:59 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

bool	is_dead(t_vars *vars)
{
	bool	is_philo_dead;

	sem_wait(vars->dead_sem);
	is_philo_dead = vars->is_dead;
	sem_post(vars->dead_sem);
	return (is_philo_dead);
}

void	*philo_checker(t_vars *vars)
{
	while (1)
	{
		if (check_die(vars) == true)
			exit(1);
		if (check_eaten_amount(vars) == true)
			exit(0);
	}
}

bool	check_die(t_vars *vars)
{
	t_timeval	time;

	sem_wait(vars->last_eat_sem);
	if (time_in_ms(&time) - vars->last_eat_time > vars->time_to_die)
	{
		mut_print(vars, &time, "died");
		sem_wait(vars->dead_sem);
		vars->is_dead = true;
		sem_post(vars->dead_sem);
		sem_post(vars->last_eat_sem);
		sem_wait(vars->print_sem);
		return (true);
	}
	sem_post(vars->last_eat_sem);
	return (false);
}

bool	check_eaten_amount(t_vars *vars)
{
	bool	ate_already;

	if (vars->must_eat_amount == -1)
		return (false);
	ate_already = false;
	sem_wait(vars->eaten_amount_sem);
	if (vars->eaten_amount >= vars->must_eat_amount)
		ate_already = true;
	sem_post(vars->eaten_amount_sem);
	return (ate_already);
}
