#include "lpyp.h"

static void	print_option_usage(t_lpyp_options *option)
{
	ft_putstr_fd(" [", 1);
	
	if (option->short_name && ft_isalpha(option->short_name))
	{
		ft_putchar_fd('-', 1);
		ft_putchar_fd(option->short_name, 1);
	}
	else if (option->long_name)
	{
		ft_putstr_fd("--", 1);
		ft_putstr_fd(option->long_name, 1);
	}
	
	if (option->flags & LPYP_REQUIRED_ARG)
	{
		if (option->long_name && !(option->short_name && ft_isalpha(option->short_name)))
			ft_putchar_fd('=', 1);
		else
			ft_putchar_fd(' ', 1);
		if (option->arg_name)
			ft_putstr_fd(option->arg_name, 1);
		else
			ft_putstr_fd("ARG", 1);
	}
	else if (option->flags & LPYP_OPTIONAL_ARG)
	{
		ft_putchar_fd('[', 1);
		if (option->long_name && !(option->short_name && ft_isalpha(option->short_name)))
			ft_putchar_fd('=', 1);
		else
			ft_putchar_fd(' ', 1);
		if (option->arg_name)
			ft_putstr_fd(option->arg_name, 1);
		else
			ft_putstr_fd("ARG", 1);
		ft_putchar_fd(']', 1);
	}
	
	ft_putchar_fd(']', 1);
}

/* Function to print usage information */
int	lpyp_usage(t_lpyp_options *options, char *program_name)
{
	int	i;
	
	ft_putstr_fd("Usage: ", 1);
	if (program_name)
		ft_putstr_fd(program_name, 1);
	else
		ft_putstr_fd("program", 1);
	
	i = 0;
	while (options[i].key != 0)
	{
		if (options[i].key != LPYP_KEY_ARG)
			print_option_usage(&options[i]);
		i++;
	}
	
	i = 0;
	while (options[i].key != 0)
	{
		if (options[i].key == LPYP_KEY_ARG)
		{
			ft_putstr_fd(" ", 1);
			if (options[i].arg_name)
				ft_putstr_fd(options[i].arg_name, 1);
			else
				ft_putstr_fd("ARGS", 1);
			break;
		}
		i++;
	}
	
	ft_putstr_fd("\n", 1);
	return (0);
}

static int	calculate_option_width(t_lpyp_options *option)
{
	int	width;

	width = 0;
	if (option->short_name && ft_isalpha(option->short_name))
		width += 2;
	if (option->short_name && ft_isalpha(option->short_name) && option->long_name)
		width += 2;
	else if (!option->short_name || !ft_isalpha(option->short_name))
		width += 4;
	if (option->long_name)
		width += 2 + ft_strlen(option->long_name);
	if (option->flags & LPYP_REQUIRED_ARG)
	{
		if (option->long_name && !(option->short_name && ft_isalpha(option->short_name)))
			width += 1;
		else
			width += 1;
		if (option->arg_name)
			width += ft_strlen(option->arg_name);
		else
			width += 3;
	}
	else if (option->flags & LPYP_OPTIONAL_ARG)
	{
		if (option->long_name && !(option->short_name && ft_isalpha(option->short_name)))
			width += 1;
		else
			width += 1;
		width += 2;
		if (option->arg_name)
			width += ft_strlen(option->arg_name);
		else
			width += 3;
	}
	return (width);
}

static void	print_option_line(t_lpyp_options *option, int max_width)
{
	int	current_width;

	current_width = 0;
	ft_putstr_fd("  ", 1);
	
	if (option->short_name && ft_isalpha(option->short_name))
	{
		ft_putchar_fd('-', 1);
		ft_putchar_fd(option->short_name, 1);
		current_width += 2;
	}
	
	if (option->short_name && ft_isalpha(option->short_name) && option->long_name)
	{
		ft_putstr_fd(", ", 1);
		current_width += 2;
	}
	else if (!option->short_name || !ft_isalpha(option->short_name))
	{
		ft_putstr_fd("    ", 1);
		current_width += 4;
	}
	
	if (option->long_name)
	{
		ft_putstr_fd("--", 1);
		ft_putstr_fd(option->long_name, 1);
		current_width += 2 + ft_strlen(option->long_name);
	}
	
	if (option->flags & LPYP_REQUIRED_ARG)
	{
		if (option->long_name && !(option->short_name && ft_isalpha(option->short_name)))
			ft_putchar_fd('=', 1);
		else
			ft_putchar_fd(' ', 1);
		current_width += 1;
		if (option->arg_name)
		{
			ft_putstr_fd(option->arg_name, 1);
			current_width += ft_strlen(option->arg_name);
		}
		else
		{
			ft_putstr_fd("ARG", 1);
			current_width += 3;
		}
	}
	else if (option->flags & LPYP_OPTIONAL_ARG)
	{
		if (option->long_name && !(option->short_name && ft_isalpha(option->short_name)))
			ft_putchar_fd('=', 1);
		else
			ft_putchar_fd(' ', 1);
		ft_putchar_fd('[', 1);
		current_width += 2;
		if (option->arg_name)
		{
			ft_putstr_fd(option->arg_name, 1);
			current_width += ft_strlen(option->arg_name);
		}
		else
		{
			ft_putstr_fd("ARG", 1);
			current_width += 3;
		}
		ft_putchar_fd(']', 1);
		current_width += 1;
	}
	
	while (current_width < max_width + 2)
	{
		ft_putchar_fd(' ', 1);
		current_width++;
	}
	
	if (option->description)
		ft_putstr_fd(option->description, 1);
	
	ft_putchar_fd('\n', 1);
}

/* Function to print detailed help */
int	lpyp_help(t_lpyp_options *options, char *program_name, char *description)
{
	int	i;
	int	max_width;
	int	current_width;
	
	lpyp_usage(options, program_name);
	
	if (description)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(description, 1);
		ft_putstr_fd("\n", 1);
	}
	
	max_width = 0;
	i = 0;
	while (options[i].key != 0)
	{
		if (options[i].key != LPYP_KEY_ARG)
		{
			current_width = calculate_option_width(&options[i]);
			if (current_width > max_width)
				max_width = current_width;
		}
		i++;
	}
	
	ft_putstr_fd("\nOptions:\n", 1);
	i = 0;
	while (options[i].key != 0)
	{
		if (options[i].key != LPYP_KEY_ARG)
			print_option_line(&options[i], max_width);
		i++;
	}
	
	return (0);
}
