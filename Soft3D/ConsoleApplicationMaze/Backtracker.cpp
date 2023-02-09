#include "Backtracker.h"

void clearScreen() {
#ifndef _WIN32
	for (int i = 0; i < 20; i++) {
		cout << std::endl;
	}
#else
	system("CLS");
#endif
}

void printMTX(vector<vector<int>> maze, int solX, int solY) {
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			if (j == solX && i == solY && maze[solY][solX] == 1) {
				cout << "\u001b[" << 40 + 2 << ";" << "1m" << " ";
				//cout << "A";
			}

			//cout << maze[i][j] << "";
			cout << "\u001b[" << 40 + maze[i][j] << ";" << "1m" << " ";
			cout << "\033[0m";
		}
		std::cout << '\n';
		cout << "\033[0m";
	}

	std::cout << '\n';
}

int countMoves(vector<vector<int>> maze) {
	int moves = 0;
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			if (maze[i][j] == 6) {
				moves++;
			}
		}
	}

	return moves;
}

bool BacktrackerHighPrecision(vector<vector<int>>& maze, int initX, int initY, VectorCoords dest, int direction) {
	if (initX < 0 || initY < 0) {
		return false;
	}
	else if (initY >= maze.size()) {
		return false;
	}
	else if (initX >= maze[initY].size()) {
		return false;
	}
	else if (maze[initY][initX] != 1) {
		return false;
	}
	else if (initX == dest.x && initY == dest.y) {
		return true;
	}
	else {
		maze[initY][initX] = 6;
		//clearScreen();
		//printMTX(maze, dest.x, dest.y);

		if ((direction != -1 && BacktrackerHighPrecision(maze, initX + 1, initY, dest, 0))) {
			//std::cout << "Call 1";
			return true;
		}
		else if (direction != -2 && BacktrackerHighPrecision(maze, initX, initY + 1, dest, 1)) {
			//std::cout << "Call 2";
			return true;
		}
		else if (direction != 0 && BacktrackerHighPrecision(maze, initX - 1, initY, dest, -1)) {
			//	std::cout << "Call 3";
			return true;
		}
		else if (direction != 1 && BacktrackerHighPrecision(maze, initX, initY - 1, dest, -2)) {
			//	std::cout << "Call 4";
			return true;
		}

		return false;
	}
}

bool BacktrackerDT(vector<vector<int>>& maze, int initX, int initY, VectorCoords dest, int direction) {
	if (initX < 0 || initY < 0) {
		return false;
	}
	else if (initY >= maze.size()) {
		return false;
	}
	else if (initX >= maze[initY].size()) {
		return false;
	}
	else if (maze[initY][initX] != 1) {
		return false;
	}
	else if (initX == dest.x && initY == dest.y) {
		return true;
	}
	else {
		//std::cout << "Direction: " << direction << '\n';

		int directionDX = dest.x - initX;
		int directionDY = dest.y - initY;

		maze[initY][initX] = 6;

		//clearScreen();
		//printMTX(maze,dest.x, dest.y);

		// RIGHT-DOWN

		if (directionDX >= 0 && directionDY >= 0) {
			if (directionDX >= directionDY) {
				if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//std::cout << "Call 1";
					return true;
				}
				else if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//std::cout << "Call 2";
					return true;
				}
				else if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
			else {
				if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//std::cout << "Call 1";
					return true;
				}
				else if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//std::cout << "Call 2";
					return true;
				}
				else if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
		}
		// RIGHT-UP
		else if (directionDX >= 0 && directionDY <= 0) {
			if (directionDX >= -directionDY) {
				if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//std::cout << "Call 1";
					return true;
				}
				else if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//std::cout << "Call 2";
					return true;
				}
				else if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
			else {
				if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//std::cout << "Call 1";
					return true;
				}
				else if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//std::cout << "Call 2";
					return true;
				}
				else if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
		}
		// LEFT UP
		else if (directionDX <= 0 && directionDY <= 0) {
			if (-directionDX >= -directionDY) {
				if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//std::cout << "Call 1";
					return true;
				}
				else if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//std::cout << "Call 2";
					return true;
				}
				else if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
			else {
				if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//std::cout << "Call 1";
					return true;
				}
				else if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//std::cout << "Call 2";
					return true;
				}
				else if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
		}
		// LEFT-DOWN
		else if (directionDX <= 0 && directionDY >= 0) {
			if (-directionDX >= directionDY) {
				if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//std::cout << "Call 1";
					return true;
				}
				else if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//std::cout << "Call 2";
					return true;
				}
				else if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
			else {
				if (direction != -2 && BacktrackerDT(maze, initX, initY + 1, dest, 1)) {
					//std::cout << "Call 1";
					return true;
				}
				else if (direction != 0 && BacktrackerDT(maze, initX - 1, initY, dest, -1)) {
					//std::cout << "Call 2";
					return true;
				}
				else if ((direction != -1 && BacktrackerDT(maze, initX + 1, initY, dest, 0))) {
					//	std::cout << "Call 3";
					return true;
				}
				else if (direction != 1 && BacktrackerDT(maze, initX, initY - 1, dest, -2)) {
					//	std::cout << "Call 4";
					return true;
				}
			}
		}

		maze[initY][initX] = 4;
		return false;
	}
}