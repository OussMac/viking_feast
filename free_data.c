#include "philo.h"

void    print_error(char *error)
{
    int i;

    i = 0;
    printf(RED"[-] ");
    while (error[i])
    {
        write(STDOUT_FILENO, &error[i], 1);
        i++;
    }
    printf(RST"\n");
}

void    print_comm(char *comment)
{
    printf(YLW"[*] %s"RST, comment);
}

void    free_data(t_table *table)
{
    free(table->vikings);
    free(table->forks);
}

void    destroy_forks(t_table *table)
{
    int i;

    i = 0;
    while (i < table->viking_number)
    {
        pthread_mutex_destroy(&table->forks->fork + i);
        i++;
    }
}

void    clean_up(t_table *table)
{
    // destroy_forks(table);
    free_data(table);
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->end_lock);
    pthread_mutex_destroy(&table->eat_lock);
    pthread_mutex_destroy(&table->write_lock);
    pthread_mutex_destroy(&table->nbr_lock);
    pthread_mutex_destroy(&table->sleep_lock);
    pthread_mutex_destroy(&table->forks_lock);
    pthread_mutex_destroy(&table->full_lock);
}