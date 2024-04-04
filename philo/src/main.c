/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:08:37 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/04 16:41:33 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	start_simulation(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_create(&(vars->philos[i].tid), NULL,
			(void *)philo_sim, vars->philos + i);
		i++;
	}
	while (1)
	{
		if (check_die(vars) == true || check_eaten_amount(vars) == true)
			break ;
	}
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_join(vars->philos[i].tid, NULL);
		pthread_mutex_destroy(vars->forks + i);
		pthread_mutex_destroy(&vars->philos[i].last_eat_mutex);
		pthread_mutex_destroy(&vars->philos[i].eaten_amount_mutex);
		i++;
	}
	pthread_mutex_destroy(&vars->dead_mutex);
	pthread_mutex_destroy(&vars->print_mutex);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (validate_input(argc, argv, &vars) == false)
	{
		printf("\033[0;036mProgram expected arguments(numbers):\
		\n\tnumber_of_philosophers\n\ttime_to_die\n\ttime_to_eat\
		\n\ttime_to_sleep\
		\n\t[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (init_vars(&vars) == false)
		return (1);
	init_mutex(&vars);
	start_simulation(&vars);
}
