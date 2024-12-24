#include "minishell.h"

int	ft_fprintp2(int fd, void *p);
int	ft_fprintp(int fd, void *p);
int	ft_fprintu(int fd, unsigned int n);
int	ft_fprintx_up(int fd, long n);
int	ft_fprintd(int fd, int n);
int	ft_fprints(int fd, char *s);
int	ft_fprintc(int fd, char c);

int	ft_fprintp2(int fd, void *p)
{
	char			*hex;
	int				chars;
	unsigned long	num;

	hex = "0123456789abcdef";
	chars = 0;
	num = (unsigned long)p;
	if (num / 16 > 0)
	{
		chars += ft_fprintp2(fd, (void *)(num / 16));
	}
	chars += ft_fprintc(fd, hex[num % 16]);
	return (chars);
}

int	ft_fprintp(int fd, void *p)
{
	unsigned long	num;
	int				chars;

	num = (unsigned long)p;
	chars = 0;
	if (num == 0)
	{
		chars += write(fd, "(nil)", 5);
	}
	else
	{
		chars += write(fd, "0x", 2);
		chars += ft_fprintp2(fd, p);
	}
	return (chars);
}

int	ft_fprintu(int fd, unsigned int n)
{
	int	chars;

	chars = 0;
	if (n >= 10)
	{
		chars += ft_fprintd(fd, (n / 10));
	}
	chars += ft_fprintc(fd, '0' + n % 10);
	return (chars);
}

int	ft_fprintx_up(int fd, long n)
{
	char	*hex;
	int		chars;

	hex = "0123456789ABCDEF";
	chars = 0;
	if (n / 16 > 0)
	{
		chars += ft_fprintx_up(fd, (n / 16));
	}
	chars += ft_fprintc(fd, hex[n % 16]);
	return (chars);
}

int	ft_fprintx_lo(int fd, long n)
{
	char	*hex;
	int		chars;

	hex = "0123456789abcdef";
	chars = 0;
	if (n / 16 > 0)
	{
		chars += ft_fprintx_lo(fd, (n / 16));
	}
	chars += ft_fprintc(fd, hex[n % 16]);
	return (chars);
}

int	ft_fprintd(int fd, int n)
{
	int	chars;

	chars = 0;
	if (n == -2147483648)
	{
		chars += ft_fprints(fd, "-2147483648");
		return (chars);
	}
	if (n < 0)
	{
		chars += ft_fprintc(fd, '-');
		n = -n;
	}
	if (n >= 10)
	{
		chars += ft_fprintd(fd, (n / 10));
	}
	chars += ft_fprintc(fd, '0' + n % 10);
	return (chars);
}

int	ft_fprints(int fd, char *s)
{
	int	chars;

	chars = 0;
	if (!s)
	{
		return (write(fd, "(null)", 6));
	}
	while (*s != '\0')
	{
		chars += ft_fprintc(fd, *s);
		s++;
	}
	return (chars);
}

int	ft_fprintc(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_fprintf2(int fd, char specifier, va_list args)
{
	int	chars;

	chars = 0;
	if (specifier == 'c')
		chars += ft_fprintc(fd, va_arg(args, int));
	else if (specifier == 's')
		chars += ft_fprints(fd, va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		chars += ft_fprintd(fd, va_arg(args, int));
	else if (specifier == 'x')
		chars += ft_fprintx_lo(fd, va_arg(args, unsigned int));
	else if (specifier == 'X')
		chars += ft_fprintx_up(fd, va_arg(args, unsigned int));
	else if (specifier == 'u')
		chars += ft_fprintu(fd, va_arg(args, unsigned int));
	else if (specifier == 'p')
		chars += ft_fprintp(fd, va_arg(args, void *));
	else if (specifier == '%')
		chars += ft_fprintc(fd, '%');
	return (chars);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	int		chars;
	va_list	args;

	chars = 0;
	if (!s)
		return (-1);
	va_start(args, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			chars += ft_fprintf2(fd, *s, args);
		}
		else
			chars += write(fd, s, 1);
		s++;
	}
	va_end(args);
	return (chars);
}
