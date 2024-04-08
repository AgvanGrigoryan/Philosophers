/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:35:54 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/08 18:42:22 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

#define MAX_NUM_LEN 11

void	mut_print(t_vars *vars, t_timeval *time, char *action)
{
	sem_wait(vars->print_sem);
	if (is_dead(vars) == false)
		printf("%lld %d %s\n", time_in_ms(time), vars->id + 1, action);
	sem_post(vars->print_sem);
}

long long	time_in_ms(t_timeval *time)
{
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void	my_usleep(long long ms, t_vars *vars)
{
	long long	start;
	t_timeval	time;

	start = time_in_ms(&time);
	while (time_in_ms(&time) - start <= ms)
	{
		if (is_dead(vars) == true)
			break ;
		usleep(10);
	}
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	long long	num;

	if (ft_strlen(nptr) >= MAX_NUM_LEN)
		return (-1);
	num = 0;
	while ('0' <= *nptr && *nptr <= '9')
	{
		num *= 10;
		num += *nptr - 48;
		nptr++;
	}
	if (num > INT_MAX || num < INT_MIN || *nptr != '\0')
		return (-1);
	return (num);
}
