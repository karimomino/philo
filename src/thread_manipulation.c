/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:58:21 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 01:11:27 by kamin            ###   ########.fr       */
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

static void	init_mutex(t_container *cont)
{
	int	i;

	i = -1;
	while (++i < cont->num)
	{
		pthread_mutex_init(&cont->philos[i].fork_mutex, NULL);
		pthread_mutex_init(&cont->philos[i].time_mutex, NULL);
		pthread_mutex_init(&cont->philos[i].min_mutex, NULL);
	}
	init_right(cont);
	pthread_mutex_init(&cont->done_mutex, NULL);
	pthread_mutex_init(&cont->check_mutex, NULL);
	pthread_mutex_init(&cont->print_mutex, NULL);
	pthread_mutex_init(&cont->dead_mutex, NULL);
}

static int	create_monitors(t_container *cont)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while(++i < (*cont).num)
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

int	philo_create(t_container *cont)
{
	int				error;
	int				i;
	struct timeval	time;

	error = 0;
	i = -1;
	gettimeofday(&time, NULL);
	cont->created = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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
		pthread_mutex_destroy(&(*cont).philos[i].fork_mutex);
		pthread_mutex_destroy(&(*cont).philos[i].min_mutex);
		pthread_mutex_destroy(&(*cont).philos[i].time_mutex);
	}
	free(cont->philos);
	free(cont->forks);
	return (0);
}
