
#include "../philo.h"

int get_stop(t_data *d)
{
	int v;

	pthread_mutex_lock(&d->stop_mutex);
	v = d->stop;
	pthread_mutex_unlock(&d->stop_mutex);
	return (v);
}

void set_stop(t_data *d, int v)
{
	pthread_mutex_lock(&d->stop_mutex);
	d->stop = v;
	pthread_mutex_unlock(&d->stop_mutex);
}

static void print_line(long ts, int id, const char *msg)
{
	printf("%ld %d %s\n", ts, id, msg);
}

void log_state(t_data *d, int id, const char *msg)
{
	if (get_stop(d))
		return ;
	pthread_mutex_lock(&d->print_mutex);
	if (!get_stop(d))
		print_line(since_start(d), id, msg);
	pthread_mutex_unlock(&d->print_mutex);
}

void log_death(t_data *d, int id)
{
	pthread_mutex_lock(&d->print_mutex);
	if (!get_stop(d))
	{
		print_line(since_start(d), id, MSG_DIED);
		set_stop(d, 1);
	}
	pthread_mutex_unlock(&d->print_mutex);
}