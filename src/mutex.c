/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:10 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 17:52:05 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_right(t_container *cont)
{
	int	i;

	i = 0;
	(*cont).philos[i].right = &(*cont).philos[(*cont).num - 1].fork_mutex;
	while (++i < (*cont).num)
		(*cont).philos[i].right = &(*cont).philos[i - 1].fork_mutex;
}

void	init_mutex(t_container *cont)
{
	int	i;

	i = -1;
	while (++i < cont->num)
	{
		pthread_mutex_init(&cont->philos[i].fork_mutex, NULL);
		pthread_mutex_init(&cont->philos[i].time_mutex, NULL);
		pthread_mutex_init(&cont->philos[i].min_mutex, NULL);
		pthread_mutex_init(&cont->philos[i].last_mutex, NULL);
	}
	init_right(cont);
	pthread_mutex_init(&cont->done_mutex, NULL);
	pthread_mutex_init(&cont->check_mutex, NULL);
	pthread_mutex_init(&cont->print_mutex, NULL);
	pthread_mutex_init(&cont->dead_mutex, NULL);
}
