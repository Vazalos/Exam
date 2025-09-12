#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int cha = fgetc(f);

    if (cha == EOF)
        return(-1);
    while(cha != EOF)
    {
        if (isspace(cha) == 0)
        {
            break;
        }
        cha = fgetc(f);
    }
    if (cha != EOF)
        ungetc(cha, f);
    return (0);
}

int match_char(FILE *f, char c)
{
    int cha = fgetc(f);

    if (cha == c)
        return(1);
    if (cha != EOF)
        ungetc(cha, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int cha = fgetc(f);
    char *dest;

    if (cha == EOF)
        return(-1);
    dest = va_arg(ap, char*);
    *dest = (char)cha;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int cha;
    int *dest;
    int value = 0;
    int sign = 1;
    int digits = 0;

    cha = fgetc(f);
    if(cha != '-' && cha != '+' && isdigit(cha) == 0)
    {
        printf("wrong first char (num) || tests %c, %i, %i, %i\n", (char)cha, cha != '-', cha != '+', isdigit(cha) == 0);
        return(-1);
    }
    if(cha == '-' || cha == '+')
    {
        if(cha == '-')
            sign = -1;
        cha = fgetc(f);
    }
    while(cha != EOF && isdigit(cha) != 0)
    {
        value = value * 10 + (cha - '0');
        cha = fgetc(f);
        digits++;
    }
    if (digits == 0)
    {
        printf("no digits counted (num)\n");
        return(-1);
    }
    dest = va_arg(ap, int*);
    *dest = (value * sign);
    if (cha != EOF)
        ungetc(cha, f);
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int cha = fgetc(f);
    char *dest = va_arg(ap, char*);
    int i = 0;

    if(cha == EOF)
        return(-1);
    while (cha != EOF && isspace(cha) == 0)
    {
        dest[i++] = (char)cha;
        cha = fgetc(f);
    }
    dest[i] = '\0';
    if (cha != EOF)
        ungetc(cha, f);
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
			else
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
/*
int main(void)
{
    char c;
    int num;
    char str[100];

    printf("insert a number\n");
    ft_scanf("%d", &num);
    printf("insert a char\n");
    ft_scanf("%c", &c);

    printf("insert a word\n");
    ft_scanf("%s", str);

    
    printf("insert thusly 'number, char, word'\n");
    ft_scanf("%d, %c, %s", &c, &num, str);
    
    printf("you wrote char '%c', number '%d', and word '%s'\n", c, num, str);
    return(0);
}*/

int main(void)
{
	char c;
	int n;
	char str[100];

    /*
	printf("enter a char, digit, string\n");
	if (ft_scanf("%c", &c) < 1)
		printf("error\n");
	if (ft_scanf("%s", str) < 1)
		printf("error\n");
	if (ft_scanf("%d", &n) < 1)
		printf("error\n");*/

    ft_scanf("%c %s %d", &c, str, &n);

	printf("you entered\n c = '%c'\n d = '%d'\n s = '%s'", c, n, str);
	return (0);
}