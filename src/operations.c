/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:53:06 by kamin             #+#    #+#             */
/*   Updated: 2022/05/10 01:12:42 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->num % 2 > 0)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		printf("Philo %d took left fork \n", philo->num);
		pthread_mutex_lock(philo->right);
		printf("Philo %d took right fork \n", philo->num);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		printf("Philo %d took right fork \n", philo->num);
		pthread_mutex_lock(&(*philo).fork_mutex);
		printf("Philo %d took left fork \n", philo->num);
	}
	eat(philo);
}

void	eat(t_philo *philo)
{
	printf("Philo %d is eating.\n", philo->num);
	usleep(philo->info->eat * 1000);
	if (philo->num % 2 > 0)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&(*philo).fork_mutex);
	}
	sleep_op(philo);
}

void	sleep_op(t_philo *philo)
{
	printf("Philo %d is sleeping.\n", philo->num);
	usleep(philo->info->sleep * 1000);
}
