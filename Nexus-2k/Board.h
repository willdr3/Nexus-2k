#pragma once
#ifndef _BOARD
#define _BOARD

#define BLOCK_SIZE 40
#define BOARD_WIDTH 9
#define BOARD_HEIGHT 9

#include <vcclr.h>
#include <vector>
#include "State.h"

using namespace std;
using namespace System;

struct Cell
{
	int x;
	int y;
};

class Board
{
	Cell cells[BOARD_WIDTH][BOARD_HEIGHT];
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	vector<Cell> freecells;
	gcroot<Random^> random;
	Cell selected;
	State *state;
	int selectedOriginalColor;
	int score;
	int highScore;
	bool gameOver;
public:
	Board();
	int cellContent(int, int);
	void selectCell(int x, int y);
	void initBoard();
	void draw();
	bool clear(int, int);
	void spawn();
	void selectedFlicker();
	void gameRun();
	const int getScore() { return score; };
	const int getHighScore() { return highScore; };
	void clearCells();
	void undo();
	void setHighScore();
	~Board();
};

#endif