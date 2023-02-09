#include <iostream>
#include <vector>
#include <tgmath.h>
#include "VectorCoords.h"

using namespace std;

void clearScreen();

void printMTX(vector<vector<int>> maze, int solX, int solY);

int countMoves(vector<vector<int>> maze);

bool BacktrackerHighPrecision(vector<vector<int>>& maze, int initX, int initY, VectorCoords dest, int direction);

bool BacktrackerDT(vector<vector<int>>& mazeMatrix, int initX, int initY, VectorCoords dest, int direction);