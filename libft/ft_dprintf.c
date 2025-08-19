#include "ft_dprintf.h"

static int	ft_write_fd(int fd, const void *buf, size_t count)
{
	ssize_t	result;

	if (count == 0)
		return (0);
	result = write(fd, buf, count);
	if (result == -1)
		return (-1);
	return ((int)result);
}

static int	ft_putchar_fd_count(char c, int fd)
{
	return (ft_write_fd(fd, &c, 1));
}

static int	ft_putstr_fd_count(char *str, int fd)
{
	int	len;

	if (!str)
		return (ft_write_fd(fd, "(null)", 6));
	len = 0;
	while (str[len])
		len++;
	return (ft_write_fd(fd, str, len));
}

static int	ft_putnbr_recursive(int n, int fd)
{
	int	result = 0;

	if (n == -2147483648)
		return (ft_write_fd(fd, "-2147483648", 11));
	if (n < 0)
	{
		result = ft_write_fd(fd, "-", 1);
		if (result == -1)
			return (-1);
		n = -n;
	}
	if (n >= 10)
	{
		result = ft_putnbr_recursive(n / 10, fd);
		if (result == -1)
			return (-1);
	}
	int temp = ft_write_fd(fd, &(char){'0' + (n % 10)}, 1);
	if (temp == -1)
		return (-1);
	return (result + temp);
}

static int	ft_putint10_fd(int int10, int fd)
{
	int	result;

	if (int10 == 0)
		return (ft_write_fd(fd, "0", 1));
	result = ft_putnbr_recursive(int10, fd);
	if (result == -1)
		return (-1);
	return (result);
}

static int	ft_putunbr_recursive(unsigned int n, int fd)
{
	int	result = 0;

	if (n >= 10)
	{
		result = ft_putunbr_recursive(n / 10, fd);
		if (result == -1)
			return (-1);
	}
	int temp = ft_write_fd(fd, &(char){'0' + (n % 10)}, 1);
	if (temp == -1)
		return (-1);
	return (result + temp);
}

static int	ft_putuint10_fd(unsigned int uint10, int fd)
{
	int	result;

	if (uint10 == 0)
		return (ft_write_fd(fd, "0", 1));
	result = ft_putunbr_recursive(uint10, fd);
	if (result == -1)
		return (-1);
	return (result);
}

static int	ft_puthex_nb_fd(unsigned int uint16, const char *base, int fd)
{
	int	result = 0;

	if (uint16 < 16)
		return (ft_write_fd(fd, &base[uint16], 1));
	else
	{
		result = ft_puthex_nb_fd(uint16 / 16, base, fd);
		if (result == -1)
			return (-1);
		int temp = ft_puthex_nb_fd(uint16 % 16, base, fd);
		if (temp == -1)
			return (-1);
		return (result + temp);
	}
}

static int	ft_putuint16low_fd(unsigned int uint16, int fd)
{
	int	result;

	if (uint16 == 0)
		return (ft_write_fd(fd, "0", 1));
	result = ft_puthex_nb_fd(uint16, HEX_BASE_LOWER, fd);
	if (result == -1)
		return (-1);
	return (result);
}

static int	ft_putuint16up_fd(unsigned int uint16, int fd)
{
	int	result;

	if (uint16 == 0)
		return (ft_write_fd(fd, "0", 1));
	result = ft_puthex_nb_fd(uint16, HEX_BASE_UPPER, fd);
	if (result == -1)
		return (-1);
	return (result);
}

static int	ft_puthex_nb_ptr_fd(unsigned long long value, const char *base, int fd)
{
	int	result = 0;

	if (value < 16)
		return (ft_write_fd(fd, &base[value], 1));
	else
	{
		result = ft_puthex_nb_ptr_fd(value / 16, base, fd);
		if (result == -1)
			return (-1);
		int temp = ft_puthex_nb_ptr_fd(value % 16, base, fd);
		if (temp == -1)
			return (-1);
		return (result + temp);
	}
}

static int	ft_putptr_fd(unsigned long long value, int fd)
{
	int		result;

	if (value == 0)
		return (ft_write_fd(fd, "0x0", 3));
	if (ft_write_fd(fd, "0x", 2) == -1)
		return (-1);
	result = ft_puthex_nb_ptr_fd(value, HEX_BASE_LOWER, fd);
	if (result == -1)
		return (-1);
	return (result + 2);
}

static int	ft_putformat_fd(va_list args, char format, int fd)
{
	int	result = 0;

	if (format == 'c')
		result = ft_putchar_fd_count(va_arg(args, int), fd);
	else if (format == 's')
		result = ft_putstr_fd_count(va_arg(args, char *), fd);
	else if (format == 'p')
		result = ft_putptr_fd(va_arg(args, unsigned long long), fd);
	else if (format == 'd' || format == 'i')
		result = ft_putint10_fd(va_arg(args, int), fd);
	else if (format == 'u')
		result = ft_putuint10_fd(va_arg(args, unsigned int), fd);
	else if (format == 'x')
		result = ft_putuint16low_fd(va_arg(args, unsigned int), fd);
	else if (format == 'X')
		result = ft_putuint16up_fd(va_arg(args, unsigned int), fd);
	else if (format == '%')
		result = ft_putchar_fd_count('%', fd);
	else
		result = ft_putchar_fd_count('%', fd) + ft_putchar_fd_count(format, fd);
	return (result);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	args;
	int		i = 0;
	int		ct = 0;
	int		result;

	if (fd < 0 || !s)
		return (-1);
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
			result = ft_putformat_fd(args, s[++i], fd);
		else if (s[i] == '%')
			result = ft_putchar_fd_count('%', fd);
		else
			result = ft_putchar_fd_count(s[i], fd);
		if (result == -1)
			return (va_end(args), -1);
		ct += result;
		i++;
	}
	va_end(args);
	return (ct);
}
