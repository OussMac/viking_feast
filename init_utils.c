#include "philo.h"

void    init_locks(t_table *table)
{
    table->flags.print_flag = false;
    table->flags.end_flag = false;
    table->flags.last_meal_flag = false;
    table->flags.meals_eaten_flag = false;
}

void    clean_locks(t_table *table)
{
    if (table->flags.print_flag)
        pthread_mutex_destroy(&table->print_lock);
    if (table->flags.end_flag)
        pthread_mutex_destroy(&table->end_lock);
    if (table->flags.last_meal_flag)
        pthread_mutex_destroy(&table->last_meal_lock);
    if (table->flags.meals_eaten_flag)
        pthread_mutex_destroy(&table->meals_eaten_lock);
}

static void first_block(t_table *table, bool *one_failed)
{
    if (pthread_mutex_init(&table->print_lock, NULL) == 0)
        table->flags.print_flag = true;
    else
        *one_failed = true;
    if (pthread_mutex_init(&table->end_lock, NULL) == 0)
        table->flags.end_flag = true;
    else
        *one_failed = true;
    if (pthread_mutex_init(&table->last_meal_lock, NULL) == 0)
        table->flags.last_meal_flag = true;
    else
        *one_failed = true;
    if (pthread_mutex_init(&table->meals_eaten_lock, NULL) == 0)
        table->flags.meals_eaten_flag = true;
    else
        *one_failed = true;
}

int allocate_locks(t_table *table)
{
    bool    one_failed;

    one_failed = false;
    first_block(table, &one_failed);
    if (one_failed)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
