#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

int main(void)
{

    int choice, row, firstSpot, secondSpot;
    char rowInput;

    int x = 0, y = 0;

    printf("*Create Breadboard*\nMax:20x20 | Min:3x3\n");
    while (1)
    {
        if (y < 3 || y > 20)
        {
            printf("Enter height (max 20) : ");
            scanf("%d", &y);
        }
        else if (x < 3 || x > 20)
        {
            printf("Enter width : ");
            scanf("%d", &x);
        }
        else
        {
            break;
        }
    }

    array board[y][x];

    createArray(y, x, board);

    while (1)
    {
        clearBoard(y, x, board);
        menu();
        printf("-> ");
        getc(stdin);
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("Invalid input\n");
            break;

        case 1:
            // Show breadboard
            printf("\n");
            showBoard(y, x, board);
            break;

        case 2:
            // Add resistor
            printf("\n");
            showBoard(y, x, board);
            printf("\nRow: ");
            getc(stdin);
            scanf("%c", &rowInput);
            printf("First point: ");
            scanf("%d", &firstSpot);
            printf("Second point: ");
            scanf("%d", &secondSpot);
            row = rowInput - 65;

            if (row > 30)
            {
                printf("\nYou can only use capital letters!!\n");
            }
            else if (row > y - 1 || row < 0 || firstSpot > x || firstSpot - 1 < 0 || secondSpot > x || secondSpot - 1 < 0)
            {
                printf("\nInvalid input, breadboard is %dx%d!\n", x, y);
            }
            else if (firstSpot == secondSpot)
            {
                printf("\nInvalid input!\n - Can't put in same place..\n");
            }
            else
            {
                add(y, x, row, firstSpot, secondSpot, board);
            }
            break;

        case 3:
            // Remove resistor
            printf("\n");
            showBoard(y, x, board);
            printf("\nRow: ");
            getc(stdin);
            scanf("%c", &rowInput);
            printf("Resistor position : ");
            scanf("%d", &firstSpot);
            row = rowInput - 65;

            if (row > 30)
            {
                printf("\nYou can only use capital letters!!\n");
            }
            else if (row > y - 1 || row < 0 || firstSpot - 1 < 0 || firstSpot > x)
            {
                printf("\nInvalid input, breadboard is %dx%d!\n", x, y);
            }
            else
            {
                removeC(y, x, row, firstSpot, board);
            }
            break;

        case 4:
            // Check connection
            printf("\n");
            showBoard(y, x, board);
            printf("\nFirst point\nRow: ");
            getc(stdin);
            scanf("%c", &rowInput);
            printf("Column: ");
            scanf("%d", &firstSpot);
            row = rowInput - 65;
            board[row][firstSpot - 1].connection = true;

            printf("\nSecond point\nRow: ");
            getc(stdin);
            scanf("%c", &rowInput);
            printf("Column: ");
            scanf("%d", &secondSpot);
            row = rowInput - 65;
            board[row][secondSpot - 1].connection = true;

            printf("\n");
            showBoard(y, x, board);
            checkConnection(y, x, firstSpot - 1, secondSpot - 1, board);
            break;

        case 5:
            // Removes every resistor
            createArray(y, x, board);
            printf("\n");
            showBoard(y, x, board);
            printf("\nBreadboard cleared.\n");
            break;

        case 6:
            return 0;

        default:
            printf("Invalid input\n");
        }
    }
    return 0;
}
