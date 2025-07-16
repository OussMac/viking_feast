#include "philo.h"

void    finished_meal(t_viking *viking, int *full_vikings, int nbr_of_meals)
{
    int meals_eaten;

    meals_eaten = read_shared_int(&viking->table->meals_eaten_lock, &viking->meals_eaten);
    if (nbr_of_meals != -1 && meals_eaten >= nbr_of_meals)
        *full_vikings = *full_vikings + 1;
}

bool    starvation_check(t_viking *viking)
{
    long    tm_since_lst_meal;
    long    last_meal;

    last_meal = read_shared_long(&viking->table->last_meal_lock, &viking->last_meal);
    tm_since_lst_meal = get_time(viking->table);
    if (tm_since_lst_meal >= viking->table->time_to_die)
        return (true);
    return (false);
}

static void increment_meals(t_viking *viking, int incr_amount)
{
    int temp;
    temp = read_shared_int(&viking->table->meals_eaten_lock, &viking->meals_eaten);
    temp += incr_amount;
    write_shared_int(&viking->table->meals_eaten_lock, &viking->meals_eaten, temp);
}

void    pick_up_forks(t_viking *viking)
{
    pthread_mutex_lock(&viking->left_fork->fork);
    print_action(viking, "has taken a fork");
    pthread_mutex_lock(&viking->right_fork->fork);
    print_action(viking, "has taken a fork");
}

void    viking_eating(t_viking *viking)
{
    print_action(viking, EATING);
    // set last meal
    write_shared_long(&viking->table->last_meal_lock, &viking->last_meal, get_time(viking->table));
    // set number of meals eaten
    increment_meals(viking, 1);
    // sleep time to eat
    ft_usleep(viking->table->time_to_sleep, viking->table);
    // drop forks.
    pthread_mutex_unlock(&viking->left_fork->fork);
    pthread_mutex_unlock(&viking->right_fork->fork);
}

void    viking_sleeping(t_viking *viking)
{
    print_action(viking, SLEEPING);
    ft_usleep(viking->table->time_to_sleep, viking->table);
}

void    viking_thinking(t_viking *viking)
{
    print_action(viking, THINKING);
}