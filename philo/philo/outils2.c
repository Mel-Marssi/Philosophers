/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mars < mel-mars@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:41:22 by mel-mars          #+#    #+#             */
/*   Updated: 2023/05/17 16:09:34 by mel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	init(t_par *s, char **argv)
{
	if (check_argv(argv) != 0)
		return (-1);
	s->numphilo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		s->num_meals = ft_atoi(argv[5]);
		if (s->num_meals <= 0)
			return (-1);
	}
	if (s->numphilo <= 0 || s->time_to_die <= 0
		|| s->time_to_eat <= 0 || s->time_to_sleep <= 0)
		return (-1);
	return (0);
}

long int	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int s)
{
	long	ts;

	ts = time_ms();
	while (time_ms() - ts < s)
		usleep(100);
}

void	init_n_fork(t_philo *philo, int i)
{
	while (++i < philo->x.numphilo - 1)
		philo[i].n_fork = &philo[i + 1].my_fork;
	philo[i].n_fork = &philo[0].my_fork;
}

void	start_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->x.numphilo)
	{
		pthread_create(&philo[i].philo, NULL, life_cercle, (void *)&philo[i]);
		usleep(100);
		i++;
	}
}
