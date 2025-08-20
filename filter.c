#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

char *ft_strdup(char *str)
{
	char *new_str;
	int	len;
	int	i = 0; 

	len = strlen(str);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
	{
		fprintf(stderr, "Error: invalid malloc\n");
		return(NULL);
	}
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char *replace(char *str, char *substr)
{
	char *aster;
	char *temp;
	size_t j = 0;

	if (!str){
		return(NULL);
	}
	aster = malloc((strlen(str) + 1) * sizeof(char));
	if (!aster)
	{
		fprintf(stderr, "Error: invalid malloc\n");
		return(NULL);
	}
	while (j < strlen(str))
	{
		aster[j++] = '*';
	}
	aster[j] = '\0';
	temp = str;
	while(temp)
	{
		temp = memmem(temp, strlen(temp), substr, strlen(substr));
		if (!temp)
			break;
		temp = memmove(temp, aster, strlen(substr));
		if (!temp)
			break;
	}
	free(aster);
	return(str);
}

char *filter(char *substr)
{
	char *result;
	int i = 0;
	static int read_pos;
	static int buff_pos;
	static char buffer[BUFFER_SIZE];
	char line[7000];

	if (BUFFER_SIZE <= 0){
		return(NULL);}
	while(1)
	{
		if (buff_pos >= read_pos)
		{
			read_pos = read(0, buffer, BUFFER_SIZE);
			buff_pos = 0;
			if (read_pos == 0)
				break;
			if (read_pos < 0)
			{
				fprintf(stderr, "Error: invalid read\n");
				break;
			}
		}
		line[i++] = buffer[buff_pos++];
		if (line[i - 1] == '\n')
			break;
	}
	if (i == 0)
	{
		return (NULL);
	}
	line[i] = '\0';
	result = replace(ft_strdup(line), substr);
	return(result);
}

int main(int argc, char **argv)
{
	char *str;
	char *temp;

	if (argc != 2)
		return(1);
	str = argv[1];
	if (!str)
	{
		return(1);
	}
	while(1)
	{
		temp = filter(str);
		if (!temp)
			break;
		printf("%s", temp);
		free(temp);
	}
	return(0);

}
