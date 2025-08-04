#include "ft_printf.h"

int	ft_putint10(int int10)
{
	char	*a;
	int		ct;

	a = ft_itoa(int10);
	if (!a)
		return (0);
	ct = ft_strlen(a);
	ft_putstr_fd(a, 1);
	free(a);
	return (ct);
}

static int	ft_uint10len(unsigned int uint10)
{
	int	ct;

	ct = 0;
	while (uint10 > 0)
	{
		uint10 /= 10;
		ct++;
	}
	return (ct);
}

static void	ft_putuint10rec(unsigned int uint10)
{
	if (uint10 < 10)
		ft_putchar_fd((char)uint10 + 48, 1);
	else
	{
		ft_putuint10rec(uint10 / 10);
		ft_putchar_fd((char)(uint10 % 10) + 48, 1);
	}
}

int	ft_putuint10(unsigned int uint10)
{
	if (uint10 < 10)
	{
		ft_putchar_fd((char)uint10 + 48, 1);
		return (1);
	}
	ft_putuint10rec(uint10);
	return (ft_uint10len(uint10));
}
