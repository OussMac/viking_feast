#include "philo.h"

void    join_threads(t_table *table, int viking_nbr)
{
    int i;

    i = 0;
    while (i < viking_nbr)
        pthread_join(table->vikings[i++].th_id, NULL);
}

void    *viking_cycle(void *arg)
{
    t_viking *viking;
    
    viking = (t_viking *) arg;
    if (viking->viking_id % 2 == 0)
        ft_usleep(viking->table->time_to_eat / 10, viking->table);
    if (viking->table->viking_number == 1)
    {
        print_action(viking, "has taken a fork");
        return (NULL);
    }
    while (true)
    {
        if (end_feast(viking->table))
            break;
        viking_eat(viking);
        if (check_eaten(viking))
            break;
        if (end_feast(viking->table))
            break;
        viking_sleep(viking);
        if (end_feast(viking->table))
            break;
        viking_think(viking);
    }
    return (NULL);
}

void    *ragnar_monitor(void *arg)
{
    t_table *table;
    int     i;

    table = (void *)arg;
    while (true)
    {
        i = 0;
        if (end_feast(table))
            return (NULL);
        while(i < check_viking_nbr(table))
        {
            if ((get_time(table) - get_last_meal(table, i)) >= table->time_to_die)
            {
                set_end_flag(table);
                print_action(&table->vikings[i], "died");
                return (NULL);
            }
            i++;
        }
        full_vikings(table);
        ft_usleep(5, table);
    }
    return (NULL);
}

int valhala_feast(t_table *table)
{
    int i;
    int j;
    pthread_t    ragnar;

    i = 0;
    int viking_nbr = table->viking_number;
    while (i < viking_nbr)
    {
        if (pthread_create(&table->vikings[i].th_id, NULL, viking_cycle, &table->vikings[i]) != 0)
        {
            j = 0;
            set_end_flag(table);
            while (j < i)
                pthread_join(table->vikings[j++].th_id, NULL);
            return (EXIT_FAILURE);
        }
        i++;
    }
    if (pthread_create(&ragnar, NULL, ragnar_monitor, table) != 0)
        return (set_end_flag(table), join_threads(table, viking_nbr), EXIT_FAILURE);
    pthread_join(ragnar, NULL);
    join_threads(table, viking_nbr);
    return (EXIT_SUCCESS);
}
