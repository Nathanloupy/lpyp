#include "lpyp.h"

int	main(int argc, char **argv)
{
	if (argc > 1)
		parse_args(argc, argv);
	else
		ft_putstr_fd("Please provide some arguments.\n", 1);
	return (0);
} 