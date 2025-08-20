#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int cha;

	cha = fgetc(f);
	while(cha != EOF)
	{
		if(isspace(cha) == 0)
		{
			ungetc(cha, f);
			break;
		}
		cha = fgetc(f);
	}
    return (0);
}

int match_char(FILE *f, char c)
{
	int cha;

	cha = fgetc(f);
	if (cha == c)
		return (1);
	if (cha != EOF)
		ungetc(cha, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int cha;
	char *dest;

	cha = fgetc(f);
	if (cha == EOF)
		return(0);
	dest = va_arg(ap, char*);
	*dest = (char)cha;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int cha;
	int sign = 1;
	int value = 0;
	int digits = 0;
	int *dest; 

	cha = fgetc(f);
	if (cha != '-' && cha != '+' && isdigit(cha) == 0)
	{
		if (cha != EOF)
			ungetc(cha, f);
		return(0);
	}
	if (cha == '-' || cha == '+')
	{
		if (cha == '-')
			sign = -1;
		cha = fgetc(f);
	}
	while (cha != EOF && isdigit(cha) != 0)
	{
		value = (value * 10) + (cha - '0');
		cha = fgetc(f);
		digits++;
	}
	if (cha != EOF)
		ungetc(cha, f);
	if (digits == 0)
		return(0);
	dest = va_arg(ap, int*);
	*dest = (value * sign);
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	int cha;
	char *dest = va_arg(ap, char *);
	int i = 0;

	cha = fgetc(f);
	if (cha == EOF)
		return(0);
	while (cha != EOF && isspace(cha) == 0)
	{
		dest[i++] = (char)cha;
		cha = fgetc(f);
	}
	if (cha != EOF)
		ungetc(cha, f);
	dest[i] = '\0';
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			elsebreak;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
