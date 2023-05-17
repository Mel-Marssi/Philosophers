/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mars < mel-mars@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:31:43 by mel-mars          #+#    #+#             */
/*   Updated: 2023/05/17 16:09:18 by mel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_skip_spaces(const char *str)
{
	int	u;

	u = 0;
	while ((str[u] >= 9 && str[u] <= 13) || str[u] == 32)
		u++;
	return (u);
}

int	ft_atoi(const char *str)
{
	size_t	mem;
	int		e;

	e = ft_skip_spaces(str);
	if (str[e] == '-' || str[e] == '+')
		e++;
	mem = 0;
	while (str[e] >= '0' && str[e] <= '9')
	{
		mem = mem * 10 + (str[e] - '0');
		e++;
	}
	if (str[e] != '\0' && !(str[e] >= '0' && str[e] <= '9'))
		return (-1);
	if (str[ft_skip_spaces(str)] == '-')
		mem = -1 * mem;
	return (mem);
}

int	check_deads(t_philo *s)
{
	int			i;
	long int	ts;

	i = 0;
	while (i < s->x.numphilo)
	{
		pthread_mutex_lock(s[i].vars);
		ts = time_ms();
		if (ts - s[i].last_eat >= s[i].x.time_to_die && s[i].pass == 0)
		{
			printf("%li ms %i philo is dead\n", ts - s[i].last_eat, s[i].id);
			return (1);
		}
		pthread_mutex_unlock(s[i].vars);
		i++;
	}
	return (0);
}

int	check_meals(t_philo *s)
{
	int	i;

	i = 0;
	while (i < s->x.numphilo)
	{
		pthread_mutex_lock(s->vars);
		if (s[i].meals < s[i].x.num_meals)
		{
			pthread_mutex_unlock(s->vars);
			return (0);
		}
		pthread_mutex_unlock(s->vars);
		i++;
	}
	return (1);
}

void	get_info(t_philo *philo, int i, t_par s, pthread_mutex_t *vars_2)
{
	philo->id = i + 1;
	philo ->time = time_ms();
	philo->x = s;
	philo->pass = 0;
	philo->last_eat = time_ms();
	philo->meals = 0;
	philo->vars = vars_2;
}
