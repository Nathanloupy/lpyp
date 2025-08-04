#include "ft_printf.h"

void	ft_create_base(char base[16], int upcase)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (i < 10)
			base[i] = '0' + i;
		else
		{
			if (upcase)
				base[i] = 'A' + i % 10;
			else
				base[i] = 'a' + i % 10;
		}
		i++;
	}
}

static void	ft_puthex_nb(unsigned int uint16, char base[16])
{
	if (uint16 < 16)
		ft_putchar(base[uint16]);
	else
	{
		ft_puthex_nb(uint16 / 16, base);
		ft_puthex_nb(uint16 % 16, base);
	}
}

static int	ft_uint16len(unsigned int uint16)
{
	int	ct;

	ct = 0;
	if (uint16 == 0)
		return (1);
	while (uint16 > 0)
	{
		uint16 /= 16;
		ct++;
	}
	return (ct);
}

int	ft_putuint16low(unsigned int uint16)
{
	char	base[16];

	ft_create_base(base, 0);
	ft_puthex_nb(uint16, base);
	return (ft_uint16len(uint16));
}

int	ft_putuint16up(unsigned int uint16)
{
	char	base[16];

	ft_create_base(base, 1);
	ft_puthex_nb(uint16, base);
	return (ft_uint16len(uint16));
}
