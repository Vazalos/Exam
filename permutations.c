#include <stdio.h>
#include <stdlib.h>

void	swap(char *str, int l_index, int r_index)
{
	char temp = str[l_index];
	str[l_index] = str[r_index];
	str[r_index] = temp;
}

void print_list(char **list, int max)
{
	int i = 0;

	while (i < max)
	{
		printf("%s\n", list[i]);
		i++;
	}
}

char* ft_strdup(char *str)
{
	int i = 0;
	char *new_str;
	int len;

	while(str[i])
		i++;
	len = i;
	new_str = malloc((len + 1) * sizeof(char));
	if(!new_str)
		return(NULL);
	i = 0;
	while(i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return(new_str);
}

void permutations(char *str, int len, int l_index, int r_index, int max, char **list)
{
	static int i;

	if (l_index == len)
	{
		list[i++] = ft_strdup(str);
		if (i == max)
			print_list(list, max);
		return ;
	}
	r_index = l_index;
	while (r_index < len)
	{
		swap(str, l_index, r_index);
		permutations(str, len, l_index + 1, r_index, max, list);
		swap(str, l_index, r_index);
		r_index++;
	}
}

int diff(char* str1, char *str2, int len)
{
	int i = 0;

	while (i < len && str1[i] == str2[i])
		i++;
	if(i == len)
		return(0);
	if(str1[i] > str2[i])
		return(1);
	else if (str1[i] < str2[i])
		return(-1);
	else
		return(-2);
}

char *organize(char *str)
{
	int i = 0;
	int j = 0;

	while(str[i])
	{
		while(str[j])
		{
			if (str[i] > str[j])
				swap(str, i, j);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (str);
}

int main(int argc, char **argv)
{
	char *str;
	int i = 0;
	int len;
	int max = 1;
	char **list;

	if (argc != 2)
		return(1);
	str = argv[1];
	while(str[i])
		i++;
	len = i;
	while (i > 1)
	{
		max = max * i;
		i--;
	}
	list = malloc((max + 1) * sizeof(char));
	if (!list)
		return(1);
	str = organize(str);
	permutations(str, len, 0, 0, max, list);
	i = 0;
	while(i < max)
	{
		free(list[i]);
		i++;
	} 
	free(list);
}
