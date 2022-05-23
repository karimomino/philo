/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:53:06 by kamin             #+#    #+#             */
/*   Updated: 2022/05/22 16:32:16 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	if (!philo->info->done)
		print_message(philo, 3);
}

static void take_fork(t_philo *philo, int which)
{
	long long	time;
	int			fork;
	
	if (philo->num == 1 && which == 2)
		fork = philo->info->num - 1;
	else if (which == 2)
		fork = philo->num;
	else
		fork = philo->num - 1;
	if (!philo->info->done && philo->info->forks[fork])
	{
		pthread_mutex_lock(&philo->fork_mutex);
		philo->info->forks[fork] = 0;
		time = get_time(philo);
		philo->forks++;
		print_message(philo, 0);
	}
	// else if (!philo->info->done && which == 2 && philo->info->forks[fork])
	// {
	// 	pthread_mutex_lock(philo->right);
	// 	philo->info->forks[fork] = 0;
	// 	time = get_time(philo);
	// 	philo->forks++;
	// 	print_message(philo, 0);
	// }
}

static void put_fork(t_philo *philo)
{
	long long	time;
	int			l_fork;
	int			r_fork;
	
	if (philo->num == 1)
		r_fork = philo->info->num - 1;
	else
		r_fork = philo->num;
	l_fork = philo->num - 1;

	philo->info->forks[l_fork] = 1;
	philo->info->forks[r_fork] = 1;
	if (philo->num % 2 > 0)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&philo->fork_mutex);
	}
}

void	pick_forks(t_philo *philo)
{
	long long	time;

	if (philo->num % 2 > 0 && !philo->info->done)
	{
		take_fork(philo, 1);
		take_fork(philo, 2);
	}
	else if (philo->num % 2 == 0 && !philo->info->done)
	{
		take_fork(philo, 2);
		take_fork(philo, 1);
	}
	eat(philo);
}

void	eat(t_philo *philo)
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
	put_fork(philo);
	sleep_op(philo);
}

void	sleep_op(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	if (!philo->info->done && philo->forks == 2)
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
