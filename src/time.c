/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:43:27 by kamin             #+#    #+#             */
/*   Updated: 2022/05/19 01:34:45 by kamin            ###   ########.fr       */
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
