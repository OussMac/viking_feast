#include "philo.h"

void    *viking_cycle(void *arg)
{
    t_viking *viking;
    
    viking = (t_viking *) arg;
    if (viking->viking_id % 2 == 0)
        ft_usleep(viking->table->time_to_eat / 10);
    while (true)
    {
        if (end_feast(viking->table))
            break;

        viking_eat(viking);

        if (check_eaten(viking))
            break;

       viking_sleep(viking);

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
        while(i < table->viking_number)
        {

            if ((get_time(table) - table->vikings[i].last_meal) >= table->time_to_die)
            {
                set_end_flag(table);
                print_action(RED, &table->vikings[i], "died");
                return (NULL);
            }
            i++;
            usleep(10);
        }
        usleep(800);
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
    pthread_detach(ragnar);
    while (i < viking_nbr)
        pthread_join(table->vikings[i++].th_id, NULL);
    return (EXIT_SUCCESS);
}
