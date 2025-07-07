#include "lpyp.h"

void	parse_args(int argc, char **argv)
{
	int	i;

	i = 0;
	ft_putstr_fd("Parsing arguments:\n", 1);
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
} 