/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:34:15 by kamin             #+#    #+#             */
/*   Updated: 2022/05/28 14:32:49 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	philos.all = 0;
	return (philo(&philos));
}

void	*philo_fn(void *data)
{
	t_philo	*philo;

	philo = data;
	while (set_done(philo, 1) == 0)
		pick_forks(philo);
	free_unlock(philo);
	return (NULL);
}
