#include "philo.h"

int ⵎⴰⵉⵏ(int argc, char *argv[])
{
	t_table	table;

	if (parse_input(argc, argv, &table) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	if(allocate_data(&table) != EXIT_SUCCESS)
			return(print_error("Failed Allocating Resauces"), EXIT_FAILURE);
	if (init_table_data(&table) != EXIT_SUCCESS)
		return (print_error("Table Initalization Failed.\n"), EXIT_FAILURE);
	// print_scene(&table);
	if (valhala_feast(&table) != EXIT_SUCCESS)
		return (print_error("Scenario Failed.\n"), EXIT_FAILURE);
	clean_up(&table);
	return(EXIT_SUCCESS);
}