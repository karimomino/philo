/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:36:52 by kamin             #+#    #+#             */
/*   Updated: 2022/05/24 14:58:26 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "philo.h"

typedef struct s_philo
{
	int					status;
	int					num;
	int					min_eat;
	int					forks;
	pthread_mutex_t		fork_mutex;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		min_mutex;
	pthread_mutex_t		last_mutex;
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
	pthread_mutex_t		check_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print_mutex;
	int					*forks;
	t_philo				*philos;
	size_t				created;
}				t_container;

#endif
