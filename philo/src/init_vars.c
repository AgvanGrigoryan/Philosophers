/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:59:26 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/03 19:11:47 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	init_vars(t_vars *vars)
{
	int	i;

	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->philos_num);
	if (vars->philos == NULL)
		return (false);
	vars->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->philos_num);
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
		vars->philos[i].last_eat_time = LLONG_MAX;
		i++;
	}
	return (true);
}

void		init_mutex(t_vars *vars)
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
