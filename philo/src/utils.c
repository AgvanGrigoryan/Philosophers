/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:35:54 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/03 19:39:34 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	mut_print(t_philo *philo, t_timeval *time, int id, char *action)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	if (is_dead(philo) == false)
		printf("%lld %d %s\n", time_in_ms(time) , id + 1, action);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

long long	time_in_ms(t_timeval *time)
{
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

long long	my_get_time(void)
{
	static long long	start;
	t_timeval			t1;

	if (start == 0)
		start = time_in_ms(&t1);
	return (time_in_ms(&t1) - start);
}

void	my_usleep(long long ms, t_philo *philo)
{
	long long	start;
	t_timeval	time;

	start = time_in_ms(&time);
	while (time_in_ms(&time) - start <= ms)
	{
		if (check_die(philo->vars) == true)
			break;
		usleep(10);
	}
}

bool	is_dead(t_philo *philo)
{
	bool	is_philo_dead;

	pthread_mutex_lock(&philo->vars->dead_mutex);
	is_philo_dead = *(philo->is_dead);
	pthread_mutex_unlock(&philo->vars->dead_mutex);
	return (is_philo_dead);
}

bool	check_die(t_vars *vars)
{
	t_timeval	time;
	int			i;

	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_lock(&vars->philos[i].last_eat_mutex);
		if (time_in_ms(&time) - vars->philos[i].last_eat_time > vars->time_to_die)
		{
			mut_print(vars->philos + i, &time, vars->philos[i].id, "died");
			pthread_mutex_lock(&vars->dead_mutex);
			vars->is_dead = true;
			pthread_mutex_unlock(&vars->dead_mutex);
			// printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
			pthread_mutex_unlock(&vars->philos[i].last_eat_mutex);
			return (true);
		}
		pthread_mutex_unlock(&vars->philos[i].last_eat_mutex);
		i++;
	}
	return (false);
}

bool	check_eaten_amount(t_vars *vars)
{
	int	already_eaten;
	int	i;

	if (vars->meals_amount == -1)
		return (false);
	i = 0;
	already_eaten = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_lock(&vars->philos[i].eaten_amount_mutex);
		if (vars->philos[i].eaten_amount >= vars->meals_amount)
			already_eaten++;
		pthread_mutex_unlock(&vars->philos[i].eaten_amount_mutex);
		i++;
	}
	if (already_eaten == vars->philos_num)
		return (true);
	return (false);
}