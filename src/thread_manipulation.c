/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:58:21 by kamin             #+#    #+#             */
/*   Updated: 2022/05/07 01:19:11 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_create(t_container *cont)
{
	int	error;
	int	i;

	error = 0;
	i = -1;
	while (++i < (*cont).num)
	{
		error = pthread_create(&(*cont).philos[i].self,
				NULL, philo_fn, (void *)i);
		if (error)
		{
			ft_putstr_fd("\033[0;31mError Creating Thread\n", 2);
			return (-1);
		}
		(*cont).philos[i].fork = 1;
		(*cont).philos[i].status = -1;
		(*cont).philos[i].fork_mutex = PTHREAD_MUTEX_INITIALIZER;
	}
	return (philo_join(cont));
}

int	philo_join(t_container *cont)
{
	int	error;
	int	i;

	error = 0;
	i = -1;
	while (++i < (*cont).num)
	{
		error = pthread_join ((*cont).philos[i].self, NULL);
		if (error)
		{
			ft_putstr_fd("\033[0;31mError Joining Threads\n", 2);
			return (-1);
		}
	}
	return (0);
}
