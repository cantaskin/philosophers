/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultilits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataskin <ataskin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 01:00:41 by ataskin           #+#    #+#             */
/*   Updated: 2022/10/27 01:00:41 by ataskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_deneme.h"

long	long	int	get_time(void)
{
	struct timeval	i;

	gettimeofday (&i, NULL);
	return ((i.tv_sec * 1000) + (i.tv_usec / 1000));
}

void	ft_free(t_table *all)
{
	if (all->philo)
		free(all->philo);
	if (all->forks)
		free(all->forks);
	if (all->thread)
		free(all->thread);
	free(all);
}

void	philo_print(t_table *table, t_philo *philo, char *str)
{
	if (table->flag_of_death)
		return ;
	pthread_mutex_lock(&table->print);
	if (table->flag_of_death)
		return ;
	printf("%lld %d %s\n",
		get_time() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(&table->print);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(60);
}

void	kill_them_all(t_table *all)
{
	int	i;

	i = 0;
	while (i < all->count_philo)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->final_eat);
}
