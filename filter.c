#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *replace(char* str, char *substr)
{
    size_t i = 0;
    char *aster;
    char *temp;
    size_t len = strlen(substr);

    aster = malloc((len + 1) * sizeof(char));
    if (!aster)
    {
        fprintf(stderr, "Error: invalid malloc");
        return(NULL);
    }
    while (i < len)
    {
        aster[i] = '*';
        i++;
    }
    aster[i] = '\0';

    temp = str;
    while (temp)
    {
        temp = memmem(temp, strlen(temp), substr, len);
        if(!temp)
            break;
        temp = memmove(temp, aster, len);
    }
    free(aster);
    return(str);
}

char *ft_strdup(char *str)
{
    char *new_str;
    int len = strlen(str);
    int i = 0;

    new_str = malloc((len + 1) * sizeof(char));
    if (!new_str)
    {
        fprintf(stderr, "Error: invalid malloc");
        return(NULL);
    }
    while (i < len)
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return(new_str);
}

char *filter(char *substr)
{
    int i = 0;
    static int read_pos;
    static int buff_pos;
    static char buffer[BUFFER_SIZE];
    char line[10000];
    char *result;

    if(BUFFER_SIZE <= 0)
        return(NULL);
    while(1)
    {
        if(buff_pos >= read_pos)
        {
            read_pos = read(0, buffer, BUFFER_SIZE);
            buff_pos = 0;
            if (read_pos == 0)
                break;
            if (read_pos < 0)
            {
                fprintf(stderr, "Error: invalid read");
                return(NULL);
            }
        }
        line[i++] = buffer[buff_pos++];
        if (line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return(NULL);
    result = replace(ft_strdup(line), substr);
    return(result);
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return(1);
    char *str;
    char *line;

    str = argv[1];
    while (1)
    {
        line = filter(str);
        if (!line)
            return(1);
        /*if (line[0] == '!')
        {
            free(line);
            return(0);
        }*/
        fprintf(stdout, "%s", line);
        free(line);
    }
    return(0);
}