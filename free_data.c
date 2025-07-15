#include "philo.h"


// probably didnt use this one will check later.
void    ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
}

void    print_error(char *error)
{
    int i;

    i = 0;
    write(STDERR_FILENO, RED, 5);
    write(STDERR_FILENO, "[-]", 3);
    while (error[i])
    {
        write(STDERR_FILENO, &error[i], 1);
        i++;
    }
    write(STDERR_FILENO, RST, 5);
}

void    print_comm(char *comment)
{
    printf(YLW"[*] %s"RST"\n", comment);
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
        pthread_mutex_destroy(&table->forks[i].fork);
        i++;
    }
}

void    clean_up(t_table *table)
{
    destroy_forks(table);
    free_data(table);
    clean_locks(table);
}
