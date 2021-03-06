/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:30:18 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 17:47:27 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_num_size(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	n /= 10;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*number;
	long	nbr;
	size_t	size;

	nbr = n;
	size = ft_num_size(n);
	number = (char *)malloc((size + 1) * sizeof(char));
	if (nbr == 0)
		number[0] = '0';
	if (nbr < 0)
	{
		number[0] = '-';
		nbr *= -1;
	}
	number[size] = '\0';
	while (nbr)
	{
		number[--size] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (number);
}

size_t	ft_strlen(const char *s)
{
	int	size;

	size = 0;
	while (s[size] != '\0')
	{
		size++;
	}
	return (size);
}

int	ft_atoi(const char *str)
{
	int	final;
	int	sign;

	final = 0;
	sign = 1;
	while (*str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		final = (final * 10) + *str - 48;
		str++;
	}
	return (final * sign);
}

void	free_unlock(void *cont)
{
	t_philo	*philo;

	philo = cont;
	if (philo->num % 2 && philo->forks == 1)
		pthread_mutex_unlock(&philo->fork_mutex);
	else if (philo->num % 2 && philo->forks == 2)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right);
	}
	else if (!(philo->num % 2) && philo->forks == 1)
		pthread_mutex_unlock(philo->right);
	else if (!(philo->num % 2) && philo->forks == 2)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&philo->fork_mutex);
	}
}
