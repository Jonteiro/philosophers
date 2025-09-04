/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:42:02 by jsilveir          #+#    #+#             */
/*   Updated: 2025/09/04 15:07:05 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	since_start(t_data *d)
{
	return (now_ms() - d->start_time);
}

void	sleep_ms_precise(long ms, t_data *d)
{
	long	end;

	end = now_ms() + ms;
	while (now_ms() < end)
	{
		if (get_stop(d))
			break ;
		usleep(200);
	}
}
