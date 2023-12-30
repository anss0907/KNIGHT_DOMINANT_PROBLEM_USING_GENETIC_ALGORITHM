/*_______________________________________________________
Written by Muhammad Anss (2022-MC-1) on December 12,2023
_________________________________________________________
This is being written to solve the n_KNIGHT problem using
Genetic Algorithm.
_______________________________________________________*/
#include "n_KNIGHT_HEADER_2nd.h"
/* all macros, global variables, arrays
and user defined functionsare included in the header file*/
int main()
{

    char sol[__BOARD_SIZE__][__BOARD_SIZE__];
    int isOver = 0, iter = 0, maxIter = 1000;
    Reset_Chrom_Board(chrom);
    RandomPOP(chrom, chromosome);
    attacks(chrom);
    int ne = 0; // will remove later
    int checker[1000];
    while (iter <= maxIter)
    {
        if(iter>900)
        {checker[iter]=fitness[0];
        if (checker[iter]> checker[iter-100])
        {
            Reset_Chrom_Board(chrom);
            RandomPOP(chrom, chromosome);
            attacks(chrom);
            iter = 0;
            ne++;
        } }// will remove later
        iter++;
        Fitness(chrom, fitness);
        Sorting(chrom, fitness, chromosome);
        printf("Iteration number %d\n", iter);
        Display_EMPTY_spaces(fitness);
        isOver = Checking_Solutions(fitness, sol);
        if (isOver == 1)
        {
            printf("ne = %d\n", ne); // will remove later
            printf("Solution found after %d iterations!\n\n", iter);
            Solution_Board(sol);
            break;
        }
        if (iter == maxIter)
        {
            printf("No solution found after %d iterations!\n\n", iter);
            break;
        }
        // chrom will be reset in beforing next population
        Next_POP(chromosome, chrom);
        attacks(chrom);
    }
    printf("No. of knights in this solution = %d\n", __MAX__KNIGHTS__);
    // int x = 3;
    // printf("Press any key to exit...>> \n");
    // scanf("%d", &x);

    return 0;
}