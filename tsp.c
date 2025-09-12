#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

void swap(float **a, float **b)
{
    float *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

float calc_dist(float *a, float *b)
{
    float x_dist;
    float y_dist;
    float dist;

    x_dist = a[0] - b[0];
    y_dist = a[1] - b[1];
    dist = sqrt((x_dist * x_dist) + (y_dist * y_dist));

    return(dist);
}

void tsp(float **cities, int city_num, int index, float sum, float *min_dist)
{
    int i;
    float result;

    if (index == city_num)
    {
        result = sum + calc_dist(cities[0], cities[index - 1]);
        if (result < *min_dist)
            *min_dist = result; 
        return ;
    }

    i = index;
    while(i < city_num)
    {
        swap(&cities[index], &cities[i]);
        tsp(cities, city_num, index + 1, sum + calc_dist(cities[i], cities[i - 1]), min_dist);
        swap(&cities[index], &cities[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    FILE* fptr;
    float **cities;
    int city_num = 1;
    int i = 0;
    float min_dist = FLT_MAX;

    if (argc != 2)
        return(1);
    cities = malloc(city_num * sizeof(float*));
    while (i < city_num)
    {
        cities[i] = malloc(2 * sizeof(float));
        i++;
    }
    fptr = fopen(argv[1], "r");
    i = 0;
    while (fscanf(fptr, "%f, %f\n", &cities[i][0], &cities[i][1]) == 2)
    {
        i++;
        if (i >= city_num)
        {
            city_num++;
            cities = realloc(cities, city_num * sizeof(float*));
            cities[i] = malloc(2 * sizeof(float));
        }
    }
    city_num--;
    free(cities[i]);
    cities = realloc(cities, city_num * sizeof(float*));

    tsp(cities, city_num, 1, 0.0, &min_dist);
    fprintf(stdout, "%.2f\n", min_dist);
    fclose(fptr);
    free(cities);
}