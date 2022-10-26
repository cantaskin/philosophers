/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataskin <ataskin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:35:00 by ataskin           #+#    #+#             */
/*   Updated: 2022/10/27 00:35:00 by ataskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_deneme.h"

void	thinking(t_philo *monk)
{
	if (monk->arg->flag_of_death)
		return ;
	philo_print(monk->arg, monk, "is making love");
}

void	sleeping(t_philo *monk)
{
	if (monk->arg->flag_of_death)
		return ;
	philo_print(monk->arg, monk, "is sleeping");
	ft_usleep(monk->time_to_sleep);
}

void	one_philo(t_table *all)
{
	pthread_mutex_lock(&all->forks[all->philo->left_fork]);
	philo_print(all, all->philo, "has taken a fork");
	ft_usleep(all->time_to_die);
	philo_print(all, all->philo, "died");
	pthread_mutex_unlock(&all->forks[all->philo->left_fork]);
}

void	eating(t_philo *monk)
{
	if (monk->arg->flag_of_death)
		return ;
	pthread_mutex_lock(&monk->arg->forks[monk->left_fork]);
	philo_print(monk->arg, monk, "has taken a left fork");
	pthread_mutex_lock(&monk->arg->forks[monk->right_fork]);
	philo_print(monk->arg, monk, "has taken a right fork");
	philo_print(monk->arg, monk, "is eating");
	monk->count_eat++;
	pthread_mutex_lock(&monk->arg->final_eat);
	monk->last_eat = get_time();
	pthread_mutex_unlock(&monk->arg->final_eat);
	ft_usleep(monk->arg->time_to_eat);
	pthread_mutex_unlock(&monk->arg->forks[monk->left_fork]);
	pthread_mutex_unlock(&monk->arg->forks[monk->right_fork]);
	if (monk->count_eat == monk->arg->count_of_lunch)
	{
		monk->count_eat = 0;
		monk->arg->count_of_cook++;
	}
}

int	death(t_table *all, long long time)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&all->final_eat);
		if (get_time() - all->philo[i].last_eat > all->time_to_die
			&& all->philo[i].last_eat != 0)
		{
			pthread_mutex_unlock(&all->final_eat);
			philo_print(all, all->philo, "is death");
			return (1);
		}
		else if (all->count_of_lunch)
		{
			if (all->count_of_lunch == all->count_of_cook)
			{
				return (0);
			}
		}
		pthread_mutex_unlock(&all->final_eat);
	}
	return (0);
}
