/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:59:26 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/05 22:32:16 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

bool	validate_input(int argc, char **argv, t_vars *vars)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return (false);
	}
	i = 0;
	vars->philos_num = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (vars->philos_num <= 0 || vars->time_to_die < 0
		|| vars->time_to_eat < 0 || vars->time_to_sleep < 0)
		return (false);
	if (argc != 6)
	{
		vars->meals_amount = -1;
		return (true);
	}
	vars->meals_amount = ft_atoi(argv[5]);
	if (vars->meals_amount <= 0)
		return (false);
	return (true);
}

bool	init_vars(t_vars *vars)
{
	vars->philo->eaten_amount = 0;
	vars->philo->is_dead = false;
	vars->vars = vars;
	vars->forks = sem_open("forks", O_CREAT, S_IRWXU, vars->philos_num);
	if (vars->forks == SEM_FAILED)
		return (false);
	vars->dead_sem = sem_open("dead_sem", O_CREAT, S_IRWXU, 1);
	if (vars->dead_sem == SEM_FAILED)
		return (false);
	vars->print_sem = sem_open("print_sem", O_CREAT, S_IRWXU, 1);
	if (vars->print_sem == SEM_FAILED)
		return (false);
	return (true);
	vars->philo->last_eat_sem = sem_open("last_eat_sem", O_CREAT, S_IRWXU, vars->philos_num);
	if (vars->forks == SEM_FAILED)
		return (false);
	vars->philo->eaten_amount_sem = sem_open("eaten_amount_sem", O_CREAT, S_IRWXU, vars->philos_num);
	if (vars->forks == SEM_FAILED)
		return (false);
	return (true);
}
