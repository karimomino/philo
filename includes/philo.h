/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:52:59 by kamin             #+#    #+#             */
/*   Updated: 2022/05/28 14:45:14 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include "structs.h"

/*MAIN ALGO*/
int			philo(t_container *cont);
int			philo_init(int ac, char **av);
void		*philo_fn(void *p_data);
void		*monitor_fn(void *p_data);

/*MUTEX HANDLING*/
void		init_mutex(t_container *cont);

/*THREAD HANDLING*/
int			philo_join(t_container *cont);

/*MONITORING*/
int			set_done(t_philo *philo, int type);

/*ERROR HANDLING*/
int			error_handler(int argc, char **argv);

/*FORK HANDELR*/
void		take_fork(t_philo *philo, int which);
void		put_fork(t_philo *philo);
int			set_fork(t_philo *philo, int fork, int val, int type);

/*UTILITY FUNCTIONS*/
int			ft_isnum(char *s);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
long long	get_time(t_philo *philo);
void		ft_usleep(size_t time);
size_t		get_current_time(void);
void		free_unlock(void *cont);

/*OPERATIONS*/
void		pick_forks(t_philo *philo);

/*Output Handling*/
void		ft_putstr_fd(char *s, int fd);
void		print_message(t_philo *philo, int type);

#endif
