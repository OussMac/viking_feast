#include "philo.h"

int general_table(int argc , char *argv[],t_table *table)
{
    table->end_feast = false;
    table->viking_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->nbr_of_meals = ft_atol(argv[5]);
	else
		table->nbr_of_meals = -1;
    table->start = m_time();
    if (table->start == -1)
        return(EXIT_FAILURE);
    table->forks = NULL;
    table->vikings = NULL;
    return (EXIT_SUCCESS);
}

long    m_time(void)
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
        return (print_error("Failed To Get Time.\n"), -1);
    return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long    get_time(t_table *table)
{
    return (m_time() - table->start);
}

int allocate_data(t_table *table)
{
    table->vikings = malloc(table->viking_number * sizeof(t_viking));
    if (!table->vikings)
        return(EXIT_FAILURE);
    table->forks = malloc(table->viking_number * sizeof(t_fork));
    if (!table->forks)
        return(free(table->vikings), EXIT_FAILURE);
    init_locks(table);
    if (allocate_locks(table) != EXIT_SUCCESS)
        return (free_data(table), clean_locks(table), EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

int init_table_data( t_table *table)
{
    int i;

    i = 0;
    while (i < table->viking_number)
    {
        // initing philos
        table->vikings[i].viking_id = i + 1;
        table->vikings[i].meals_eaten = 0;
        table->vikings[i].last_meal = get_time(table);
        table->vikings[i].left_fork = &table->forks[i];
        table->vikings[i].right_fork = &table->forks[(i + 1) % table->viking_number];
        table->vikings[i].table = table;
        table->vikings[i].full = false;
        // initing forks
        table->vikings[i].left_fork->fork_id = i;
        table->vikings[i].right_fork->fork_id = (i + 1) % table->viking_number;
        if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i].fork);
            return (free_data(table), clean_locks(table), EXIT_FAILURE);
        }
        i++;
    }
    return(EXIT_SUCCESS);
}
