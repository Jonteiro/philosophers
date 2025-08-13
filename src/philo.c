/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:32:44 by jsilveir          #+#    #+#             */
/*   Updated: 2025/08/11 15:39:21 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int start_threads(t_data *d)
{
	int i;

	d->start_time = now_ms();
	i = 0;
	while (i < d->n)
	{
		if (pthread_create(&d->philos[i].thread, NULL, &philo_start, &d->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&d->monitor, NULL, &monitor_start, d) != 0)
		return (1);
	i = 0;
	while (i < d->n)
	{
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}
	pthread_join(d->monitor, NULL);
	return (0);
}

int main(int ac, char **av)
{
	t_data d;

	memset(&d, 0, sizeof(d));
	if (parse_args(ac, av, &d))
		return (1);
	if (setup(&d))
		return (cleanup(&d), 1);
	if (start_threads(&d))
		return (cleanup(&d), 1);
	cleanup(&d);
	return (0);
}

