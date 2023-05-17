/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mars < mel-mars@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:20:01 by mel-mars          #+#    #+#             */
/*   Updated: 2023/05/17 15:24:08 by mel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_par
{
	int		numphilo;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_die;
	long	num_meals;
}t_par;

typedef struct s_philo
{
	t_par				x;
	int					id;
	int					pass;
	int					meals;
	long int			time;
	long int			last_eat;
	pthread_t			philo;
	pthread_mutex_t		*n_fork;
	pthread_mutex_t		my_fork;
	pthread_mutex_t		*vars;
}t_philo;

int			ft_atoi(const char *str);
int			check_deads(t_philo *s);
int			check_meals(t_philo *s);
long int	time_ms(void);
int			check_argv(char **argv);
int			init(t_par *s, char **argv);
void		ft_usleep(int s);
void		get_info(t_philo *philo, int i, t_par s, pthread_mutex_t *vars_2);
void		init_n_fork(t_philo *philo, int i);
void		start_thread(t_philo *philo);
void		*life_cercle(void *philo);

#endif