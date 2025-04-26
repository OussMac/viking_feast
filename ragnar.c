#include "philo.h"

void    set_end_flag(t_table *table)
{
    pthread_mutex_lock(&table->end_lock);
    table->end_feast = true;
    pthread_mutex_unlock(&table->end_lock);
}
