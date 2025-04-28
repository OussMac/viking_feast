#include "philo.h"

void    print_action(char *color, t_viking *viking, char *action)
{
    pthread_mutex_lock(&viking->table->print_lock);
     if (end_feast(viking->table))
     {
        pthread_mutex_unlock(&viking->table->print_lock);
        return ;
     }
    printf("%s%ld %d %s\n"RST,color , get_time(viking->table), viking->viking_id, action);
    pthread_mutex_unlock(&viking->table->print_lock);
}

void    ft_usleep(long miliseconds)
{
    long    start_time;

    start_time = m_time();
    while ((m_time() - start_time) < miliseconds)
        usleep(100);
}

bool    end_feast(t_table *table)
{
    pthread_mutex_lock(&table->end_lock);
    if (table->end_feast)
    {
        pthread_mutex_unlock(&table->end_lock);
        return (true);
    }
    pthread_mutex_unlock(&table->end_lock);
    return (false);
}
