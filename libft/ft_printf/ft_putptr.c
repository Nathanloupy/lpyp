#include "ft_printf.h"

static void	ft_putulong16(unsigned long long ulong16, char base[16])
{
	if (ulong16 < 16)
		ft_putchar(base[ulong16]);
	else
	{
		ft_putulong16(ulong16 / 16, base);
		ft_putulong16(ulong16 % 16, base);
	}
}

static int	ft_ulong16len(unsigned long long ulong16)
{
	int	ct;

	ct = 0;
	if (ulong16 == 0)
		return (1);
	while (ulong16 > 0)
	{
		ulong16 /= 16;
		ct++;
	}
	return (ct);
}

int	ft_putptr(unsigned long long value)
{
	int		ct;
	char	base[16];

	ct = 0;
	if (value == 0)
		ct += ft_putstr("0x0");
	else
	{
		ct += ft_putstr("0x");
		ft_create_base(base, 0);
		ft_putulong16(value, base);
		ct += ft_ulong16len(value);
	}
	return (ct);
}
