/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_deneme.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataskin <ataskin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 01:02:13 by ataskin           #+#    #+#             */
/*   Updated: 2022/10/27 01:11:51 by ataskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_DENEME_H
# define THREAD_DENEME_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				flag_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	int				left_fork;
	int				right_fork;
	long long		time_start;
	long long		last_eat;
	struct s_table	*arg;
}t_philo;

typedef struct s_table
{
	int				count_philo;
	int				count_of_cook;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_lunch;
	int				flag_of_death;
	long long		time_start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	final_eat;
	pthread_t		*thread;
}t_table;

int						check_args(int argc, char **argv);
void					init_table(int argc, char **argv, t_table *all);
int						memory_allocate(t_table *all);
void					init_philo(t_table *all);
int						ft_atoi(const char *str);
void					create_thread(t_table *all);
void					*party_begin(void *lol);
int						death(t_table *all, long long time);
void					eating(t_philo *monk);
void					one_philo(t_table *all);
void					sleeping(t_philo *monk);
void					thinking(t_philo *monk);
void					kill_them_all(t_table *all);
void					ft_usleep(long long time);
void					philo_print(t_table *table, t_philo *philo, char *str);
void					ft_free(t_table *all);
long long int			get_time(void);

#endif
