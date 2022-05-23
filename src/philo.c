/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:34:15 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 01:43:19 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	eat_check(t_container *cont)
{
	int	done;
	int	i;

	done = 1;
	i = -1;
	while (++i < (*cont).num)
	{
		pthread_mutex_lock(&cont->philos[i].min_mutex);
		if ((*cont).philos[i].min_eat < (*cont).min_eat
			|| (*cont).philos[i].info->min_eat == -1)
			done = 0;
		pthread_mutex_unlock(&cont->philos[i].min_mutex);
	}
	return (done);
}

int	philo_init(int ac, char **av)
{
	t_container		philos;
	int				i;

	i = -1;
	philos.num = ft_atoi(av[1]);
	philos.die = ft_atoi(av[2]);
	philos.eat = ft_atoi(av[3]);
	philos.sleep = ft_atoi(av[4]);
	philos.done = 0;
	if (ac == 6)
		philos.min_eat = ft_atoi(av[5]);
	else
		philos.min_eat = -1;
	philos.philos = (t_philo *)malloc(philos.num * sizeof(t_philo));
	philos.forks = (int *)malloc(philos.num * sizeof(t_philo));
	if (philos.philos == NULL || philos.forks == NULL)
		return (-1);
	while (++i < philos.num)
		philos.forks[i] = 1;
	// pthread_mutex_init(&philos.done_mutex, NULL);
	// pthread_mutex_init(&philos.print_mutex, NULL);
	return (philo(&philos));
}

int	philo(t_container *cont)
{
	int	error;

	error = philo_create(cont);
	return (error);
}

void	*philo_fn(void *data)
{
	t_philo	*philo;

	philo = data;
	while (philo->info->done == 0)
		pick_forks(philo);
	free_unlock(philo);
	return (NULL);
}

static void	set_done(t_philo *philo)
{
	// pthread_mutex_lock(&philo->info->done_mutex);
	philo->info->done = 1;
	// pthread_mutex_unlock(&philo->info->done_mutex);
}

void	*monitor_fn(void *data)
{
	t_philo		*philo;
	long long	time;

	philo = data;
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		time = get_time(philo);
		if (time - philo->last_eat > philo->info->die)
		{
			pthread_mutex_lock(&philo->info->done_mutex);
			set_done(philo);
			print_message(philo, 4);
			pthread_mutex_unlock(&philo->info->done_mutex);
			// free_unlock(philo);
			return (NULL);
		}
		if (eat_check(philo->info))
		{
			pthread_mutex_lock(&philo->info->done_mutex);
			set_done(philo);
			print_message(philo, 5);
			pthread_mutex_unlock(&philo->info->done_mutex);
			// free_unlock(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->time_mutex);
	}
	return (NULL);
}
