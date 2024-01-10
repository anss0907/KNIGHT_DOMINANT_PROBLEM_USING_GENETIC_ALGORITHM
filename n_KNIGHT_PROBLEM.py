# This is the python version of n_KNIGHT_problem

from random import sample
from colorama import Fore
from os import system

__BOARD_SIZE__ = 8
__EMPTY__ = ' '
__KNIGHT__ = 'O'
__ATTACK__ = 'X'
__MAX__KNIGHTS__ = 12
__POP__ = 200
Possible_Positions = []
for i in range(__BOARD_SIZE__ * __BOARD_SIZE__):
    x = i // __BOARD_SIZE__
    y = i % __BOARD_SIZE__
    if (x and y and x < 7 and y < 7):
        Possible_Positions.append(i)
# print(Possible_Positions)
# chrom is for fitness funciton whereas chromosome is to generate random population
chrom = [[[" " for i in range(__BOARD_SIZE__)] for c in range(__BOARD_SIZE__)]for p in range(__POP__)]
# this is equiavalent to reset the boards
chromosome = [
    sample(Possible_Positions, __MAX__KNIGHTS__) for p in range(__POP__)
]
# This is equivalent to generate first random population
fitness = [65 for i in range(__POP__)]
# half of population will be parents
nParents = __POP__ // 2
# sol[__BOARD_SIZE__][__BOARD_SIZE__]

# no need to reset it's already reset
# first random populatin is already generated


def Board_Filler(chromosome):
    chrom = [[[" " for i in range(__BOARD_SIZE__)]
              for c in range(__BOARD_SIZE__)] for p in range(__POP__)]
    for p in range(__POP__):
        for k in range(__MAX__KNIGHTS__):
            row = chromosome[p][k] // __BOARD_SIZE__
            col = chromosome[p][k] % __BOARD_SIZE__
            chrom[p][row][col] = __KNIGHT__
    for p in range(__POP__):
        for r in range(__BOARD_SIZE__):
            for c in range(__BOARD_SIZE__):
                if (chrom[p][r][c] == __KNIGHT__):
                    # 8 cases of knight attacks
                    a = 2
                    b = -1
                    for iter in range(8):
                        if iter == 8 / 2:
                            a = 1
                            b = -2
                        if iter % 2:
                            a = -a
                        else:
                            b = -b
                        if 0 <= r + a < __BOARD_SIZE__ and 0 <= c + b < __BOARD_SIZE__ and chrom[p][r + a][c + b] != __KNIGHT__:
                            chrom[p][r + a][c + b] = __ATTACK__
    return chrom


# def Fitness(chrom,fitness):
# calculate no. of spaces in chorm in each population in save in fitness array\


def Fitness(chrom, fitness):
    empty_spaces = 0
    for p in range(__POP__):
        for r in range(__BOARD_SIZE__):
            for c in range(__BOARD_SIZE__):
                if (chrom[p][r][c] == __EMPTY__):
                    empty_spaces += 1
        fitness[p] = empty_spaces
        empty_spaces = 0
    return fitness, int(fitness[0])


def Sorting(fitness, chrom):
    for i in range(__POP__):
        for j in range(i + 1, __POP__):
            if (fitness[i] > fitness[j]):
                fitness[i], fitness[j] = fitness[j], fitness[i]
                for k in range(__MAX__KNIGHTS__):
                    chromosome[i][k], chromosome[j][k] = chromosome[j][
                        k], chromosome[i][k]
    return fitness, chromosome


def Next_POP(chromosome):
    # crossing over time
    for k in range(0, nParents, 2):
        for i in range(0, __MAX__KNIGHTS__, 2):
            chromosome[nParents + k][i] = chromosome[k][i]
        for i in range(1, __MAX__KNIGHTS__, 2):
            chromosome[nParents + k][i] = chromosome[k + 1][i]
    for k in range(1, nParents, 2):
        for i in range(0, __MAX__KNIGHTS__, 2):
            chromosome[nParents + k][i] = chromosome[k][i]
        for i in range(1, __MAX__KNIGHTS__, 2):
            chromosome[nParents + k][i] = chromosome[k][i]
    # mutation time
    for p in range(nParents, __POP__):
        index = int(sample(range(__MAX__KNIGHTS__), 1)[0])
        value = int(sample(Possible_Positions, 1)[0])
        while(value in chromosome[p]):
            value = int(sample(Possible_Positions, 1)[0])
        chromosome[p][index] = value
    return chromosome


def Solution_Points(chromome):
    print("Knights were placed at the following points", end="")
    found_knights = 0
    for k in range(__MAX__KNIGHTS__):
        x = chromome[0][k] // __BOARD_SIZE__
        y = chromome[0][k] % __BOARD_SIZE__
        print(f"({x+1},{y+1})", end=" ")
        found_knights += 1
    print("\nNo. of knights placed in this Board were", found_knights)


# print gird
def Solution_Board(sol):
    print(Fore.CYAN, end="")
    print(" ", "-" * (2*__BOARD_SIZE__+1), sep="")
    print(" ", end="")
    for i in range(__BOARD_SIZE__):  # this will change
        print("|", i + 1, sep="", end="")
    print("|\n", "-" * (2*__BOARD_SIZE__+1))
    for i in range(__BOARD_SIZE__):
        print("", i + 1, sep="", end="")
        for j in range(__BOARD_SIZE__):
            print("|", end="")
            if (sol[i][j] == __EMPTY__):
                print(sol[i][j], end="")
            elif (sol[i][j] == __ATTACK__):
                print(Fore.RED, sol[i][j],Fore.CYAN, sep="", end="")
            elif (sol[i][j] == __KNIGHT__):
                print(Fore.MAGENTA, sol[i][j],Fore.CYAN, sep="", end="")
        print("|\n", "-" * (2*__BOARD_SIZE__+1))
    print(Fore.RESET, end="")
    print(end="")


###########main Program##########
# chrom = Board_Filler(chrom, chromosome)
# Solution_Board(chrom[0])
# random population is already generated and stored in chromosome
chrom = Board_Filler(chromosome)
for i in range(1000):
    fitness, min_fitness = Fitness(chrom, fitness)
    fitness, chromosome = Sorting(fitness, chromosome)
    # print(chromosome)
    if (i % 1 == 0):
        system("cls")
        print("Generation", i)
        print(f"most fittest individual have {fitness[0]} spaces")
        # print("Fitness",fitness)
        Solution_Board(chrom[0])
    if (min_fitness == 0):
        system("cls")
        print("Solution found at generation", i)
        Solution_Board(chrom[0])
        Solution_Points(chromosome)
        exit(0)
    chromosome = Next_POP(chromosome)
    chrom = Board_Filler(chromosome)
