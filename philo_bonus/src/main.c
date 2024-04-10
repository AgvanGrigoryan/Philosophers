/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:08:37 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/10 14:34:42 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
// #include <stdlib.h>
// bool	config_philo_process_args(t_vars *vars, pid_t pid, int i)
// {
// 	vars->philos_pids[i] = pid;
// 	vars->id = i;
// 	return (true);
// }

void	wait_processes(t_vars *vars)
{
	int		i;
	int		exit_status;
	pid_t	pid;

	i = 0;
	while (i <= vars->philos_num)
	{
		pid = waitpid(-1, &exit_status, 0);
		if (WEXITSTATUS(exit_status) > 0)
		{
			i = 0;
			while (i < vars->philos_num)
			{
				if (vars->philos_pids[i] != pid)
					kill(vars->philos_pids[i], SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
}

bool	start_simulation(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->philos_num)
	{
		vars->philos_pids[i] = fork();
		if (vars->philos_pids[i] == -1)
			return (false);
		if (vars->philos_pids[i] == 0)
		{
			vars->id = i;
			philo_sim(vars);
		}
	}
	wait_processes(vars);
	return (true);
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
	close_sems_and_unlink(&vars);
	return (0);
}
