/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:08:37 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/03 19:31:23 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void	print_info_about_philos(t_vars *vars)
// {
// 	printf("Common Information\n");
// 	printf("time_to_eat: %d, time_to_sleep: %d, time_to_die: %d\n\n", vars->time_to_eat, vars->time_to_sleep, vars->time_to_die);

// 	for (int i = 0; i < vars->philos_num; i++)
// 	{
// 		printf("Philo №%d: \n\ttime_to_eat: %d, time_to_sleep: %d, time_to_die: %d\n\n", i, vars->philos[i].time_to_eat, vars->philos[i].time_to_sleep, vars->philos[i].time_to_die);
// 	}
// }

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

void	*philo_sim(void *void_philo)
{
	// printf("TID:%d\n", philo->id);
	t_timeval		cur_time;
	t_philo			*philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	philo = (t_philo *)void_philo;
	l_fork = &philo->vars->forks[philo->id];
	r_fork = &philo->vars->forks[(philo->id + 1) % philo->vars->philos_num];
	if (philo->id + 1 % 2 == 0)
		usleep(philo->vars->time_to_eat);
	while (is_dead(philo) == false)
	{

		mut_print(philo, &cur_time, philo->id, "is thinking");
		pthread_mutex_lock(l_fork);
		mut_print(philo, &cur_time, philo->id, "has taken a fork");
		pthread_mutex_lock(r_fork);
		mut_print(philo, &cur_time, philo->id, "has taken a fork");
		mut_print(philo, &cur_time, philo->id, "is eating");
		my_usleep(philo->vars->time_to_eat, philo);
		
		pthread_mutex_lock(&philo->last_eat_mutex);		
		philo->last_eat_time = time_in_ms(&cur_time);
		pthread_mutex_unlock(&philo->last_eat_mutex);

		pthread_mutex_lock(&philo->eaten_amount_mutex);
		philo->eaten_amount++;
		pthread_mutex_unlock(&philo->eaten_amount_mutex);

		pthread_mutex_unlock(l_fork);
		pthread_mutex_unlock(r_fork);
		mut_print(philo, &cur_time, philo->id, "is sleeping");
		my_usleep(philo->vars->time_to_sleep, philo);
	}
	return (NULL);
}

void	start_simulation(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_create(&(vars->philos[i].tid), NULL,
				philo_sim, vars->philos + i);
		i++;
	}
	while (1)
	{
		if (check_die(vars) == true || check_eaten_amount(vars) == true)
			break;
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
