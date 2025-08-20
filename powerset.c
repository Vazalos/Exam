#include <stdlib.h>
#include <stdio.h>

void print_list(int *list, int list_size)
{
    int i = 0;

    while (i < list_size)
    {
        if (i > 0)
        {
            printf(" ");
        }
        printf("%i", list[i]);
        i++;
    }
    printf("\n");
}

void powerset(int *set_list, int set_size, int index, int target, int sum, int *comb_list, int comb_size)
{
    if (index == set_size && sum == target)
    {
        print_list(comb_list, comb_size);
        return ;
    }
    else if (index == set_size)
    {
        return ;
    }
    powerset(set_list, set_size, index + 1, target, sum, comb_list, comb_size);
    comb_list[comb_size] = set_list[index];
    powerset(set_list, set_size, index + 1, target, sum + set_list[index], comb_list, comb_size + 1);
}

int main(int argc, char **argv)
{
    int *set_list;
    int *comb_list;
    int set_size;
    int target;
    int i = 0;

    if (argc < 3)
        return(1);
    target = atoi(argv[1]);
    set_size = argc - 2;
    set_list = malloc(set_size * sizeof(int));
    if (!set_list)
        return(1);
    while (i < set_size)
    {
        set_list[i] = atoi(argv[i + 2]);
        i++;
    }
    comb_list = malloc(set_size * sizeof(int));
    if (!comb_list)
        return(1);
    powerset(set_list, set_size, 0, target, 0, comb_list, 0);
    free(set_list);
    free(comb_list);
}