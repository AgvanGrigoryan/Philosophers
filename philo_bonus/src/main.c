/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:08:37 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/05 22:19:25 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

bool	start_simulation(t_vars *vars)
{
	pid_t	pid
	int	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pid = fork();
		if (pid == -1)
			return (false);
		if (pid == 0)
		{
			vars->philos.pid = pid;
			vars->philo.id = i;
			philo_sim(vars);
		}
		i++;
	}
	i = 0;
	while (i < vars->philos_num)
	{
		waitpid(0, NULL, 0);
		i++;
	}
	// CLEAR DESTROY SEMAPHORES
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	t_philo	philo;

	if (validate_input(argc, argv, &vars) == false)
	{
		printf("\033[0;036mProgram expected arguments(numbers):\
		\n\tnumber_of_philosophers\n\ttime_to_die\n\ttime_to_eat\
		\n\ttime_to_sleep\
		\n\t[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	vars.philo = &philo;
	if (init_vars(&vars) == false)
		return (1);
	if (start_simulation(&vars) == false)
		return (1);
	return (0);
}
