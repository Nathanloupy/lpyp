#pragma once

#include <unistd.h>
#include <stdarg.h>

#define HEX_BASE_LOWER	"0123456789abcdef"
#define HEX_BASE_UPPER	"0123456789ABCDEF"

int	ft_dprintf(int fd, const char *s, ...);
