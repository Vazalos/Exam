#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int cha;

    cha = fgetc(f);
    if(cha == EOF)
        return(EOF);
    while(cha != EOF)
    {
        if(isspace(cha) == 0)
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
    int cha;

    cha = fgetc(f);
    if (cha == c)
        return(1);
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
    int value = 0;
    int sign = 1;
    int digits = 0;
    int cha;
    int* dest;

    cha = fgetc(f);
    if (cha != '+' && cha != '-' && isdigit(cha) == 0)
        return(0);
    if (cha == '+' || cha == '-')
    {
        if (cha == '-')
            sign = -1;
        cha = fgetc(f); 
    }
    while (cha != EOF && isdigit(cha) != 0)
    {
        value = value * 10 + (cha - '0');
        cha = fgetc(f);
        digits++;
    }
    if (digits == 0)
        return(0);
    dest = va_arg(ap, int*);
    *dest = (value * sign);
    if (cha != EOF)
        ungetc(cha, f);
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int cha;
    char *dest = va_arg(ap, char*);
    int i = 0;

    cha = fgetc(f);
    if (cha == EOF)
        return(0);
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

int main()
{
    int num;
    char c;
    char str[1000];

    printf("input word: ");
    if (ft_scanf("%s", &str) != 1)
        printf("invalid word");

    printf("input number: ");
    if (ft_scanf("%d", &num) != 1)
        printf("invalid num");

    printf("input character: ");
    if (ft_scanf("%c", &c) != 1)
        printf("invalid char");

    printf("\n");
    printf("num is %d\n", num);
    printf("char is %c\n", c);
    printf("word is %s\n", str);
}