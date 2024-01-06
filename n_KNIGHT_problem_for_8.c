/*_______________________________________________________
Written by Muhammad Anss (2022-MC-1) on December 12,2023
_________________________________________________________
This is being written to solve the n_KNIGHT problem using
Genetic Algorithm.
_______________________________________________________*/
#include "n_KNIGHT_HEADER_for_8.h"
/* all macros, global variables, arrayss
and user defined functionsare included in the header file*/
int main()
{
    srand(time(0)); // to generate random numbers
    int isOver = 12, iter = 0, maxIter = 10000;
    RandomPOP(chromosome);
    Board_Filler(Boards,chromosome);
    while (iter < maxIter)
    {
        iter++;
        Fitness(Boards, fitness);
        Sorting( fitness, chromosome);
        Board_Filler(Boards,chromosome);
        if (iter % 1000 == 0)
        {
            system("cls");
            printf("Iteration number %d\n", iter);
            Solution_Board(Boards[0]);
        }
        // Display_EMPTY_spaces(fitness); // for debugging purposes
        isOver = !fitness[0];
        if (isOver)
        {
            system("cls");
            printf("Solution found after %d iterations!", iter);
            Solution_Board(Boards[0]);
            Solution_points(Boards[0]);
            break;
        }
        if (iter == maxIter - 1)
            printf("No solution found after %d iterations!\n\n", iter);
        // chrom will be reset in beforing next population
        Next_POP(chromosome);
        Board_Filler(Boards,chromosome);
    }
    // int x = 3;
    // printf("Press any key to exit...>> ");
    // scanf("%d", &x); // to hold the screen

    return 0;
}