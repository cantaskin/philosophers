/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataskin <ataskin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:49:52 by ataskin           #+#    #+#             */
/*   Updated: 2022/10/27 00:49:52 by ataskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_deneme.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	tmp;

	i = 0;
	a = 1;
	tmp = 0;
	while (str[i] == ' ' || (str[i] <= '\r' && str[i] >= '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = tmp * 10 + str[i] - 48;
		i++;
	}
	return (tmp * a);
}

void	init_philo(t_table *all)
{
	int	i;

	i = 0;
	while (i < all->count_philo)
	{
		all->philo[i].id = i + 1;
		all->philo[i].time_to_die = all->time_to_die;
		all->philo[i].time_to_eat = all->time_to_eat;
		all->philo[i].time_to_sleep = all->time_to_sleep;
		all->philo[i].count_eat = 0;
		all->philo[i].right_fork = i;
		all->philo[i].left_fork = i + 1;
		all->philo[i].arg = all;
		if (i + 1 == all->count_philo)
			all->philo[i].left_fork = 0;
		i++;
	}
	i = 0;
	all->time_start = get_time();
	while (i < all->count_philo)
	{
		all->philo[i].time_start = all->time_start;
		all->philo[i].last_eat = all->time_start;
		i++;
	}
}

int	memory_allocate(t_table *all)
{
	int	i;

	i = 0;
	if (!all)
		return (1);
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->count_philo);
	if (!all->philo)
		return (1);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->count_philo);
	if (!all->forks)
		return (1);
	all->thread = malloc(sizeof(pthread_t) * all->count_philo);
	if (!all->thread)
		return (1);
	while (i < all->count_philo)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		i++;
	}
	return (0);
}

void	init_table(int argc, char **argv, t_table *all)
{
	int	i;

	i = 0;
	all->count_philo = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	all->count_of_cook = 0;
	all->flag_of_death = 0;
	all->count_of_lunch = 0;
	if (argc == 6)
		all->count_of_lunch = ft_atoi(argv[5]);
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->final_eat, NULL);
	all->philo = NULL;
	all->forks = NULL;
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Argument count error\n");
		return (1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0)
	{
		printf("Philo number error\n");
		return (1);
	}
	if (ft_atoi(argv[3]) <= 0)
	{
		printf("Time to eat error\n");
		return (1);
	}
	if (ft_atoi(argv[4]) <= 0)
	{
		printf("Time to sleep error\n");
		return (1);
	}
	return (0);
}
