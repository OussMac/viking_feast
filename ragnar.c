#include "philo.h"

void    set_end_flag(t_table *table)
{
    pthread_mutex_lock(&table->end_lock);
    table->end_feast = true;
    pthread_mutex_unlock(&table->end_lock);
}

void full_vikings(t_table *table)
{
    pthread_mutex_lock(&table->full_lock);
    if (table->viking_number <= 0)
        set_end_flag(table);
    pthread_mutex_unlock(&table->full_lock);
}
int check_viking_nbr(t_table *table)
{
    int ret;
    pthread_mutex_lock(&table->full_lock);
    ret = table->viking_number;
    pthread_mutex_unlock(&table->full_lock);
    return (ret);
}

long    get_last_meal(t_table *table, int i)
{
    long    ret;
    pthread_mutex_lock(&table->eat_lock);
    ret = table->vikings[i].last_meal;
    pthread_mutex_unlock(&table->eat_lock);
    return (ret);
}