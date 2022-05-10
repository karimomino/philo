/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:34:15 by kamin             #+#    #+#             */
/*   Updated: 2022/05/10 04:14:34 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_init(int ac, char **av)
{
	t_container	philos;

	philos.num = ft_atoi(av[1]);
	philos.die = ft_atoi(av[2]);
	philos.eat = ft_atoi(av[3]);
	philos.sleep = ft_atoi(av[4]);
	philos.done = 0;
	gettimeofday(&philos.created, NULL);
	if (ac == 6)
		philos.min_eat = ft_atoi(av[5]);
	else
		philos.min_eat = -1;
	philos.philos = (t_philo *)malloc(philos.num * sizeof(t_philo));
	if (philos.philos == NULL)
		return (-1);
	pthread_mutex_init(&philos.done_mutex, NULL);
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
	return (NULL);
}

void	*monitor_fn(void *data)
{
	t_philo		*philo;
	long long	time;

	philo = data;
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		pthread_mutex_lock(&philo->info->done_mutex);
		time = get_time(philo);
		if (time - philo->last_eat >= philo->info->die)
		{
			printf("%lld Philo %d Died.\n", time, philo->num);
			philo->info->done = 1;
			return (NULL);
		}
		pthread_mutex_unlock(&philo->time_mutex);
		pthread_mutex_unlock(&philo->info->done_mutex);
	}
	return (NULL);
}
