/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:35:54 by aggrigor          #+#    #+#             */
/*   Updated: 2024/04/04 16:29:24 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#define MAX_NUM_LEN 11

void	mut_print(t_philo *philo, t_timeval *time, int id, char *action)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	if (is_dead(philo) == false)
		printf("%lld %d %s\n", time_in_ms(time), id + 1, action);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

long long	time_in_ms(t_timeval *time)
{
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void	my_usleep(long long ms, t_philo *philo)
{
	long long	start;
	t_timeval	time;

	start = time_in_ms(&time);
	while (time_in_ms(&time) - start <= ms)
	{
		if (is_dead(philo) == true)
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
