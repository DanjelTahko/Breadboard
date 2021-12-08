#include <stdbool.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{

    char place, pos;
    bool right, left, latest, connection;

} array;

void clearBoard(int y, int x, array board[y][x]);

void createArray(int y, int x, array board[y][x]);

void repeat(char *string, int count);

void showBoard(int y, int x, array board[y][x]);

void add(int y, int x, int row, int firstSpot, int secondSpot, array board[y][x]);

void removeC(int y, int x, int row, int column, array board[y][x]);

void checkConnection(int y, int x, int column, int goal, array board[y][x]);

void menu();

#endif