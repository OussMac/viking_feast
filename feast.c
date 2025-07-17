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
    // handle one
    if (viking->table->viking_number == 1)
    {
        pthread_mutex_lock(&viking->left_fork->fork);
        print_action(viking, "has taken a fork");
        return (NULL);
    }
    if (viking->viking_id % 2 == 0)
        ft_usleep(1, viking->table);
    // set last meal under a mutex last meal lock
    write_shared_long(&viking->table->last_meal_lock, &viking->last_meal, get_time(viking->table));
    while (1337)
    {
        if (end_feast(viking->table))
            return (NULL);
        pick_up_forks(viking);
        viking_eating(viking);
        if (end_feast(viking->table))
            return (NULL);
        viking_sleeping(viking);
        if (end_feast(viking->table))
            return (NULL);
        viking_thinking(viking);
    }
    return (NULL);
}

int ragnar_monitor(t_table *table, int vikings_number)
{
    int     i;
    int     full_vikings;

    // new imp
    full_vikings = 0;
    while (1337)
    {
        i = 0;
        while (i < vikings_number)
        {
            if (starvation_check(&table->vikings[i]))
            {
                set_end_flag(table);
                print_action(&table->vikings[i], "died");
                return (EXIT_SUCCESS);
            }
            if (table->nbr_of_meals != -1)
                finished_meal(&table->vikings[i], &full_vikings, table->nbr_of_meals);
            i++;
        }
        if (table->nbr_of_meals != -1 && full_vikings == vikings_number)
            return (set_end_flag(table), EXIT_SUCCESS);
        ft_usleep(3, table);
    }

    return (EXIT_SUCCESS);
}

int valhala_feast(t_table *table)
{
    int i;
    int j;

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
    // monitor thread is literally the main
    ragnar_monitor(table, viking_nbr);
    join_threads(table, viking_nbr);
    return (EXIT_SUCCESS);
}
