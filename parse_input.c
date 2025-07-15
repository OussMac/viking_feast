#include "philo.h"


static bool	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (true);
	return (false);
}

static bool	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

static bool	syntax_parser(char *str)
{
	int	i;

	i = 0;
	if (!ft_issign(str[i]) && !ft_isdigit(str[i]))
		return (true);
	if (ft_issign(str[i]) && !ft_isdigit(str[i + 1]))
		return (true);
	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

long	ft_atol(const char *str)
{
	int		i;
	long	pow;
	int		s;

	i = 0;
	s = 1;
	pow = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		pow = (pow * 10) + (str[i] - 48);
		i++;
	}
	return (pow * s);
}

int parse_input(int argc, char *argv[], t_table *table)
{
    int     i;
    long    nbr;

    if (argc != 5 && argc != 6)
        return (print_comm("Usage: ./philo <philo> <die> <eat> <sleep> [meals]\n"), EXIT_FAILURE);
    i = 1;
    while (argv[i])
    {
        if (syntax_parser(argv[i]))
            return (print_error("Invalid Number Syntax.\n"), EXIT_FAILURE);
		nbr = ft_atol(argv[i]);
        if (!(nbr >= INT_MIN && nbr <= INT_MAX) || nbr <= 0)
            return (print_error("Invalid Number Range.\n"), EXIT_FAILURE);
		if (i == 1 && nbr > 200)
			return (print_error("Too Many Philosophers.\n"), EXIT_FAILURE);
        i++;
    }
	general_table(argc, argv, table);
    return (EXIT_SUCCESS);
}
