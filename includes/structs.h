/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:36:52 by kamin             #+#    #+#             */
/*   Updated: 2022/05/07 01:16:37 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "philo.h"

typedef struct s_philo
{
	int				status;
	int				fork;
	pthread_mutex_t	fork_mutex;
	pthread_t		self;
}				t_philo;

typedef struct t_container{
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				min_eat;
	t_philo			*philos;
}				t_container;

#endif 
