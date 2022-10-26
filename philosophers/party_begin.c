/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataskin <ataskin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:39:40 by ataskin           #+#    #+#             */
/*   Updated: 2022/10/27 00:39:40 by ataskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_deneme.h"

void	*party_begin(void *lol)
{
	int		i;
	t_philo	*monk;
	t_table	*can;

	monk = (t_philo *)lol;
	can = monk->arg;
	if (can->count_philo == 1)
		one_philo(can);
	else if (monk->id % 2 == 0)
	{
		philo_print(monk->arg, monk, "is making love");
		ft_usleep(60);
	}
	while (!monk->arg->flag_of_death)
	{
		eating(monk);
		sleeping(monk);
		thinking(monk);
	}
	return (NULL);
}

void	create_thread(t_table *all)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (i < all->count_philo)
	{
		pthread_create(&all->thread[i], NULL, &party_begin, &all->philo[i]);
		i++;
	}
	if (!death(all, get_time()))
	{
		i = 0;
		while (i < all->count_philo)
		{
			pthread_join(all->thread[i], NULL);
			i++;
		}
	}
}
