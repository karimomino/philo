/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:52:51 by kamin             #+#    #+#             */
/*   Updated: 2022/04/29 17:22:11 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static long long	ft_isint(char *str)
{
	long long	final;
	int			sign;

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

int	ft_isnum(char *s)
{
	int	valid;
	int	i;

	i = 0;
	valid = 1;
	if ((s[i] == '-' && s[i + 1] == '\0') || s[i] == '\0')
		return (-1);
	else if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && valid)
	{
		if (!ft_isdigit(s[i]))
			valid = -1;
		i++;
	}
	if (valid && (ft_isint(s) > 2147483647 || ft_isint(s) < -2147483648))
		valid = -1;
	return (valid);
}
