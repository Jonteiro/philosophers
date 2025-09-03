/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:32:10 by marvin            #+#    #+#             */
/*   Updated: 2025/09/03 12:32:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int all_full(t_data *d)
{
	int i;
	int full;

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

void *monitor_start(void *arg)
{
	t_data *d;
	int i;
	long t;
	long lm;

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
		usleep(500);
	}
	return (NULL);
}
