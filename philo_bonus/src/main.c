/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:08:37 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/08 18:55:13 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <stdlib.h>
// bool	config_philo_process_args(t_vars *vars, pid_t pid, int i)
// {
// 	vars->philos_pids[i] = pid;
// 	vars->id = i;
// 	return (true);
// }

bool	start_simulation(t_vars *vars)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < vars->philos_num)
	{
		pid = fork();
		if (pid == -1)
			return (false);
		if (pid == 0)
		{
			vars->philos_pids[i] = pid;
			vars->id = i;
			philo_sim(vars);
			exit(0);
		}
		i++;
	}
	pid = waitpid(-1, NULL, 0);
	kill(0, SIGTERM);
	i = 0;
	while (i < vars->philos_num - 1)
		waitpid(-1, NULL, 0);
	// i = 0;
	// while (i < vars->philos_num)
	// {
	// 	if (vars->philos_pids[i] == pid)
	// 		continue;
	// 	kill(vars->philos_pids[i], SIGTERM)
	// }

	return (true);
	// CLEAR DESTROY SEMAPHORES
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
	{
		free(vars.philos_pids);
		return (1);
	}
	if (start_simulation(&vars) == false)
		return (1);
	return (0);
}
