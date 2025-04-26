#include "philo.h"

void    *viking_cycle(void *arg)
{
    t_viking *viking;
    
    viking = (t_viking *) arg;
    while (true)
    {
        if (viking->viking_id % 2 == 0)
            usleep(5);
        // eating

        // sleeping

        // thinking

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
            i++;
        }
    }
    return (NULL);
}

int start_scenario(t_table *table)
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