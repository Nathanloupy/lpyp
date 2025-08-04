#include "ft_printf.h"

int	ft_putformat(va_list args, char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putptr(va_arg(args, unsigned long long)));
	else if (format == 'd' || format == 'i')
		return (ft_putint10(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putuint10(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_putuint16low(va_arg(args, unsigned int)));
	else if (format == 'X')
		return (ft_putuint16up(va_arg(args, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	int		ct;

	ct = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			ct += ft_putformat(args, s[++i]);
		}
		else
			ct += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (ct);
}
