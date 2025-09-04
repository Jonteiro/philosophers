/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:41:37 by jsilveir          #+#    #+#             */
/*   Updated: 2025/08/14 12:41:40 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void init_philos(t_data *d)
{
	int i;

	i = 0;
	while (i < d->n)
	{
		d->philos[i].id = i + 1;
		d->philos[i].left = i;
		d->philos[i].right = (i + 1) % d->n;
		d->philos[i].last_meal = 0;
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		i++;
	}
}

int setup(t_data *d)
{
	int i;

	if (pthread_mutex_init(&d->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&d->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&d->meal_mutex, NULL) != 0)
		return (1);
	d->forks = safe_malloc(sizeof(pthread_mutex_t) * d->n);
	if (!d->forks)
		return (1);
	i = 0;
	while (i < d->n)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	d->philos = safe_malloc(sizeof(t_philo) * d->n);
	if (!d->philos)
		return (1);
	init_philos(d);
	return (0);
}

void cleanup(t_data *d)
{
	int i;

	i = 0;
	if (d->forks)
	{
		while (i < d->n)
		{
			pthread_mutex_destroy(&d->forks[i]);
			i++;
		}
		free(d->forks);
	}
	if (d->philos)
		free(d->philos);
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->stop_mutex);
	pthread_mutex_destroy(&d->meal_mutex);
}
