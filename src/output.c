/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:26:34 by kamin             #+#    #+#             */
/*   Updated: 2022/05/22 15:28:36 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	print_message(t_philo *philo, int type)
{
	long long	time;

	time = get_time(philo);
	pthread_mutex_lock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->check_mutex);
	if (type == 0 && !philo->info->done)
		printf("\033[0;33m%lld Philo %d has taken a fork \n\033[0m",
		time, philo->num);
	else if (type == 1 && !philo->info->done)
		printf("\033[0;32m%lld Philo %d is eating\n\033[0m", time, philo->num);
	else if (type == 2 && !philo->info->done)
		printf("\033[0;34m%lld Philo %d is sleeping\n\033[0m",
			time, philo->num);
	else if (type == 3 && !philo->info->done)
		printf("\033[0;35m%lld Philo %d is thinking\n\033[0m",
			time, philo->num);
	else if (type == 4 && philo->info->done)
		printf("\033[0;31m%lld Philo %d died\n\033[0m", time, philo->num);
	pthread_mutex_unlock(&philo->info->check_mutex);
	pthread_mutex_unlock(&philo->info->print_mutex);
}
