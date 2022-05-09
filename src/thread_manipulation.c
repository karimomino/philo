/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:58:21 by kamin             #+#    #+#             */
/*   Updated: 2022/05/10 01:10:57 by kamin            ###   ########.fr       */
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

int	philo_create(t_container *cont)
{
	int	error;
	int	i;

	error = 0;
	i = -1;
	while (++i < (*cont).num)
		pthread_mutex_init(&(*cont).philos[i].fork_mutex, NULL);
	init_right(cont);
	i = -1;
	while (++i < (*cont).num)
	{
		error = pthread_create(&(*cont).philos[i].self,
				NULL, philo_fn, &(*cont).philos[i]);
		if (error)
		{
			ft_putstr_fd("\033[0;31mError Creating Thread\n", 2);
			return (-1);
		}
		(*cont).philos[i].fork = 1;
		(*cont).philos[i].status = -1;
		(*cont).philos[i].num = i + 1;
		(*cont).philos[i].info = cont;
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
