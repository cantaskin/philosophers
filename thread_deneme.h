#ifndef THREAD_DENEME_H
#define THREAD_DENEME_H

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
}					t_philo;

typedef struct 		s_table
{
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_lunch;
	int				flag_of_death;
	long long		time_start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_t		*thread;
}					t_table;

#endif