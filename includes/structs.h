/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:36:52 by kamin             #+#    #+#             */
/*   Updated: 2022/05/10 04:03:06 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "philo.h"

typedef struct s_philo
{
	int					status;
	int					fork;
	int					num;
	pthread_mutex_t		fork_mutex;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		*right;
	pthread_t			self;
	pthread_t			monitor;
	struct t_container	*info;
	long long			last_eat;
}				t_philo;

typedef struct t_container{
	int					num;
	int					die;
	int					eat;
	int					sleep;
	int					min_eat;
	int					done;
	pthread_mutex_t		done_mutex;
	t_philo				*philos;
	struct timeval		created;
}				t_container;

#endif 
