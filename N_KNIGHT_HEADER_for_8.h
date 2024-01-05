/*_______________________________________________________
Written by Muhammad Anss (2022-MC-1) on December 12,2023
_________________________________________________________

_______________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define __BOARD_SIZE__ 8
#define __EMPTY__ ' '
#define __KNIGHT__ 'O'
#define __ATTACK__ 'X'
#define __MAX__KNIGHTS__ 12
#define __POP__ 200
// global variables
char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__]; // this is for fitness function
int chromosome[__POP__][__MAX__KNIGHTS__];           // this is for random generation of population and next population
int fitness[__POP__];
const int nParents = __POP__ / 2; // half of population will be parents
char sol[__BOARD_SIZE__][__BOARD_SIZE__];

/*
    I have defined following functions here
    functions summary
    01. Reset_Chrom_Board
    02. RandomPOP
    03. attacks
    04. Fitness
    05. swap_int
    06. swap_char
    07. Sorting
    08. Next_POP
    09. Display_EMPTY_spaces
    10. Solution_points
    11. Solution_Board
*/
// function prototypes
void Reset_Chrom_Board(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__])
{
    // initialize the chrom elements with empty spaces
    for (int p = 0; p < __POP__; p++)
    {
        for (int r = 0; r < __BOARD_SIZE__; r++)
        {
            for (int c = 0; c < __BOARD_SIZE__; c++)
                chrom[p][r][c] = __EMPTY__;
        }
    }
}
void RandomPOP(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__], int chromosome[__POP__][__MAX__KNIGHTS__])
// This function will generate values of knights randomly
{
    srand(time(0));
    for (int i = 0; i < __POP__; i++)
    {
        int alloted_knights = 0;
        while (alloted_knights < __MAX__KNIGHTS__)
        {
            int x = __BOARD_SIZE__ * __BOARD_SIZE__ - __BOARD_SIZE__ - 2;
            int y = __BOARD_SIZE__ + 1;
            chromosome[i][alloted_knights] = (rand() % (x - y)) + y;
            int row = chromosome[i][alloted_knights] / __BOARD_SIZE__; // this will give us row
            int col = chromosome[i][alloted_knights] % __BOARD_SIZE__; // this will give us column
            if (!row || row == 7 || !col || col == 7)
                continue; // no knight should be at boundary of the board
            if (chrom[i][row][col] != __KNIGHT__)
            {
                chrom[i][row][col] = __KNIGHT__;
                alloted_knights++; // only increment if knight is placed
            }
        }
    }
}
void attacks(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__])
// This function will mark the attacks of the knights
{
    for (int p = 0; p < __POP__; p++)
    {
        for (int r = 0; r < __BOARD_SIZE__; r++)
        {
            for (int c = 0; c < __BOARD_SIZE__; c++)
            {
                if (chrom[p][r][c] == __KNIGHT__)
                { // 8 cases of knight attacks
                    int a = 2;
                    int b = -1;
                    for (int iter = 0; iter < 8; iter++)
                    {
                        if (iter == 8 / 2)
                        {
                            a = 1;
                            b = -2;
                        }
                        if (iter % 2)
                            a = -a;
                        else
                            b = -b;
                        if (r + a >= 0 && c + b >= 0 && r + a < __BOARD_SIZE__ && c + b < __BOARD_SIZE__ && chrom[p][r + a][c + b] != __KNIGHT__)
                            chrom[p][r + a][c + b] = __ATTACK__;
                    }
                }
            }
        }
    }
}
void Fitness(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__], int fitness[__POP__])
/*This function will measure the fitness of chroms generated by
RandomPOP funciton*/
/* This function will check how much empty spaces are there
in the board will store fitness of each chrom in the fitness array*/

{
    int empty_spaces = 0;
    for (int p = 0; p < __POP__; p++)
    {
        for (int r = 0; r < __BOARD_SIZE__; r++)
        {
            for (int c = 0; c < __BOARD_SIZE__; c++)
            {
                if (chrom[p][r][c] == __EMPTY__)
                    empty_spaces++;
            }
        }
        fitness[p] = empty_spaces;
        empty_spaces = 0;
    }
}
// till now we have generated the population
// we have marked the attacks
// we have calculated the fitness
// now we will select the parents
// parents will those who have less emply spaces
// they will be selected in Fitness function

// i will sort the chrom and fitness array on the basis of empty spaces

void swap_int(int *a, int *b)
// This the simple function used to swap the values
// i checked it will work for arrays elements
// while calling this function will use like swap(&arr[0],&arr[1]);
// i know array are pointers but there elements will be treated as integers
// so we will use this function
// this function is only for integers
// this function will be used in sorting
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void swap_char(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
void Sorting(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__], int fitness[__POP__], int chromosome[__POP__][__MAX__KNIGHTS__])
{
    // Bubble sort the population
    // we will have fittest at start
    // meaning least empty spaces will be at start

    // for sorting
    // we will first assume the first element is the fittest
    for (int sp = 0; sp < __POP__; sp++)
    {
        for (int b = sp + 1; b < __POP__; b++)
        {
            if (fitness[sp] > fitness[b])
            {
                swap_int(&fitness[sp], &fitness[b]);
                // now we will swap the chroms
                // but the important part here
                // the whole 2D array within chroms should be swapped
                for (int r = 0; r < __BOARD_SIZE__; r++)
                {
                    for (int c = 0; c < __BOARD_SIZE__; c++)
                    {
                        swap_char(&chrom[sp][r][c], &chrom[b][r][c]);
                        // for 1 value of j all value of k will iterate
                        // and swap the whole 2-D arrays
                    }
                }
                for (int knights = 0; knights < __MAX__KNIGHTS__; knights++)
                    swap_int(&chromosome[sp][knights], &chromosome[b][knights]);
            }
        }
    }
}
/* now the chrom is sorted on the basis of empty spaces
 and combination with less empty spaces will be at start
 now we will select first of the combinations as parents
 and will perform cross over and mutation on them
 new generation will born*/
