#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Removes all "flags" from array/struct (right, left, latest, place)
void clearBoard(int y, int x, array board[y][x])
{

    for (int row = 0; row < y; row++)
    {
        for (int column = 0; column < x; column++)
        {
            board[row][column].latest = false;
            board[row][column].right = false;
            board[row][column].left = false;
            board[row][column].connection = false;
        }
    }
}

// Creates empty array / erases everything
void createArray(int y, int x, array board[y][x])
{
    for (int i = 0; i < y; i++)
    {
        for (int k = 0; k < x; k++)
        {
            board[i][k].place = ' ';
        }
    }
}

// Repeats string "----"
void repeat(char *string, int count)
{

    for (int i = 0; i < count; i++)
    {
        printf("%s", string);
    }
    printf("\n");
}

// Shows breadboard
void showBoard(int y, int x, array board[y][x])
{

    int *ascii = (int *)malloc(sizeof(int));

    if (ascii != NULL)
    {

        *ascii = 65;

        // numbers at the top
        for (int i = 1; i < x + 1; i++)
        {
            if (i == 1)
            {
                printf("    %d  ", i);
                // double-digits
            }
            else if (i >= 10)
            {
                printf(" %d ", i);
                // numbers between 2 - 9
            }
            else
            {
                printf(" %d  ", i);
            }
        }
        printf("\n  ");

        // breadboard
        for (int i = 0; i < y; i++)
        {
            repeat(" ---", x);
            // Prints char instead of int at row
            printf("%c ", *ascii);
            *ascii += 1;
            for (int j = 0; j < x; j++)
            {
                printf("| %c ", board[i][j].place);
            }
            printf("|\n  ");
        }
        repeat(" ---", x);
        free(ascii);
    }
    else
    {
        printf("Out of memory\n");
    }
}

// Adds resistor to breadboard/array
void add(int y, int x, int row, int input_1, int input_2, array board[y][x])
{

    int *spots = (int *)malloc(2 * sizeof(int));

    if (spots != NULL)
    {

        bool empty = true;
        // wich input is greater
        if (input_1 > input_2)
        {
            spots[0] = input_2;
            spots[1] = input_1;
        }
        else
        {
            spots[0] = input_1;
            spots[1] = input_2;
        }

        for (int i = spots[0] - 1; i < spots[1]; i++)
        {
            if (board[row][i].place != ' ')
            {
                empty = false;
                break;
            }
        }

        if (empty)
        {
            for (int i = spots[0] - 1; i < spots[1]; i++)
            {
                if (i == spots[0] - 1 || i == spots[1] - 1)
                {
                    board[row][i].place = '+';
                }
                else
                {
                    board[row][i].place = '-';
                }
            }
            board[row][spots[0] - 1].pos = 'R';
            board[row][spots[1] - 1].pos = 'L';
        }
        else
        {
            printf("Already existing resistor..");
        }
        free(spots);
    }
    else
    {
        printf("Out of memory\n");
    }
}

// Removes resistor from breadboard/array
void removeC(int y, int x, int row, int column, array board[y][x])
{

    if (board[row][column - 1].pos == 'R')
    {
        for (int i = column - 1; board[row][i].place != ' '; i++)
        {
            board[row][i].place = ' ';
        }
    }
    else if (board[row][column - 1].pos == 'L')
    {
        for (int i = column - 1; board[row][i].place != ' '; i--)
        {
            board[row][i].place = ' ';
        }
    }
    else
    {
        printf("Nothing there..\n");
    }
}

// Shows menu-choice
void menu()
{

    printf("\n----------------------\n");
    printf("1. Show breadboard\n");
    printf("2. Add\n");
    printf("3. Remove\n");
    printf("4. Check connection\n");
    printf("5. Clear board\n");
    printf("6. Quit\n");
    printf("----------------------\n");
}

// Checks if temporary place in breadboard/array has more resistors in that column (val array)
bool value(int column, int count, int *val)
{

    for (int i = 0; i < count; i++)
    {
        if (column == val[i])
        {
            return true;
        }
    }
    return false;
}

// Checking connection between two points
void checkConnection(int y, int x, int column, int goal, array board[y][x])
{

    int val[x], count = 0, valCount = 0, loopCount = 0;
    bool active = true;

    // Adds columns with 2 or more resistors / inputs points
    for (int i = 0; i < x; i++)
    {
        for (int k = 0; k < y; k++)
        {
            if (board[k][i].place == '+')
            {
                count += 1;
            }
            if (board[k][i].connection == true)
            {
                count += 1;
            }
        }
        if (count >= 2)
        {
            val[valCount] = i;
            valCount++;
        }
        count = 0;
    }

    while (active)
    {

        if (column == goal)
        {
            printf("\n * CONNECTION FOUND!!\n");
            active = false;
            break;
        }
        else if (loopCount > 2)
        {
            printf("\n * CONNECTION NOT FOUND!!\n");
            active = false;
            break;
        }

        // Loops every row
        for (int row = 0; row < y; row++)
        {
            // Checks if resistor and that it wasnt latest
            if (board[row][column].place == '+' && board[row][column].latest == false)
            {
                // If resistor pos right & not already checked right
                if (board[row][column].pos == 'R' && board[row][column].right != true)
                {
                    board[row][column].right = true;
                    loopCount = 0;
                    column++;
                    // Loops every column until end of resistor
                    for (; column < x; column++)
                    {
                        if (board[row][column].place == '+' && value(column, valCount, val) == true)
                        {
                            board[row][column].latest = true;
                            break;
                        }
                        else if (board[row][column].place == '+' && value(column, valCount, val) == false)
                        {
                            column--;
                            // Going back if no more resistors in that column
                            for (; column >= 0; column--)
                            {
                                if (board[row][column].place == '+')
                                {
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                // If resistor pos left & not already checked left
                else if (board[row][column].pos == 'L' && board[row][column].left != true)
                {
                    board[row][column].left = true;
                    loopCount = 0;
                    column--;
                    // Loops every column until end of resistor
                    for (; column >= 0; column--)
                    {
                        if (board[row][column].place == '+' && value(column, valCount, val) == true)
                        {
                            board[row][column].latest = true;
                            break;
                        }
                        else if (board[row][column].place == '+' && value(column, valCount, val) == false)
                        {
                            column++;
                            // Going back if no more resistors in that column
                            for (; column < x; column++)
                            {
                                if (board[row][column].place == '+')
                                {
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            // Checks if already been at every resistor in that column
            else if (row + 1 == y)
            {
                loopCount += 1;
                for (int i = 0; i < y; i++)
                {
                    if (board[i][column].latest == true)
                    {
                        board[i][column].latest = false;
                    }
                }
                break;
            }
        }
    }
}
