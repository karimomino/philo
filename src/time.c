/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:43:27 by kamin             #+#    #+#             */
/*   Updated: 2022/05/22 14:24:41 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time(void)
{
	size_t			time;
	struct timeval	timeaz;

	time = 0;
	gettimeofday(&timeaz, NULL);
	time = ((timeaz.tv_sec * 1000) + (timeaz.tv_usec / 1000));
	return (time);
}

void	ft_usleep(size_t sleep)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() < (start + sleep))
	{
		usleep(25);
	}
}

long long	get_time(t_philo *philo)
{
	size_t		time;

	time = get_current_time() - philo->info->created;
	return (time);
}
