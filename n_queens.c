#include <stdlib.h>
#include <stdio.h>

void print_list(int *queen_pos, int n)
{
    int i = 0;

    while (i < n)
    {
        if (i > 0)
            fprintf(stdout, " ");
        fprintf(stdout, "%i", queen_pos[i]);
        i++;
    }
    fprintf(stdout, "\n");
}

int is_safe(int *queen_pos, int col, int row)
{
    int old_col = 0;
    int old_row;

    while (old_col < col)
    {
        old_row = queen_pos[old_col];
        if(row == old_row 
            || old_row - old_col == row - col
            || old_row + old_col == row + col)
        {
            return(0);
        }
        old_col++;
    }
    return(1);
}

void n_queens(int *queen_pos, int n, int col)
{
    int row = 0;

    if(col == n)
    {
        print_list(queen_pos, n);
        return ;
    }
    while (row < n)
    {
        if (is_safe(queen_pos, col, row) == 1)
        {
            queen_pos[col] = row;
            n_queens(queen_pos, n, col + 1);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    int n;
    int *queen_pos;
    if (argc != 2)
        return(1);
    n = atoi(argv[1]);
    if (n <= 0)
        return(1);
    queen_pos = malloc(n * sizeof(int));
    if (!queen_pos)
        return(1);
    n_queens(queen_pos, n, 0);
    free(queen_pos);
}