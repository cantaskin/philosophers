#include "thread_deneme.h"
long long int   get_time(void)
{
    struct timeval  i;
    gettimeofday (&i, NULL);
    return ((i.tv_sec * 1000) + (i.tv_usec / 1000));
} 
void    philo_print(t_table *table, t_philo *philo, char *str)
{
    //if (table->flag_of_death)
      //  return ;
    //printf("jjj\n");
    //pthread_mutex_lock(&table->print);
    //if (table->flag_of_death)
     //   return ;
    printf("%lld %d %s\n",
        get_time() - philo->time_start, philo->id, str);
    //printf("123\n");
    //pthread_mutex_unlock(&table->print);
}
void    ft_usleep(long long time)
{
    long long   start;
    start = get_time();
    while (get_time() - start < time)
        usleep(1000000);
}
void thinking(t_philo *monk)
{
    if(monk->arg->flag_of_death)
        return ;
    philo_print(monk->arg,monk,"is thinking");
}
void sleeping(t_philo *monk)
{
    if(monk->arg->flag_of_death)
        return ;
    philo_print(monk->arg,monk,"is sleeping");
    ft_usleep(monk->time_to_sleep);
}
void one_philo(t_table *all)
{
    pthread_mutex_lock(&all->forks[all->philo->left_fork]);
    philo_print(all,all->philo,"has taken a fork");
    ft_usleep(all->time_to_die);
    philo_print(all,all->philo,"died");
    pthread_mutex_unlock(&all->forks[all->philo->left_fork]);
}
void eating(t_philo *monk)
{
    if(monk->arg->flag_of_death)
        return ;
    pthread_mutex_lock(&monk->arg->forks[monk->left_fork]);
    philo_print(monk->arg,monk,"has taken a left fork");
    pthread_mutex_lock(&monk->arg->forks[monk->right_fork]);
    philo_print(monk->arg,monk,"has taken a right fork");
    philo_print(monk->arg,monk,"is eating");
    monk->count_eat++;
    monk->last_eat = get_time();
    ft_usleep(monk->arg->time_to_eat);
    pthread_mutex_unlock(&monk->arg->forks[monk->left_fork]);
    pthread_mutex_unlock(&monk->arg->forks[monk->right_fork]);
}
void *party_begin(void *lol)
{
    int i = 0;
    t_philo *monk;
    t_table *can;

    monk =  (t_philo *)lol;
    can = monk->arg;
    if(can->count_philo == 1)
        one_philo(can);
    else if(monk->id % 2 == 0)
    {
        philo_print(monk->arg,monk,"is thinking");
        ft_usleep(50);
    }
    while(!monk->arg->flag_of_death)
    {
        if(monk->arg->count_of_lunch == monk->count_eat && monk->arg->count_of_lunch > 0)
            return (NULL);
        eating(monk);
        sleeping(monk);
        thinking(monk);
    }
	return (NULL);
}
void create_thread(t_table *all)
{
    int i;
    i = 0;
    while(i < all->count_philo)
    {
        pthread_create(&all->thread[i], NULL, &party_begin, &all->philo[i]);
        i++;
    }
    i = 0;
    while(i<all->count_philo)
    {
        pthread_join(all->thread[i], NULL);
        i++;
    }
}
void init_philo(t_table *all)
{
    int i = 0;
    while(i < all->count_philo)
    {
        all->philo[i].id = i+1;
        all->philo[i].time_to_die = all->time_to_die;
        all->philo[i].time_to_eat = all->time_to_eat;
        all->philo[i].time_to_sleep = all->time_to_sleep;
        all->philo[i].count_eat = 0;
        all->philo[i].right_fork = i;
        all->philo[i].left_fork = i + 1;
        all->philo[i].arg = all;
        if(i + 1 == all->count_philo)
            all->philo[i].left_fork = 0;
        i++;
    }
    i = 0;
   	all->time_start = get_time();
    while(i < all->count_philo)
    {
        all->philo[i].time_start = all->time_start;
        all->philo[i].last_eat = all->time_start;
        i++;
    }
}
int memory_allocate(t_table *all)
{
	int i;

	i = 0;
    if(!all)
        return (1);
    all->philo = (t_philo *)malloc(sizeof(t_philo) * all->count_philo);
    if(!all->philo)
        return (1);
    all->forks= malloc(sizeof(pthread_mutex_t) * all->count_philo);
    if(!all->forks)
        return (1);
    all->thread = malloc(sizeof(pthread_t) * all->count_philo);
    if(!all->thread)
        return (1);
	while(i < all->count_philo)
    {
        pthread_mutex_init(&all->forks[i],NULL);
        i++;
    } 
    return (0);
}
void init_table(int argc, char **argv, t_table *all)
{
    int i;
    i = 0;
    all->count_philo = atoi(argv[1]);
    all->time_to_die = atoi(argv[2]);
    all->time_to_eat = atoi(argv[3]);
    all->time_to_sleep = atoi(argv[4]);
    all->count_of_lunch = 0;
    all->flag_of_death = 0;
    if(argc == 6)
        all->count_of_lunch = atoi(argv[5]);
    all->flag_of_death = 0;
    pthread_mutex_init(&all->print,NULL);
	all->philo = NULL;
	all->forks = NULL;
}
int check_args(int argc, char **argv)
{
    if(argc < 5 && argc > 6)
    {
        printf("Argument count error\n");
        return (1);
    }
    if(atoi(argv[1]) <= 0)
    {
        printf("Philo number error\n");
        return (1);
    }
    if(atoi(argv[2]) <= 0)
    {
        printf("Time to die error\n");
        return (1);
    }
    if(atoi(argv[3]) <= 0)
    {
        printf("Time to eat error\n");
        return (1);
    }
    if(atoi(argv[4]) <= 0)
    {
        printf("Time to sleep error\n");
        return (1);
    }
    return (0);
}
int main(int argc, char **argv)
{
    t_table *all;
    all = malloc(sizeof(t_table));
    if(check_args(argc,argv))
        return(1);
    init_table(argc,argv,all);
    if(memory_allocate(all))
        return(1);  // güzel freelemedim sonradan hallet burada hepsini el ile freele 
    init_philo(all);
    create_thread(all);
}