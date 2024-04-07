/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:08:37 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/07 20:05:48 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

bool	config_philo_process_args(t_vars *vars, pid_t pid, int i)
{
	vars->last_eat_sem = sem_open("/last_eat", O_CREAT, 0777, 1);
	vars->eaten_amount_sem = sem_open("/eaten_amount", O_CREAT, 0777, 1);
	vars->dead_sem = sem_open("/dead_sem", O_CREAT, 0777, 1);
	if (vars->last_eat_sem == SEM_FAILED
		|| vars->eaten_amount_sem == SEM_FAILED
		|| vars->dead_sem == SEM_FAILED)
		return (false);
	vars->philos_pids[i] = pid;
	vars->id = i;
	return (true);
}

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
			if (config_philo_process_args(vars, pid, i) == false)
				return (false);
			philo_sim(vars);
		}
		i++;
	}
	i = 0;
	while (i < vars->philos_num)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
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
