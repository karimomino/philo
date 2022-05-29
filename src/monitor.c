/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:50:20 by kamin             #+#    #+#             */
/*   Updated: 2022/05/29 11:20:15 by kamin            ###   ########.fr       */
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
		pthread_mutex_lock(&cont->philos[i].min_mutex);
		if ((*cont).philos[i].min_eat < (*cont).min_eat
			|| (*cont).philos[i].info->min_eat == -1)
			done = 0;
		pthread_mutex_unlock(&cont->philos[i].min_mutex);
	}
	return (done);
}

int	set_done(t_philo *philo, int type)
{
	int	ret;

	ret = 0;
	if (type == 1)
	{
		pthread_mutex_lock(&philo->info->done_mutex);
		ret = philo->info->done;
		pthread_mutex_unlock(&philo->info->done_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->info->done_mutex);
		philo->info->done = 1;
		ret = philo->info->done;
		pthread_mutex_unlock(&philo->info->done_mutex);
	}
	return (ret);
}

void	*monitor_fn(void *data)
{
	t_philo		*philo;
	long long	time;

	philo = data;
	while (1)
	{
		pthread_mutex_lock(&philo->last_mutex);
		time = get_time(philo) - philo->last_eat;
		pthread_mutex_unlock(&philo->last_mutex);
		if (time > philo->info->die)
		{
			set_done(philo, 2);
			print_message(philo, 4);
			return (NULL);
		}
		if (eat_check(philo->info))
		{
			set_done(philo, 2);
			print_message(philo, 5);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}
