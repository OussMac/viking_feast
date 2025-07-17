#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // for printf
# include <stdlib.h> // for malloc, free 
# include <unistd.h> // for usleep
# include <sys/time.h> // for gettimeofday
# include <pthread.h> // pthread_create, pthread_join...
# include <stdbool.h> // for boolean flags
# include <limits.h> // for overflow check

// Text colors
# define RED "\e[31m"
# define GRN "\e[32m"
# define BLU "\e[34m"
# define YLW "\e[33m"
# define MGN "\e[35m"
# define CYN "\e[36m"
# define RST "\e[97m"

// Actions.
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

// # define gettimeofday(...) -1
// # define malloc(...) NULL
// # define pthread_mutex_init(...) 1

typedef struct s_lock_flags
{
    bool    print_flag;
    bool    end_flag;
    bool    last_meal_flag;
    bool    meals_eaten_flag;

}   t_lock_flags;


// Table type exists
typedef struct s_table t_table;

// Fork object
typedef struct s_fork
{
    int             fork_id;
    pthread_mutex_t fork;
}   t_fork;


// Viking object
typedef struct s_viking
{
    int         viking_id;
    pthread_t   th_id;

    long        last_meal;
    int         meals_eaten;


    t_fork      *left_fork;
    t_fork      *right_fork;
    t_table     *table;

    bool full;
}   t_viking;

// Table object
typedef struct s_table
{
    bool    end_feast;
    int     viking_number;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;

    int     nbr_of_meals;
    long    start;

    t_fork  *forks;
    t_viking *vikings;

    pthread_mutex_t print_lock;
    pthread_mutex_t end_lock;
    pthread_mutex_t last_meal_lock;
    pthread_mutex_t meals_eaten_lock;
    t_lock_flags    flags;
} t_table;

// readers and writers
void write_shared_long(pthread_mutex_t *lock, long *var, long value);
long read_shared_long(pthread_mutex_t *lock, long *var);
void write_shared_int(pthread_mutex_t *lock, int *var, int value);
int read_shared_int(pthread_mutex_t *lock, int *var);
void write_shared_bool(pthread_mutex_t *lock, bool *var, bool value);
bool read_shared_bool(pthread_mutex_t *lock, bool *var);

// food diagnosis.
void    finished_meal(t_viking *viking, int *full_vikings, int nbr_of_meals);
bool    starvation_check(t_viking *viking);

// new life
void    viking_eating(t_viking *viking);
void    viking_sleeping(t_viking *viking);
void    viking_thinking(t_viking *viking);

// parsing and input.
int     parse_input(int argc, char *argv[], t_table *table);
int     general_table(int argc , char *argv[],t_table *table);
int     init_table_data(t_table *table);
long	ft_atol(const char *str);

// allocate_data
int     allocate_data(t_table *table);
void    init_locks(t_table *table);
int     allocate_locks(t_table *table);
int     stack_data(t_table *table);
void    free_data(t_table *table);
void    clean_locks(t_table *table);
void    clean_up(t_table *table);

// Scenario utils
void    print_action(t_viking *viking, char *action);

// Start scenario
int     valhala_feast(t_table *table);
void    *viking_cycle(void *arg);

// Ragnar utils
void    set_end_flag(t_table *table);
void    full_vikings(t_table *table);
int     check_viking_nbr(t_table *table);
long    get_last_meal(t_table *table, int i);

// Check end_sim flag
bool    end_feast(t_table *table);

// Get time in Miliseconds.
long    m_time(void);
// Time since start (ms).
long    get_time(t_table *table); // time since start
// usleep in miliseconds
void    ft_usleep(long miliseconds, t_table *table);

// error handling
void    print_error(char *error);
void    print_comm(char *comment);

// for debuging
void    print_scene(t_table *table);


#endif // PHILO_H