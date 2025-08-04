#pragma once

# include "../libft.h"
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		ft_putformat(va_list args, char format);
void	ft_create_base(char base[16], int upcase);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putptr(unsigned long long value);
int		ft_putint10(int int10);
int		ft_putuint10(unsigned int uint10);
int		ft_putuint16low(unsigned int uint16);
int		ft_putuint16up(unsigned int uint16);
