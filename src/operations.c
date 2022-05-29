/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:53:06 by kamin             #+#    #+#             */
/*   Updated: 2022/05/29 11:11:56 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	if (!set_done(philo, 1))
		print_message(philo, 3);
}

static void	sleep_op(t_philo *philo)
{
	if (!set_done(philo, 1))
	{
		print_message(philo, 2);
		ft_usleep(philo->info->sleep);
	}
	if (philo->forks != 2)
	{
		philo->forks = 0;
		return ;
	}
	philo->forks = 0;
	think(philo);
}

static void	eat(t_philo *philo)
{
	if (!set_done(philo, 1) && philo->forks == 2)
	{
		pthread_mutex_lock(&philo->last_mutex);
		philo->last_eat = get_time(philo);
		pthread_mutex_unlock(&philo->last_mutex);
		print_message(philo, 1);
		pthread_mutex_lock(&philo->min_mutex);
		philo->min_eat++;
		pthread_mutex_unlock(&philo->min_mutex);
		ft_usleep(philo->info->eat);
	}
	else if (set_done(philo, 1))
		return ;
	put_fork(philo);
	sleep_op(philo);
}

void	pick_forks(t_philo *philo)
{
	long long	time;
	long long	time_diff;

	time = get_time(philo);
	time = time - philo->last_eat;
	time_diff = philo->info->die - philo->info->eat;
	if (philo->num % 2 > 0 && !set_done(philo, 1) && (time >= time_diff
			|| philo->min_eat == 0))
	{
		take_fork(philo, 1);
		if (philo->info->num == 1)
			ft_usleep(philo->info->die);
		take_fork(philo, 2);
	}
	else if (philo->num % 2 == 0 && !set_done(philo, 1) && (time >= time_diff
			|| philo->min_eat == 0))
	{
		take_fork(philo, 2);
		take_fork(philo, 1);
	}
	else if (set_done(philo, 1))
		return ;
	eat(philo);
}
