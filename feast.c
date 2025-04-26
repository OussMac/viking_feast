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

void    *watcher(void *arg)
{
    t_table *table;
    int     i;

    table = (void *)arg;
    while (true)
    {
        i = 0;
        while(i < table->viking_number)
        {
            // for each philosopher p in philos[]:
        //     lock(p->m_time)
        //         now = current_timestamp()
        //         if (now - p->last_meal > t_die) {
        //             lock(info->m_stop)
        //               set global stop flag
        //             unlock(info->m_stop)
        //             print_timestamped(p, "died")
        //             unlock(p->m_time)
        //             return NULL  // end watcher
        //         }
        //     unlock(p->m_time)

        // usleep(short_interval)  // avoid busy-spin
            i++;
        }
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
    pthread_create(&ragnar, NULL, watcher, table);
    pthread_detach(ragnar);
    while (i < viking_nbr)
        pthread_join(table->vikings[i++].th_id, NULL);
    return (EXIT_SUCCESS);
}
