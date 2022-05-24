/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:58:21 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 18:18:08 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	create_monitors(t_container *cont)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < (*cont).num)
	{
		error = pthread_create(&(*cont).philos[i].monitor,
				NULL, monitor_fn, &(*cont).philos[i]);
		if (error)
		{
			ft_putstr_fd("\033[0;31mError Creating Thread\n", 2);
			return (-1);
		}
		pthread_join((*cont).philos[i].monitor, NULL);
	}
	return (0);
}

static void	destroy(t_container *cont)
{
	int	i;

	i = -1;
	while (++i < cont->num)
	{
		pthread_mutex_destroy(&cont->philos[i].fork_mutex);
		pthread_mutex_destroy(&cont->philos[i].min_mutex);
		pthread_mutex_destroy(&cont->philos[i].time_mutex);
		pthread_mutex_destroy(&cont->philos[i].last_mutex);
	}
	pthread_mutex_destroy(&cont->check_mutex);
	pthread_mutex_destroy(&cont->done_mutex);
	pthread_mutex_destroy(&cont->print_mutex);
	pthread_mutex_destroy(&cont->dead_mutex);
	free(cont->philos);
	free(cont->forks);
}

static int	philo_create(t_container *cont)
{
	int				error;
	int				i;

	error = 0;
	i = -1;
	cont->created = get_current_time();
	init_mutex(cont);
	while (++i < (*cont).num)
	{
		cont->philos[i].status = -1;
		cont->philos[i].num = i + 1;
		cont->philos[i].info = cont;
		cont->philos[i].min_eat = 0;
		cont->philos[i].forks = 0;
		cont->philos[i].last_eat = 0;
		error = pthread_create(&(*cont).philos[i].self,
				NULL, philo_fn, &(*cont).philos[i]);
		if (error)
		{
			ft_putstr_fd("\033[0;31mError Creating Thread\n", 2);
			return (-1);
		}
	}
	create_monitors(cont);
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
	destroy(cont);
	return (0);
}

int	philo(t_container *cont)
{
	int	error;

	error = philo_create(cont);
	return (error);
}
