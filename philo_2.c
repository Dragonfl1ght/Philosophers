/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkory <hkory@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:58:05 by hkory             #+#    #+#             */
/*   Updated: 2022/08/01 16:58:23 by hkory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *p, char *s)
{
	pthread_mutex_lock(&(p->link->print));
	if (p->link->flag != 1)
		printf("%lu %d %s", get_time() - p->link->start, p->n, s);
	pthread_mutex_unlock(&(p->link->print));
}

void	take_f_e(t_philo *p)
{
	pthread_mutex_lock(&(p->link->fork[p->right]));
	print(p, "has taken a fork\n");
	pthread_mutex_lock(&(p->link->fork[p->left]));
	print(p, "has taken a fork\n");
	print(p, "is eating\n");
	p->set_time = get_time();
	ft_usleep(p->link->eat);
	pthread_mutex_unlock(&(p->link->fork[p->right]));
	pthread_mutex_unlock(&(p->link->fork[p->left]));
}

void	check(t_data *p)
{
	int	f;
	int	all;

	f = 0;
	all = 0;
	while (f != 1)
	{
		f = check_1(p, all);
	}
}

int	check_1(t_data *p, int all)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		if (p->philo[i].t_eat >= p->must_eat && p->must_eat != -1)
			all++;
		if (get_time() - p->philo[i].set_time > p->die)
		{
			print(p->philo, "died\n");
			p->flag = 1;
			return (1);
		}
		if (all == p->n_philo)
			return (1);
		i++;
		ft_usleep(50);
	}
	return (0);
}

void	end(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		pthread_mutex_destroy(&p->fork[i]);
		i++;
	}
}
