/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:53:06 by kamin             #+#    #+#             */
/*   Updated: 2022/05/16 22:27:27 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	if (!philo->info->done)
		printf("\033[0;35m%lld Philo %d is thinking.\n\033[0m", time, philo->num);
}

void	pick_forks(t_philo *philo)
{
	long long	time;

	if (philo->num % 2 > 0 && !philo->info->done)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		time = get_time(philo);
		printf("\033[0;33m%lld Philo %d took left fork \n\033[0m", time, philo->num);
		pthread_mutex_lock(philo->right);
		time = get_time(philo);
		printf("\033[0;33m%lld Philo %d took right fork \n\033[0m", time, philo->num);
	}
	else if (philo->num % 2 == 0 && !philo->info->done)
	{
		pthread_mutex_lock(philo->right);
		time = get_time(philo);
		printf("\033[0;33m%lld Philo %d took right fork \n\033[0m", time, philo->num);
		pthread_mutex_lock(&(*philo).fork_mutex);
		time = get_time(philo);
		printf("\033[0;33m%lld Philo %d took left fork \n\033[0m", time, philo->num);
	}
	eat(philo);
}

void	eat(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	pthread_mutex_lock(&philo->time_mutex);
	pthread_mutex_lock(&philo->min_mutex);
	if (!philo->info->done)
		printf("\033[0;32m%lld Philo %d is eating.\n\033[0m", time, philo->num);
	philo->last_eat = get_time(philo);
	philo->min_eat++;
	usleep(philo->info->eat * 1000);
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
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_unlock(&philo->min_mutex);
	sleep_op(philo);
}

void	sleep_op(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	if (!philo->info->done)
		printf("\033[0;34m%lld Philo %d is sleeping.\n\033[0m", time, philo->num);
	usleep(philo->info->sleep * 1000);
	think(philo);
}
