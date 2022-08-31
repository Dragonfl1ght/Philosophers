/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkory <hkory@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:58:01 by hkory             #+#    #+#             */
/*   Updated: 2022/08/01 16:58:22 by hkory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(unsigned int time_to_wait)
{
	unsigned long	time;

	time = get_time();
	while (get_time() < time + (unsigned long)time_to_wait)
		usleep(100);
}

void	*live(void	*p)
{
	t_philo	*new_p;

	new_p = (t_philo *)p;
	while (!new_p->link->flag)
	{
		take_f_e(new_p);
		if (new_p->t_eat != new_p->link->must_eat)
		{
			print(p, "is sleeping\n");
			ft_usleep(new_p->link->sleep);
			print(p, "is thinking\n");
		}
		new_p->t_eat++;
	}
	return (NULL);
}

void	create_thread(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		p->philo[i].set_time = get_time();
		pthread_create(&p->philo[i].thread,
			NULL, live, &p->philo[i]);
		i += 2;
		ft_usleep(100);
	}
	i = 1;
	while (i < p->n_philo)
	{
		p->philo[i].set_time = get_time();
		pthread_create(&p->philo[i].thread,
			NULL, live, &p->philo[i]);
		i += 2;
		ft_usleep(100);
	}
	check(p);
	end(p);
}
