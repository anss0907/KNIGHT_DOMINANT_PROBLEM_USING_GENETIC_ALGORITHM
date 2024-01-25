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
Possible_Positions = [
    i for i in range(__BOARD_SIZE__ * __BOARD_SIZE__)
    if 0 < i // __BOARD_SIZE__ < 7 and 0 < i % __BOARD_SIZE__ < 7
]
# Boardis for fitness funciton whereas chromosome is to generate random population
# this is equiavalent to reset the boards
chromosome = [
    sample(Possible_Positions, __MAX__KNIGHTS__) for p in range(__POP__)
]
# This is equivalent to generate first random population
fitness = [None for i in range(__POP__)]
# half of population will be parents
nParents = __POP__ // 2

Board= [[[" " for i in range(__BOARD_SIZE__)] for c in range(__BOARD_SIZE__)]
         for p in range(__POP__)]
# first random populatin generated


def Board_Filler(chromosome):
    Board= [[[" " for i in range(__BOARD_SIZE__)]
              for c in range(__BOARD_SIZE__)] for p in range(__POP__)]
    for p in range(__POP__):
        for k in range(__MAX__KNIGHTS__):
            row = chromosome[p][k] // __BOARD_SIZE__
            col = chromosome[p][k] % __BOARD_SIZE__
            Board[p][row][col] = __KNIGHT__
    for p in range(__POP__):
        for r in range(__BOARD_SIZE__):
            for c in range(__BOARD_SIZE__):
                if (Board[p][r][c] == __KNIGHT__):
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
                        if 0 <= r + a < __BOARD_SIZE__ and 0 <= c + b < __BOARD_SIZE__ and Board[
                                p][r + a][c + b] != __KNIGHT__:
                            Board[p][r + a][c + b] = __ATTACK__
    return Board


def Fitness(Board, chromosome, fitness):
    for p in range(__POP__):
        empty_spaces = sum(Board[p][r].count(__EMPTY__)
                           for r in range(__BOARD_SIZE__))
        fitness[p] = empty_spaces
    zipped = sorted(zip(fitness, chromosome))
    fitness, chromosome = zip(*zipped)
    return list(chromosome), list(fitness), fitness[0]


def Next_POP(chromosome):
    # crossing over time
    for k in range(0, nParents, 2):
        chromosome[nParents + k] = [
            chromosome[k + 1][i] if i % 2 else chromosome[k][i]
            for i in range(__MAX__KNIGHTS__)
        ]
    for k in range(1, nParents, 2):
        chromosome[nParents + k] = [
            chromosome[k - 1][i] if i % 2 else chromosome[k][i]
            for i in range(__MAX__KNIGHTS__)
        ]
    # mutation time
    for p in range(nParents, __POP__):
        index = sample(range(__MAX__KNIGHTS__), 1)[0]
        value = sample(Possible_Positions, 1)[0]
        while value in chromosome[p]:
            value = sample(Possible_Positions, 1)[0]
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
    print(" ", "-" * (2 * __BOARD_SIZE__ + 1), sep="")
    print(" ", end="")
    for i in range(__BOARD_SIZE__):  
        print("|", chr(i+97), sep="", end="") # chr(i+97) to print ascii values
    print("|\n", "-" * (2 * __BOARD_SIZE__ + 1))
    for i in range(__BOARD_SIZE__):
        print("", i + 1, sep="", end="")
        for j in range(__BOARD_SIZE__):
            print("|", end="")
            if (sol[i][j] == __EMPTY__):
                print(sol[i][j], end="")
            elif (sol[i][j] == __ATTACK__):
                print(Fore.RED, sol[i][j], Fore.CYAN, sep="", end="")
            elif (sol[i][j] == __KNIGHT__):
                print(Fore.MAGENTA+ "\u265E"+ Fore.CYAN, sep="", end="")
        print("|\n", "-" * (2 * __BOARD_SIZE__ + 1))
    print(Fore.RESET, end="")
    print(end="")


###########main Program##########
# Board= Board_Filler(Board, chromosome)
# Solution_Board(Board[0])
# random population is already generated and stored in chromosome
Board= Board_Filler(chromosome)
for i in range(200):
    chromosome, fitness, min_fitness = Fitness(Board, chromosome, fitness)
    Board= Board_Filler(chromosome)
    # print(chromosome)
    if (i % 1 == 0):
        system("cls")
        print("Generation", i)
        print(f"most fittest individual have {fitness[0]} spaces")
        # print("Fitness",fitness)
        Solution_Board(Board[0])
    if (min_fitness == 0):
        system("cls")
        print("Solution found at generation", i)
        Solution_Board(Board[0])
        Solution_Points(chromosome)
        exit(0)
    chromosome = Next_POP(chromosome)
    Board= Board_Filler(chromosome)
