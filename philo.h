/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:47:58 by jsilveir          #+#    #+#             */
/*   Updated: 2025/08/21 12:02:49 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>

# define MSG_FORK      "has taken a fork"
# define MSG_EAT       "is eating"
# define MSG_SLEEP     "is sleeping"
# define MSG_THINK     "is thinking"
# define MSG_DIED      "died"

typedef struct s_data t_data;

typedef struct s_philo
{
	int			id;
	int			left;
	int			right;
	long		last_meal;
	int			meals_eaten;
	pthread_t	thread;
	t_data		*data;
}   t_philo;

typedef struct s_data
{
	int			n;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			must_eat;
	long		start_time;
	int			stop;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t print_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t *forks;
	t_philo		*philos;
	pthread_t	monitor;       
} t_data;



int			parse_args(int ac, char **av, t_data *d);

int			setup(t_data *d);
void		cleanup(t_data *d);

long		now_ms(void);
long		since_start(t_data *d);
void		sleep_ms_precise(long ms, t_data *d);

int			get_stop(t_data *d);
void		set_stop(t_data *d, int v);
void		log_state(t_data *d, int id, const char *msg);
void		log_death(t_data *d, int id);

void		*philo_start(void *arg);

void		*monitor_start(void *arg);

int			ft_atoi_pos(const char *s, int *out);
void		*safe_malloc(size_t sz);

#endif