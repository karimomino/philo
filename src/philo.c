/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:34:15 by kamin             #+#    #+#             */
/*   Updated: 2022/05/19 01:34:03 by kamin            ###   ########.fr       */
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
		if ((*cont).philos[i].min_eat < (*cont).min_eat || (*cont).philos[i].info->min_eat == -1)
			done = 0;
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
	philos.forks = (int *)malloc(philos.num * sizeof(int));
	if (philos.philos == NULL || philos.forks == NULL)
		return (-1);
	while (++i < philos.num)
		philos.forks[i] = 1;
	pthread_mutex_init(&philos.done_mutex, NULL);
	pthread_mutex_init(&philos.print_mutex, NULL);
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
		if (time - philo->last_eat > philo->info->die)
		{
			printf("\033[0;31m%lld Philo %d Died with %d eats.\n\033[0m", time, philo->num, philo->min_eat);
			philo->info->done = 1;
			return (NULL);
		}
		if (eat_check(philo->info))
		{
			printf("Everyone Ate!\n");
			philo->info->done = 1;
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->done_mutex);
		pthread_mutex_unlock(&philo->time_mutex);
	}
	return (NULL);
}
