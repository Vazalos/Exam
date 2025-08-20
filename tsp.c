#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <math.h>

void    print_coords(float **coords, int city_num)
{
    int i = 0;

    while (i < city_num)
    {
        fprintf(stdout, "%f, %f\n", coords[i][0], coords[i][1]);
        i++;
    }   
    fprintf(stdout, "\n");
}

void    free_coords(float **coords, int i)
{
    int j = 0;

    while (j < i)
    {
        free(coords[j]);
        j++;
    }
    free(coords);
}

float calc_dist(float *a, float *b)
{
    float dist_x;
    float dist_y;
    float dist;

    dist_x = a[0] - b[0];
    dist_y = a[1] - b[1];
    dist = sqrtf((dist_x * dist_x) + (dist_y * dist_y));
    return(dist);
}

void swap(float **a, float **b)
{
    float *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void tsp(float **coords, int city_num, int index, float dist, float *min_dist)
{
    int i;

    if (index == city_num)
    {
        dist = dist + calc_dist(coords[index - 1], coords[0]);
        if (dist < *min_dist)
            *min_dist = dist;
        return ;
    }
    i = index;
    while(i < city_num)
    {
        swap(&coords[index], &coords[i]);
        tsp(coords, city_num, index + 1, dist + calc_dist(coords[index - 1], coords[index]), min_dist);
        swap(&coords[index], &coords[i]);
        i++;
    } 
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return(1);
    float **coords;
    int city_num;
    int i = 0;
    float min_dist = FLT_MAX;

    city_num = atoi(argv[1]);
    if (city_num < 2)
        return(1);
    coords = malloc(city_num * sizeof(float*));
    if(!coords)
        return(1);
    fprintf(stdout, "write %i sets of coords 'x, y' (last extra discarded)\n", city_num);
    while (i < city_num)
    {
        coords[i] = malloc(2 * sizeof(float));
        if (!coords[i])
        {
            free_coords(coords, i);
            return(1);
        }
        if(fscanf(stdin, "%f, %f\n", &coords[i][0], &coords[i][1]) != 2)
        {
            free_coords(coords, i + 1);
            return(1);
        }
        i++;
    }
    print_coords(coords, city_num);
    tsp(coords, city_num, 1, 0, &min_dist);
    fprintf(stdout, "min_dist = %.2f", min_dist);
    free_coords(coords, city_num);
}