/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:52:37 by kamin             #+#    #+#             */
/*   Updated: 2022/05/07 01:14:34 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	int	error;

	error = 0;
	error = error_handler(argc, argv);
	if (error < 0)
	{
		ft_putstr_fd("\033[0;31mUsage: ./philo [number of philos] ", 2);
		ft_putstr_fd("[time to die] [time to eat] [time to sleep] ", 2);
		ft_putstr_fd("[minimum meals (optional)]\n\033[0m", 2);
	}
	else
		philo_init(argc, argv);
	return (error);
}
