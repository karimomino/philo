/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:52:59 by kamin             #+#    #+#             */
/*   Updated: 2022/05/10 01:01:52 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "structs.h"

/*MAIN ALGO*/
int		philo(t_container *cont);
int		philo_init(int ac, char **av);
void	*philo_fn(void *p_data);

/*THREAD HANDLING*/
int		philo_create(t_container *cont);
int		philo_join(t_container *cont);

/*ERROR HANDLING*/
int		error_handler(int argc, char **argv);
int		check_args(int argc, char **argv);
int		check_negs(int argc, char **argv);

/*UTILITY FUNCTIONS*/
int		ft_isnum(char *s);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);

/*OPERATIONS*/
void	pick_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_op(t_philo *philo);

/*Output Handling*/
void	ft_putstr_fd(char *s, int fd);

#endif