/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:26:55 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/31 17:31:06 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#define MAX_NUM_LEN 11
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
