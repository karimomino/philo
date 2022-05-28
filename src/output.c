/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:26:34 by kamin             #+#    #+#             */
/*   Updated: 2022/05/28 14:40:43 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static int	all(t_philo *philo)
{
	int	ret;

	ret = philo->info->all;
	if (set_done(philo, 1))
		philo->info->all = 1;
	return (ret);
}

void	print_message(t_philo *philo, int type)
{
	long long	time;

	time = get_time(philo);
	pthread_mutex_lock(&philo->info->print_mutex);
	if (type == 0 && !set_done(philo, 1))
		printf("\033[0;33m%lld Philo %d has taken a fork \n\033[0m",
			time, philo->num);
	else if (type == 1 && !set_done(philo, 1))
		printf("\033[0;32m%lld Philo %d is eating\n\033[0m", time, philo->num);
	else if (type == 2 && !set_done(philo, 1))
		printf("\033[0;34m%lld Philo %d is sleeping\n\033[0m",
			time, philo->num);
	else if (type == 3 && !set_done(philo, 1))
		printf("\033[0;35m%lld Philo %d is thinking\n\033[0m",
			time, philo->num);
	else if (type == 4 && set_done(philo, 1) && !all(philo))
	{
		printf("\033[0;31m%lld Philo %d died\n\033[0m", time, philo->num);
		philo->info->all = 1;
	}
	else if (type == 5 && set_done(philo, 1) && !all(philo))
		printf("Everyone Ate!\n");
	pthread_mutex_unlock(&philo->info->print_mutex);
}
