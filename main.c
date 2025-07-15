#include "philo.h"

void	f(void)
{
	system("leaks philo");
}

int main(int argc, char *argv[])
{
	t_table	table;

	// atexit(f);

	if (parse_input(argc, argv, &table) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	if(allocate_data(&table) != EXIT_SUCCESS)
			return(print_error("Failed Allocating Resources"), EXIT_FAILURE);
	if (init_table_data(&table) != EXIT_SUCCESS)
		return (print_error("Table Initalization Failed.\n"), EXIT_FAILURE);
	// print_scene(&table);
	if (valhala_feast(&table) != EXIT_SUCCESS)
		return (clean_up(&table), print_error("Scenario Failed.\n"), EXIT_FAILURE);
	return(clean_up(&table), EXIT_SUCCESS);
}
