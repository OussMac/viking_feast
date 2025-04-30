#include "philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (i < n && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

void    print_action(char *color, t_viking *viking, char *action)
{
    pthread_mutex_lock(&viking->table->print_lock);
    if (end_feast(viking->table) && ft_strncmp(action , "died", 4) != 0)
    {
        pthread_mutex_unlock(&viking->table->print_lock);
        return ;
    }
    printf("%s%ld %d %s\n"RST,color , get_time(viking->table), viking->viking_id, action);
    pthread_mutex_unlock(&viking->table->print_lock);
}

void    ft_usleep(long miliseconds, t_table *table)
{
    long    start_time;

    start_time = m_time();
    while ((m_time() - start_time) < miliseconds)
    {
        if (end_feast(table))  
            return ;
        usleep(100);
    }
}

bool    end_feast(t_table *table)
{
    pthread_mutex_lock(&table->end_lock);
    if (table->end_feast)
    {
        pthread_mutex_unlock(&table->end_lock);
        return (true);
    }
    pthread_mutex_unlock(&table->end_lock);
    return (false);
}
