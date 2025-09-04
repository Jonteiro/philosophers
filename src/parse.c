/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:41:30 by jsilveir          #+#    #+#             */
/*   Updated: 2025/09/04 15:03:40 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	set_arg_int(const char *s, int *dst)
{
	if (ft_atoi_pos(s, dst))
		return (1);
	if (*dst <= 0)
		return (1);
	return (0);
}

int	parse_args(int ac, char **av, t_data *d)
{
	if (ac != 5 && ac != 6)
	{
		write(2, "Usage: ./philo n_philo t_die t_eat t_sleep [n_eat]\n", 52);
		return (1);
	}
	if (set_arg_int(av[1], &d->n) || d->n > 1000)
		return (write(2, "Error: invalid n_philo\n", 24), 1);
	if (set_arg_int(av[2], (int *)&d->t_die))
		return (write(2, "Error: invalid t_die\n", 23), 1);
	if (set_arg_int(av[3], (int *)&d->t_eat))
		return (write(2, "Error: invalid t_eat\n", 23), 1);
	if (set_arg_int(av[4], (int *)&d->t_sleep))
		return (write(2, "Error: invalid t_sleep\n", 25), 1);
	d->must_eat = -1;
	if (ac == 6)
	{
		if (set_arg_int(av[5], &d->must_eat))
			return (write(2, "Error: invalid n_eat\n", 25), 1);
	}
	return (0);
}