void Next_POP(int chromosome[__POP__][__MAX__KNIGHTS__], char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__])
{
    // Parent selection
    // survival of the fitest
    // so we choose first half of the population as parents
    // and will perform cross over and mutation on them

    // now we will perform cross over
    for (int k = 0; k < nParents; k = k + 2)
    {
        for (int i = 0; i < __MAX__KNIGHTS__; i += 2)
        {
            // even childs will take even values from even parents
            chromosome[nParents + k][i] = chromosome[k][i];
        }
        for (int i = 1; i < __MAX__KNIGHTS__; i += 2)
        {
            // even childs will take odd values from odd parents
            chromosome[nParents + k][i] = chromosome[k + 1][i];
        }
    }
    for (int k = 1; k < nParents; k = k + 2)
    {
        for (int i = 0; i < __MAX__KNIGHTS__; i += 2)
        {
            // odd parents will take even values from odd parents
            chromosome[nParents + k][i] = chromosome[k + 1][i];
        }
        for (int i = 1; i < __MAX__KNIGHTS__; i += 2)
        {
            // odd parents will take odd values from even parents
            chromosome[nParents + k][i] = chromosome[k][i];
        }
    }

    // after that we will perform mutation on the new generation
    srand(time(0));
    for (int pop = 1; pop < __POP__; pop++)
    {
        int checker_for_redundant_value=0;
        int index = (rand() % __MAX__KNIGHTS__);
        int x = __BOARD_SIZE__ * __BOARD_SIZE__ - __BOARD_SIZE__ - 2;
        int y = __BOARD_SIZE__ + 1;
        int value = (rand() % (x - y)) + y;
        for (int v = v; v < __MAX__KNIGHTS__; v++)
        {
            if(chromosome[pop][v]==value)
            {
                checker_for_redundant_value=1;
                break;
            }
        }
        if (!x || !y || x == __BOARD_SIZE__ - 1 || y == __BOARD_SIZE__ - 1||checker_for_redundant_value)
        {
            pop--;
            continue;
        }
        chromosome[pop][index] = value;
        // this will give 1 random value to each population
    }
    // now we will convert the chromosome array to chrom array
    // reseting the chrom array
    Reset_Chrom_Board(chrom);
    for (int i = 0; i < __POP__; i++)
    {
        for (int knights = 0; knights < __MAX__KNIGHTS__; knights++)
        {
            int row = chromosome[i][knights] / __BOARD_SIZE__;
            int col = chromosome[i][knights] % __BOARD_SIZE__;
            chrom[i][row][col] = __KNIGHT__;
        }
    }
}
void Display_EMPTY_spaces(int fitness[__POP__])
/* This is for debugging purposes
will tell us the difference between next gen and previous gen*/
{
    for (int pop = 0; pop < __POP__; pop++)
    {
        printf("%d", fitness[pop]);
        if (pop != __POP__ - 1)
            printf(",");
        if (pop % 10 == 0)
            printf("\n");
    }
    printf("\n");
}
void Solution_points(char sol[__BOARD_SIZE__][__BOARD_SIZE__])
{
    printf("Knights were placed at the following positions:\n");
    int found_knights = 0;
    for (int r = 0; r < __BOARD_SIZE__; r++)
    {
        for (int c = 0; c < __BOARD_SIZE__; c++)
        {
            if (sol[r][c] == __KNIGHT__)
            {
                printf("(%d,%d)", r, c);
                found_knights == __MAX__KNIGHTS__ - 1 ? printf("and ") : printf(",");
            }
        }
    }
    printf("\nNo. of knights in this solution = %d\n", __MAX__KNIGHTS__);
}
void Solution_Board(char sol[__BOARD_SIZE__][__BOARD_SIZE__])
{
    printf("\n -----------------\n");
    printf(" ");
    for (int i = 0; i < __BOARD_SIZE__; i++) // this will change
        printf("|%d", i + 1);
    printf("|\n -----------------\n");
    for (int i = 0; i < __BOARD_SIZE__; i++)
    {
        printf("%d", i + 1);
        for (int j = 0; j < __BOARD_SIZE__; j++)
        {
            if (sol[i][j] == __EMPTY__)
                printf("|%c", sol[i][j]);
            else if (sol[i][j] == __ATTACK__)
                printf("|\033[0;31m%c\033[0m", sol[i][j]); // red
            else if (sol[i][j] == __KNIGHT__)
                printf("|\033[0;34m%c\033[0m", sol[i][j]); // blue
        }
        printf("|\n -----------------\n");
    }
}

// end of header file