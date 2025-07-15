#include "philo.h"

void    viking_sleep(t_viking *viking)
{
    print_action(viking, "is sleeping");
    ft_usleep(viking->table->time_to_sleep, viking->table);
}

void    viking_think(t_viking *viking)
{
    print_action(viking, "is thinking");
}
