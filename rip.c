#include <stdio.h>

int extra_par(char *str)
{
    int open = 0;
    int closed = 0;
    int i = 0;

    while(str[i])
    {
        if (str[i] == '(')
            open++;
        if (str[i] == ')')
        {
            if (open > 0)
                open--;
            else
                closed++;
        }
        i++;
    }
    return (open + closed);
}

void rip(char *str, int len, int index, int open, int closed, int removed, int min_remove, char *buffer)
{
    if (index == len)
    {
        buffer[index] = '\0';
        if (removed == min_remove && closed == open)
            puts(buffer);
        return ;
    }

    buffer[index] = str[index];
    if (str[index] == '(')
        rip(str, len, index + 1, open + 1, closed, removed, min_remove, buffer);
    else if (str[index] == ')' && open > closed)
        rip(str, len, index + 1, open, closed + 1, removed, min_remove, buffer);
    else if (str[index] != '(' && str[index] != ')')
        rip(str, len, index + 1, open, closed, removed, min_remove, buffer);
    if (str[index] == '(' || str[index] == ')')
    {
        buffer[index] = ' ';
        rip(str, len, index + 1, open, closed, removed + 1, min_remove, buffer);
    }
}

int main(int argc, char **argv)
{
    char *str;
    int min_remove;
    int len = 0;
    char buffer[1000];

    if (argc != 2)
        return(1);
    str = argv[1];
    min_remove = extra_par(str);
    while (str[len])
        len++;
    rip(str, len, 0, 0, 0, 0, min_remove, buffer);
}