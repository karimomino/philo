/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:59:09 by kamin             #+#    #+#             */
/*   Updated: 2022/06/02 17:03:01 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	set_fork(t_philo *philo, int fork, int val, int type)
{
	int	ret;

	ret = 0;
	if (type == 1)
	{
		pthread_mutex_lock(&philo->info->check_mutex);
		ret = philo->info->forks[fork];
		pthread_mutex_unlock(&philo->info->check_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->info->check_mutex);
		philo->info->forks[fork] = val;
		ret = philo->info->forks[fork];
		pthread_mutex_unlock(&philo->info->check_mutex);
	}
	return (ret);
	pthread_mutex_lock(&philo->info->check_mutex);
	philo->info->forks[fork] = val;
	pthread_mutex_unlock(&philo->info->check_mutex);
}

void	take_fork(t_philo *philo, int which)
{
	int			fork;

	if (philo->num == 1 && which == 2)
		fork = philo->info->num - 1;
	else if (which == 2)
		fork = philo->num;
	else
		fork = philo->num - 1;
	if (!set_done(philo, 1) && which == 1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		set_fork(philo, fork, 0, 2);
		philo->forks++;
		print_message(philo, 0);
	}
	else if (!set_done(philo, 1) && which == 2)
	{
		pthread_mutex_lock(philo->right);
		set_fork(philo, fork, 0, 2);
		philo->forks++;
		print_message(philo, 0);
	}
}

void	put_fork(t_philo *philo)
{
	int			l_fork;
	int			r_fork;

	if (philo->num == 1)
		r_fork = philo->info->num - 1;
	else
		r_fork = philo->num;
	l_fork = philo->num - 1;
	set_fork(philo, l_fork, 1, 2);
	set_fork(philo, r_fork, 1, 2);
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
	else if (philo->info->num == 1 && philo->forks > 0)
		pthread_mutex_unlock(&philo->fork_mutex);
}
