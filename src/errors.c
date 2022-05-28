/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:51:07 by kamin             #+#    #+#             */
/*   Updated: 2022/05/28 14:45:09 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_negs(int argc, char **argv)
{
	int	i;
	int	error;

	i = 0;
	error = 1;
	while (error > 0 && ++i < argc)
	{
		if (ft_atoi(argv[i]) < 1 && i == 1)
		{
			ft_putstr_fd("\033[0;31mYou need at least 1 philosopher.\n", 2);
			error = -1;
		}
		else if (ft_atoi(argv[i]) < 0)
		{
			ft_putstr_fd("\033[0;31mAll arguments must not be negative.\n", 2);
			error = -1;
		}
	}
	return (error);
}

static int	check_args(int argc, char **argv)
{
	int		i;
	int		error;
	char	*num;

	i = 0;
	error = 1;
	while (error > 0 && ++i < argc)
		error = ft_isnum(argv[i]);
	if (error < 1)
	{
		ft_putstr_fd("\033[0;31mArgument number: ", 2);
		num = ft_itoa(i);
		ft_putstr_fd(num, 2);
		ft_putstr_fd(" needs to be a number (INT)\n", 2);
		free(num);
	}
	else
		error = check_negs(argc, argv);
	return (error);
}

int	error_handler(int argc, char **argv)
{
	int	error;

	error = 1;
	if (argc < 5)
	{
		ft_putstr_fd("\033[0;31mToo few arguments\n", 2);
		error = -1;
	}
	else if (argc > 6)
	{
		ft_putstr_fd("\033[0;31mToo many arguments\n", 2);
		error = -1;
	}
	else
		error = check_args(argc, argv);
	return (error);
}
