#include "philo.h"

void    init_locks(t_table *table)
{
    table->flags.print_flag = false;
    table->flags.end_flag = false;
    table->flags.eat_flag = false;
    table->flags.write_flag = false;
    table->flags.nbr_flag = false;
    table->flags.sleep_flag = false;
    table->flags.forks_flag = false;
    table->flags.full_flag = false;
    // new imp
    table->flags.last_meal_flag = false;
    table->flags.meals_eaten_flag = false;
}

void    clean_locks(t_table *table)
{
    if (table->flags.print_flag)
        pthread_mutex_destroy(&table->print_lock);
    if (table->flags.end_flag)
        pthread_mutex_destroy(&table->end_lock);
    if (table->flags.eat_flag)
        pthread_mutex_destroy(&table->eat_lock);
    if (table->flags.write_flag)
        pthread_mutex_destroy(&table->write_lock);
    if (table->flags.nbr_flag)
        pthread_mutex_destroy(&table->nbr_lock);
    if (table->flags.sleep_flag)
        pthread_mutex_destroy(&table->sleep_lock);
    if (table->flags.forks_flag)
        pthread_mutex_destroy(&table->forks_lock);
    if (table->flags.full_flag)
        pthread_mutex_destroy(&table->full_lock);
    // new imp
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

    if (pthread_mutex_init(&table->eat_lock, NULL) == 0)
        table->flags.eat_flag = true;
    else
        *one_failed = true;

    if (pthread_mutex_init(&table->write_lock, NULL) == 0)
        table->flags.write_flag = true;
    else
        *one_failed = true;
    // new imp -----------------------------------------------------------
    if (pthread_mutex_init(&table->last_meal_lock, NULL) == 0)
        table->flags.last_meal_flag = true;
    else
        *one_failed = true;
    if (pthread_mutex_init(&table->meals_eaten_lock, NULL) == 0)
        table->flags.meals_eaten_flag = true;
    else
        *one_failed = true;
}

static void second_block(t_table *table, bool *one_failed)
{
    if (pthread_mutex_init(&table->nbr_lock, NULL) == 0)
        table->flags.nbr_flag = true;
    else
        *one_failed = true;

    if (pthread_mutex_init(&table->sleep_lock, NULL) == 0)
        table->flags.sleep_flag = true;
    else
        *one_failed = true;

    if (pthread_mutex_init(&table->forks_lock, NULL) == 0)
        table->flags.forks_flag = true;
    else
        *one_failed = true;

    if (pthread_mutex_init(&table->full_lock, NULL) == 0)
        table->flags.full_flag = true;
    else
        *one_failed = true;
}

int allocate_locks(t_table *table)
{
    bool    one_failed;

    one_failed = false;
    first_block(table, &one_failed);
    second_block(table, &one_failed);
    if (one_failed)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
