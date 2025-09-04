/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:41:58 by jsilveir          #+#    #+#             */
/*   Updated: 2025/09/04 15:05:37 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_forks(t_philo *p)
{
	int	a;
	int	b;

	a = p->left;
	b = p->right;
	if (a > b)
	{
		a = p->right;
		b = p->left;
	}
	pthread_mutex_lock(&p->data->forks[a]);
	log_state(p->data, p->id, MSG_FORK);
	if (p->data->n == 1)
		return ;
	pthread_mutex_lock(&p->data->forks[b]);
	log_state(p->data, p->id, MSG_FORK);
}

static void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->data->forks[p->left]);
	if (p->data->n > 1)
		pthread_mutex_unlock(&p->data->forks[p->right]);
}

static void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->meal_mutex);
	p->last_meal = now_ms();
	pthread_mutex_unlock(&p->data->meal_mutex);
	log_state(p->data, p->id, MSG_EAT);
	sleep_ms_precise(p->data->t_eat, p->data);
	pthread_mutex_lock(&p->data->meal_mutex);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->meal_mutex);
}

static void	*solo_case(t_philo *p)
{
	log_state(p->data, p->id, MSG_FORK);
	sleep_ms_precise(p->data->t_die, p->data);
	log_death(p->data, p->id);
	return (NULL);
}

void	*philo_start(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->data->meal_mutex);
	p->last_meal = p->data->start_time;
	pthread_mutex_unlock(&p->data->meal_mutex);
	if (p->data->n == 1)
		return (solo_case(p));
	if (p->id % 2 == 0)
		usleep(1000);
	while (!get_stop(p->data))
	{
		take_forks(p);
		if (p->data->n == 1)
			break ;
		eat(p);
		drop_forks(p);
		log_state(p->data, p->id, MSG_SLEEP);
		sleep_ms_precise(p->data->t_sleep, p->data);
		log_state(p->data, p->id, MSG_THINK);
		usleep(500);
	}
	if (p->data->n > 1)
		drop_forks(p);
	return (NULL);
}
