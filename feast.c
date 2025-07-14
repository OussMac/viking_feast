#include "philo.h"

void    *viking_cycle(void *arg)
{
    t_viking *viking;
    
    viking = (t_viking *) arg;
    if (viking->viking_id % 2 == 0)
        ft_usleep(viking->table->time_to_eat / 10, viking->table);
    if (viking->table->viking_number == 1)
    {
        print_action(MGN, viking, "has taken a fork");
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
        while(i <= check_viking_nbr(table))
        {
            if ((get_time(table) - get_last_meal(table, i)) >= table->time_to_die)
            {
                set_end_flag(table);
                print_action(RED, &table->vikings[i], "died");
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
    pthread_t    ragnar;

    i = 0;
    int viking_nbr = table->viking_number;
    while (i < viking_nbr)
    {
        pthread_create(&table->vikings[i].th_id, NULL, viking_cycle, &table->vikings[i]);
        i++;
    }
    i = 0;
    pthread_create(&ragnar, NULL, ragnar_monitor, table);
    pthread_join(ragnar, NULL);
    while (i < viking_nbr)
        pthread_join(table->vikings[i++].th_id, NULL);
    return (EXIT_SUCCESS);
}
