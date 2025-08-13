/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:47:58 by jsilveir          #+#    #+#             */
/*   Updated: 2025/08/11 13:58:58 by jsilveir         ###   ########.fr       */
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
// # include <pthread.h>

# define MSG_FORK      "has taken a fork"
# define MSG_EAT       "is eating"
# define MSG_SLEEP     "is sleeping"
# define MSG_THINK     "is thinking"
# define MSG_DIED      "died"

typedef struct s_data t_data;

typedef struct s_philo
{
	int			id;            /* 1..n */
	int			left;          /* index of left fork */
	int			right;         /* index of right fork */
	long		last_meal;     /* ms since epoch of last meal */
	int			meals_eaten;   /* counter */
	pthread_t	thread;        /* worker thread */
	t_data		*data;          /* backref */
}   t_philo;

struct s_data
{
	int			n;              /* number of philosophers */
	long		t_die;          /* ms */
	long		t_eat;          /* ms */
	long		t_sleep;        /* ms */
	int			must_eat;       /* -1 if not set */
	long		start_time;     /* ms */
	int			stop;           /* 0/1 guarded by stop_mutex */
	pthread_mutex_t stop_mutex;
	pthread_mutex_t print_mutex;
	pthread_mutex_t meal_mutex; /* protects last_meal & meals_eaten */
	pthread_mutex_t *forks;     /* array of n mutexes */
	t_philo		*philos;        /* array of n philosophers */
	pthread_t	monitor;       /* monitor thread */
} t_data;

/* parse.c */
int			parse_args(int ac, char **av, t_data *d);

/* init.c */
int			setup(t_data *d);
void		cleanup(t_data *d);

/* time.c */
long		now_ms(void);
long		since_start(t_data *d);
void		sleep_ms_precise(long ms, t_data *d);

/* print.c */
int			get_stop(t_data *d);
void		set_stop(t_data *d, int v);
void		log_state(t_data *d, int id, const char *msg);
void		log_death(t_data *d, int id);

/* routine.c */
void		*philo_start(void *arg);

/* monitor.c */
void		*monitor_start(void *arg);

/* utils.c */
int			ft_atoi_pos(const char *s, int *out);
void		*safe_malloc(size_t sz);