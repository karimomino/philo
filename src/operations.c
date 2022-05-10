/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:53:06 by kamin             #+#    #+#             */
/*   Updated: 2022/05/10 04:06:46 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_forks(t_philo *philo)
{
	long long	time;

	if (philo->num % 2 > 0)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		time = get_time(philo);
		printf("%lld Philo %d took left fork \n", time, philo->num);
		pthread_mutex_lock(philo->right);
		time = get_time(philo);
		printf("%lld Philo %d took right fork \n", time, philo->num);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		time = get_time(philo);
		printf("%lld Philo %d took right fork \n", time, philo->num);
		pthread_mutex_lock(&(*philo).fork_mutex);
		time = get_time(philo);
		printf("%lld Philo %d took left fork \n", time, philo->num);
	}
	eat(philo);
}

void	eat(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	pthread_mutex_lock(&philo->time_mutex);
	printf("%lld Philo %d is eating.\n", time, philo->num);
	usleep(philo->info->eat * 1000);
	philo->last_eat = get_time(philo);
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
	sleep_op(philo);
}

void	sleep_op(t_philo *philo)
{
	long long	time;

	time = get_time(philo);
	printf("%lld Philo %d is sleeping.\n", time, philo->num);
	usleep(philo->info->sleep * 1000);
}
