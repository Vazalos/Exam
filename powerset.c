#include <stdio.h>
#include <stdlib.h>

void print_list(int *num_list, int num_size)
{
    int i = 0;

    while (i < num_size)
    {
        if (i > 0)
            printf(" ");
        printf("%i", num_list[i]);
        i++;
    }
    printf("\n");
}

void powerset(int *num_list, int num_size, int target, int index, int sum, int *sum_list, int sum_size)
{
    if (index == num_size)
    {
        if (sum == target)
            print_list(sum_list, sum_size);
        return ;
    }
    powerset(num_list, num_size, target, index + 1, sum, sum_list, sum_size);
    sum_list[sum_size] = num_list[index];
    powerset(num_list, num_size, target, index + 1, sum + num_list[index], sum_list, sum_size + 1);
}

int main(int argc, char **argv)
{
    int target;
    int *num_list;
    int num_size;
    int *sum_list;
    int i = 0;

    if(argc < 2)
        return(1);

    target = atoi(argv[1]);

    num_size = argc - 2;
    if (num_size == 0)
    {
        if (target == 0)
            printf("\n");
        return(0); //could be missing 0 for result;
    }

    num_list = malloc(num_size * sizeof(int));
    if(!num_list)
        return(1);
    while (i < num_size)
    {
        num_list[i] = atoi(argv[i + 2]);
        i++;
    }

    sum_list = malloc(num_size * sizeof(int));
    if(!sum_list)
        return(1);

    powerset(num_list, num_size, target, 0, 0, sum_list, 0);
    free(num_list);
    free(sum_list);
}