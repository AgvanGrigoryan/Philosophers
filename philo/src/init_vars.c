/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:59:26 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/04 19:02:04 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	int	i;

	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->philos_num);
	if (vars->philos == NULL)
		return (false);
	vars->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * vars->philos_num);
	if (vars->forks == NULL)
	{
		free(vars->philos);
		vars->philos = NULL;
		return (false);
	}
	vars->is_dead = false;
	i = 0;
	while (i < vars->philos_num)
	{
		vars->philos[i].id = i;
		vars->philos[i].eaten_amount = 0;
		vars->philos[i].vars = vars;
		vars->philos[i].is_dead = &vars->is_dead;
		vars->philos[i].last_eat_time = LLONG_MAX; // move to before simulation and change value
		i++;
	}
	return (true);
}

void	init_mutex(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_init(&vars->forks[i], NULL);
		pthread_mutex_init(&vars->philos[i].last_eat_mutex, NULL);
		pthread_mutex_init(&vars->philos[i].eaten_amount_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&vars->dead_mutex, NULL);
	pthread_mutex_init(&vars->print_mutex, NULL);
}
