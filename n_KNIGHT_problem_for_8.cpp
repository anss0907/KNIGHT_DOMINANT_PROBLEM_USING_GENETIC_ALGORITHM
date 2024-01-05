// this is c++ version of the n_KNIGHT_problem_for_8.py
#include "N_KNIGHT_HEADER_for_8.hpp"

int main()
{
    int isOver = 12, iter = 0, maxIter = 5000;
    Reset_Chrom_Board(chrom);
    RandomPOP(chrom, chromosome);
    attacks(chrom);
    while (iter < maxIter)
    {
        iter++;
        Fitness(chrom, fitness);
        Sorting(chrom, fitness, chromosome);
        if (iter % 100 == 0)
        {
            system("cls");
            cout<<"Iteration number "<<iter<<endl;
            Solution_Board(chrom[0]);
        }
        // Display_EMPTY_spaces(fitness); // for debugging purposes
        isOver = !fitness[0];
        if (isOver)
        {
            system("cls");
            cout<<"Solution found after "<<iter<<" iterations!"<<endl<<endl;
            Solution_Board(chrom[0]);
            Solution_points(chrom[0]);
            break;
        }
        if (iter == maxIter - 1)
            cout<<"No solution found after "<<iter<<" iterations!"<<endl<<endl;
        // chrom will be reset in beforing next population
        Next_POP(chromosome, chrom);
        attacks(chrom);
    }
    // int x = 3;
    // printf("Press any key to exit...>> ");
    // scanf("%d", &x); // to hold the screen

    return 0;
}