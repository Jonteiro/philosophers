/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:42:05 by jsilveir          #+#    #+#             */
/*   Updated: 2025/09/04 15:06:03 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi_pos(const char *s, int *out)
{
	long	acc;
	int		i;

	acc = 0;
	i = 0;
	if (!s || !*s)
		return (1);
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '+')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		acc = acc * 10 + (s[i] - '0');
		if (acc > 2147483647)
			return (1);
		i++;
	}
	if (s[i] != '\0')
		return (1);
	*out = (int)acc;
	return (0);
}

void	*safe_malloc(size_t sz)
{
	void	*p;

	p = malloc(sz);
	if (!p)
		write(2, "Error: malloc failed\n", 22);
	else
		memset(p, 0, sz);
	return (p);
}
