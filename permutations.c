#include <stdio.h>

void swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

char *sort_str(char *str, int len)
{
    int i = 0;
    int j;

    while (i < len)
    {
        j = i + 1;
        while (j < len)
        {
            if (str[i] > str[j])
                swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
    return(str);
}

int next_permutation(char *str, int len)
{
    int i;
    int j;
    int start;
    int end;

    i = len - 2;
    while (i >= 0 && str[i] >= str[i + 1])
        i--;
    if (i < 0)
        return(0);
    j = len - 1;
    while (str[j] < str[i])
        j--;
    swap(&str[i], &str[j]);
    start = i + 1;
    end = len - 1;
    while (start < end)
    {
        swap(&str[start], &str[end]);
        start++;
        end--;
    }
    return(1);
}

int main(int argc, char **argv)
{
    if (argc != 2) 
    {
        return(1);
    }
    char *str = argv[1];
    int len = 0;
    if (!str)
        return(1);
    while (str[len])
    {
        len++;
    }
    str = sort_str(str, len);
    puts(str);
    while (next_permutation(str, len) != 0)
        puts(str);
}