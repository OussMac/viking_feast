#include "philo.h"

void    *viking_cycle(void *arg)
{
    t_viking *viking;
    
    viking = (t_viking *) arg;
    while (true)
    {
       // [STOP CHECK]
        // lock(m_stop)
        // if (global stop flag is set) {
        //     unlock(m_stop)
        //     break out of loop and exit thread
        // }
        // unlock(m_stop)

        // [TAKE FORKS]
        // lock(left_fork)
        // print_timestamped("has taken a fork")
        // lock(right_fork)
        // print_timestamped("has taken a fork")

        // [EAT]
        // lock(m_time)
        //   last_meal = current_timestamp()
        // unlock(m_time)
        // print_timestamped("is eating")
        // usleep(t_eat)
        // unlock(left_fork)
        // unlock(right_fork)

        // [MEAL COUNT & TERMINATION]
        // increment personal_eat_count
        // if (personal_eat_count == required_eats) {
        //     lock(m_stop)
        //       increment(global_finished_count)
        //       if (global_finished_count == n_philo) {
        //           set global stop flag
        //       }
        //     unlock(m_stop)
        //     break out of loop and exit thread
        // }

        // [SLEEP]
        // print_timestamped("is sleeping")
        // usleep(t_sleep)

        // [THINK]
        // print_timestamped("is thinking")

    }
    return (NULL);
}

void    *watcher(void *arg)
{
    t_table *table;
    int     i;

    table = (void *)arg;
    while (true)
    {
        i = 0;
        while(i < table->viking_number)
        {
            // for each philosopher p in philos[]:
        //     lock(p->m_time)
        //         now = current_timestamp()
        //         if (now - p->last_meal > t_die) {
        //             lock(info->m_stop)
        //               set global stop flag
        //             unlock(info->m_stop)
        //             print_timestamped(p, "died")
        //             unlock(p->m_time)
        //             return NULL  // end watcher
        //         }
        //     unlock(p->m_time)

        // usleep(short_interval)  // avoid busy-spin
            i++;
        }
    }
    return (NULL);
}

int valhala_feast(t_table *table)
{
    int i;
    pthread_t    ragnar;

    i = 0;
    int viking_nbr = table->viking_number;
    while (i < viking_nbr)
    {
        pthread_create(&table->vikings[i].th_id, NULL, viking_cycle, &table->vikings[i]);
        i++;
    }
    i = 0;
    pthread_create(&ragnar, NULL, watcher, table);
    pthread_detach(ragnar);
    while (i < viking_nbr)
        pthread_join(table->vikings[i++].th_id, NULL);
    return (EXIT_SUCCESS);
}
