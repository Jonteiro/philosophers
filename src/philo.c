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

void	ft_error(char *error)
{
	ft_printf("error: %s", error);
	exit(1);
}

int	ft_atoi(char *str)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	main(int ac, char *av)
{
	if(ac != 5 && ac != 6)
		return(write(2, "argument count is wrong\n", 25));	
	pthread_create()
}
