#include "philo.h"

bool    check_forks(t_viking *viking)
{
    pthread_mutex_lock(&viking->table->forks_lock);
    if (viking->left_fork->fork_id < viking->right_fork->fork_id)
    {
        pthread_mutex_unlock(&viking->table->forks_lock);
        return(true);
    }
    pthread_mutex_unlock(&viking->table->forks_lock);
    return (false);
}

static void pick_up_forks(t_viking *viking)
{
    // if (check_forks(viking)) // problem is fork id have value 0 and not initalized correctly
    // {
    //     pthread_mutex_lock(&viking->left_fork->fork);
    //     print_action(MGN, viking, "has taken a fork");
    //     pthread_mutex_lock(&viking->right_fork->fork);
    //     print_action(CYN, viking, "has taken a fork");
    // } 
    // else
    // {
    //     pthread_mutex_lock(&viking->right_fork->fork);
    //     print_action(CYN, viking, "has taken a fork");
    //     pthread_mutex_lock(&viking->left_fork->fork);
    //     print_action(MGN, viking, "has taken a fork");
    // }
    pthread_mutex_lock(&viking->left_fork->fork);
    print_action(MGN, viking, "has taken a fork");
    pthread_mutex_lock(&viking->right_fork->fork);
    print_action(CYN, viking, "has taken a fork");
}

static void v_eating(t_viking *viking)
{
    print_action(GRN, viking, "is eating");

    // sleep the amount of eating
    ft_usleep(viking->table->time_to_eat, viking->table);
    
    // set last meal time
    pthread_mutex_lock(&viking->table->eat_lock);
    viking->last_meal = get_time(viking->table);
    pthread_mutex_unlock(&viking->table->eat_lock);

    
    pthread_mutex_unlock(&viking->left_fork->fork);
    pthread_mutex_unlock(&viking->right_fork->fork);

    // update meals eaten (only affected by one thread so no need to lock)
    viking->meals_eaten++;
}

bool    check_eaten(t_viking *viking)
{
    pthread_mutex_lock(&viking->table->nbr_lock);
    if (viking->table->nbr_of_meals != -1 && viking->meals_eaten >= viking->table->nbr_of_meals)
    {
        pthread_mutex_lock(&viking->table->full_lock);
        viking->table->viking_number--;
        pthread_mutex_unlock(&viking->table->full_lock);
        
        pthread_mutex_unlock(&viking->table->nbr_lock);
        return (true);
    }
    pthread_mutex_unlock(&viking->table->nbr_lock);
    return (false);
}

void    viking_eat(t_viking *viking)
{
    // [TAKE FORKS]
    pick_up_forks(viking);
    // [EAT]
    v_eating(viking);
}