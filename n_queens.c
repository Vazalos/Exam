#include <stdlib.h>
#include <stdio.h>

void print_solution(int *board, int n)
{
    int i = 0;

    while(i < n)
    {
        if (i > 0)
            fprintf(stdout, " ");
        fprintf(stdout, "%i", board[i]);
        i++;
    }
    fprintf(stdout, "\n");
}

int absol(int num)
{
    if (num < 0)
        return(-num);
    return(num);
}

int is_safe(int *board, int col, int row)
{
    int prev_col = 0;
    int prev_row;

    while (prev_col < col)
    {
        prev_row = board[prev_col];
        if (prev_row == row ||
            prev_row + prev_col == row + col ||
            prev_row - prev_col == row - col)
        {
            return(0);
        }
        prev_col++;
    }
    return(1);
}

void n_queens(int *board, int n, int col)
{
    int row = 0;

    if (col == n)
    {
        print_solution(board, n);
        return ;
    }
    while (row < n)
    {
        if (is_safe(board, col, row) == 1)
        {
            board[col] = row;
            n_queens(board, n, col + 1);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return(1);
    int n = atoi(argv[1]);
    if (n <= 0)
        return(0);
    int *board = malloc(n * sizeof(int));
    if (!board)
        return(1);
    n_queens(board, n, 0);
    free(board);
}