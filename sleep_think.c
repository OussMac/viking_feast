#include "philo.h"

void    viking_sleep(t_viking *viking)
{
    print_action(BLU, viking, "is sleeping");
    ft_usleep(viking->table->time_to_sleep);
}

void    viking_think(t_viking *viking)
{
    print_action(YLW, viking, "is thinking");
}
