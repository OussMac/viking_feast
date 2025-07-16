#include "philo.h"

// read and write long.
void write_shared_long(pthread_mutex_t *lock, long *var, long value)
{
    pthread_mutex_lock(lock);
    *var = value;
    pthread_mutex_unlock(lock);
}
long read_shared_long(pthread_mutex_t *lock, long *var)
{
    long value;

    pthread_mutex_lock(lock);
    value = *var;
    pthread_mutex_unlock(lock);
    return value;
}
//read and write int.
void write_shared_int(pthread_mutex_t *lock, int *var, int value)
{
    pthread_mutex_lock(lock);
    *var = value;
    pthread_mutex_unlock(lock);
}

int read_shared_int(pthread_mutex_t *lock, int *var)
{
    int value;
    pthread_mutex_lock(lock);
    value = *var;
    pthread_mutex_unlock(lock);
    return value;
}
// read and write bool.

void write_shared_bool(pthread_mutex_t *lock, bool *var, bool value)
{
    pthread_mutex_lock(lock);
    *var = value;
    pthread_mutex_unlock(lock);
}

bool read_shared_bool(pthread_mutex_t *lock, bool *var)
{
    bool value;
    pthread_mutex_lock(lock);
    value = *var;
    pthread_mutex_unlock(lock);
    return value;
}
