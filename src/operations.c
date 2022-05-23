/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:53:06 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 01:23:01 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	if (!philo->info->done)
		print_message(philo, 3);
}

static void	set_fork(t_philo *philo, int fork, int val)
{
	pthread_mutex_lock(&philo->info->check_mutex);
	philo->info->forks[fork] = val;
	pthread_mutex_unlock(&philo->info->check_mutex);
}

static void	take_fork(t_philo *philo, int which)
{
	int			fork;

	if (philo->num == 1 && which == 2)
		fork = philo->info->num - 1;
	else if (which == 2)
		fork = philo->num;
	else
		fork = philo->num - 1;
	if (!philo->info->done && which == 1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		set_fork(philo, fork, 0);
		philo->forks++;
		print_message(philo, 0);
	}
	else if (!philo->info->done && which == 2)
	{
		pthread_mutex_lock(philo->right);
		set_fork(philo, fork, 0);
		philo->forks++;
		print_message(philo, 0);
	}
}


static void	put_fork(t_philo *philo)
{
	int			l_fork;
	int			r_fork;

	if (philo->num == 1)
		r_fork = philo->info->num - 1;
	else
		r_fork = philo->num;
	l_fork = philo->num - 1;
	set_fork(philo, l_fork, 1);
	set_fork(philo, r_fork, 1);
	if (philo->num % 2 > 0 && philo->forks == 2)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right);
	}
	else if (philo->forks == 2)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&philo->fork_mutex);
	}
}

static void	sleep_op(t_philo *philo)
{
	if (!philo->info->done)
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
	if (!philo->info->done && philo->forks == 2)
	{
		pthread_mutex_lock(&philo->time_mutex);
		pthread_mutex_lock(&philo->min_mutex);
		philo->last_eat = get_time(philo);
		print_message(philo, 1);
		philo->min_eat++;
		ft_usleep(philo->info->eat);
		pthread_mutex_unlock(&philo->time_mutex);
		pthread_mutex_unlock(&philo->min_mutex);
	}
	else if (philo->info->done)
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
	if (philo->num % 2 > 0 && !philo->info->done && (time >= time_diff
			|| philo->min_eat == 0))
	{
		take_fork(philo, 1);
		take_fork(philo, 2);
	}
	else if (philo->num % 2 == 0 && !philo->info->done && (time >= time_diff
			|| philo->min_eat == 0))
	{
		take_fork(philo, 2);
		take_fork(philo, 1);
	}
	else if (philo->info->done)
		return ;
	eat(philo);
}
