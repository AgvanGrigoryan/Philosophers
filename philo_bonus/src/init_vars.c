/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:59:26 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/05 18:11:46 by aggrigor         ###   ########.fr       */
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