/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workshop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mars < mel-mars@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:55:46 by mel-mars          #+#    #+#             */
/*   Updated: 2023/05/17 16:09:44 by mel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	eat(t_philo *s)
{
	pthread_mutex_lock(&s->my_fork);
	printf("%li ms %d philo has taken a fork\n", time_ms() - s->time, s->id);
	pthread_mutex_lock(s->n_fork);
	pthread_mutex_lock(s->vars);
	printf("%li ms %d philo has taken a second fork\n", time_ms() - s->time,
		s->id);
	s->pass = 1;
	printf("%li ms %i philo is eating\n", time_ms() - s->time, s->id);
	pthread_mutex_unlock(s->vars);
	pthread_mutex_lock(s->vars);
	s->last_eat = time_ms();
	s->meals++;
	pthread_mutex_unlock(s->vars);
	ft_usleep(s->x.time_to_eat);
}

void	*life_cercle(void *philo)
{
	t_philo	*s;

	s = (t_philo *)philo;
	while (1)
	{
		eat(s);
		pthread_mutex_unlock(&s->my_fork);
		pthread_mutex_unlock(s->n_fork);
		pthread_mutex_lock(s->vars);
		s->pass = 0;
		printf("%li ms %d is sleeping\n", time_ms() - s->time, s->id);
		pthread_mutex_unlock(s->vars);
		ft_usleep(s->x.time_to_sleep);
		pthread_mutex_lock(s->vars);
		printf("%li ms %d is thinking\n", time_ms() - s->time, s->id);
		pthread_mutex_unlock(s->vars);
	}
}

int	check_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] == '-' || argv[i][j] == '+') && j == 0)
				j++;
			if (argv[i][j] <= '0' && argv[i][j] >= '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_fork(t_philo	*philo, t_par s, pthread_mutex_t *vars_2)
{
	int	i;

	i = 0;
	while (i < s.numphilo)
	{
		get_info(&philo[i], i, s, vars_2);
		pthread_mutex_init(&philo[i].my_fork, NULL);
		i++;
	}
}

int	main(int ac, char **argv)
{
	t_par			s;
	t_philo			*philo;
	pthread_mutex_t	*vars_2;
	int				i;

	i = 0;
	if ((ac != 5 && ac != 6) || init(&s, argv) == -1)
	{
		printf("Invalid argument!\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * s.numphilo);
	vars_2 = malloc(sizeof(pthread_mutex_t));
	if (philo == NULL || vars_2 == NULL)
		return (1);
	pthread_mutex_init(vars_2, NULL);
	(init_fork(philo, s, vars_2), init_n_fork(philo, -1));
	start_thread(philo);
	while (1)
	{
		if (check_deads(philo) == 1)
			break ;
		if (ac == 6 && check_meals(philo) == 1)
			break ;
	}
}
