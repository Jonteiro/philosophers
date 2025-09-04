/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:41:46 by jsilveir          #+#    #+#             */
/*   Updated: 2025/09/04 15:03:17 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	all_full(t_data *d)
{
	int	i;
	int	full;

	if (d->must_eat < 0)
		return (0);
	full = 1;
	i = 0;
	pthread_mutex_lock(&d->meal_mutex);
	while (i < d->n)
	{
		if (d->philos[i].meals_eaten < d->must_eat)
			full = 0;
		i++;
	}
	pthread_mutex_unlock(&d->meal_mutex);
	return (full);
}

/* void	*monitor_start(void *arg)
{
	t_data	*d;
	int		i;
	long	t;
	long	lm;

	d = (t_data *)arg;
	while (!get_stop(d))
	{
		i = 0;
		while (i < d->n && !get_stop(d))
		{
			pthread_mutex_lock(&d->meal_mutex);
			lm = d->philos[i].last_meal;
			pthread_mutex_unlock(&d->meal_mutex);
			t = now_ms();
			if (t - lm > d->t_die)
			{
				log_death(d, d->philos[i].id);
				return (NULL);
			}
			i++;
		}
		if (all_full(d))
		{
			set_stop(d, 1);
			break ;
		}
		usleep(200);
	}
	return (NULL);
} */

static int	check_death(t_data *d, int i)
{
	long	t;
	long	lm;

	pthread_mutex_lock(&d->meal_mutex);
	lm = d->philos[i].last_meal;
	pthread_mutex_unlock(&d->meal_mutex);
	t = now_ms();
	if (t - lm > d->t_die)
	{
		log_death(d, d->philos[i].id);
		return (1);
	}
	return (0);
}

void	*monitor_start(void *arg)
{
	t_data	*d;
	int		i;

	d = (t_data *)arg;
	while (!get_stop(d))
	{
		i = 0;
		while (i < d->n && !get_stop(d))
			if (check_death(d, i++))
				return (NULL);
		if (all_full(d))
			set_stop(d, 1);
		usleep(200);
	}
	return (NULL);
}
