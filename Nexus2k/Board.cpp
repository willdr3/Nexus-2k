/* *** Board Class ***
*  *** Contains: Struct of Cells, vector of freecells. Methods for initialising the board, 
*  *** detecting what value the current cell holds, wether the cell clicked on is selectable, method to call draw from the Drawer class,
*  *** detecting if cells in a row are of same value and then delete them if 5 or more, spawning new cells after move, 
*  *** creating a flicker effect on selected cell, get methods for score and high score, recalculate what cells are empty, 
*  *** store state of board and revert to previous state, set high score, move (using path taken from aStar class).
*
*  *** Deconstuctor
*/

#include "stdafx.h"
#include "Board.h"
#include "Drawer.h"
#include "aStar.h"


Board::Board()
{
	initBoard();
	random = gcnew Random();
}

void Board::initBoard()
{
	//read in high score from saved text file and store as variable
	gcroot<IO::StreamReader^> sr;
	sr = gcnew IO::StreamReader("HighScores.txt");
	highScore = Convert::ToInt32(sr->ReadLine());
	sr->Close();

	player = gcnew System::Media::SoundPlayer("clear.wav");
	gameOverPlayer = gcnew System::Media::SoundPlayer("lose.wav");
	state = new State;
	freecells.clear(); //recalculate free cells on board
	selected.x = -1;
	selected.y = -1;
	selectedOriginalColor = -1;
	score = 0;
	gameOver = false;
	
	//set all cells of board to value of 0
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			mBoard[i][j] = 0;

			//define size of each cell
			cells[i][j].x = i * BLOCK_SIZE;
			cells[i][j].y = j * BLOCK_SIZE;
		}
	}
	findCells(); //recalculate free cells on board
}

void Board::selectCell(int x, int y)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			Rectangle^ rect = gcnew Rectangle(cells[i][j].x, cells[i][j].y, BLOCK_SIZE, BLOCK_SIZE);

			//if where mouse was clicked
			if (rect->Contains(x, y))
			{
				//Set to flicker
				if (i == selected.x && j == selected.y)
				{
					selected.x = -1;
					selected.y = -1;
					mBoard[i][j] = selectedOriginalColor;
					selectedOriginalColor = -1;
				}
				else
				{
					if (mBoard[i][j] != 0)
					{
						if (selected.x != -1 && selected.y != -1)
						{
							mBoard[selected.x][selected.y] = selectedOriginalColor;
							selected.x = -1;
							selected.y = -1;
							selectedOriginalColor = -1;
						}
						selected.x = i;
						selected.y = j;
						selectedOriginalColor = mBoard[i][j];
					}
					else
					{
						Move(i, j);
					}
				}
				return;
			}
		}
	}
}

void Board::Move(int x, int y)
{
	//take route from aStar as string, pass location of 2 clicked cells
	string route = aStar::pathFind(selected.x, selected.y, x, y, mBoard);

	if (route.length() > 0)
	{
		int k; char c;
		int tempX = selected.x;
		int tempY = selected.y;
		mBoard[tempX][tempY] = 0;

		for (size_t h = 0; h < route.length(); h++)
		{
			c = route.at(h);
			k = c - '0';
			//k = Convert::ToInt16(route.at(h));   <-- Doesn't work???

			tempX = tempX + dx[k];
			tempY = tempY + dy[k];
			mBoard[tempX][tempY] = selectedOriginalColor;
			draw();
			System::Threading::Thread::Sleep(75);
			mBoard[tempX][tempY] = 0;
		}

		mBoard[tempX][tempY] = selectedOriginalColor;
		selected.x = -1;
		selected.y = -1;
		selectedOriginalColor = -1;
		findCells();

		if (!clear(tempX, tempY))
		{
			spawn();
		}
	}
}


int Board::cellContent(int x, int y)
{
	return mBoard[x][y];
}

void Board::gameRun()
{
	draw();
	selectedFlicker();
}

void Board::draw()
{
	Drawer::draw(*this);
}

bool Board::clear(int x,int y)
{
	std::vector<Cell> removeSquares;
	int tempX = x;
	int tempY = y;
	int color = mBoard[x][y];
	int tempColor = -1;
	int count = 1;
	bool result = false;

	Cell tempCell;
	tempCell.x = tempX;
	tempCell.y = tempY;
	removeSquares.push_back(tempCell);

	//Check Left
	do
	{
		tempX -= 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Check Right
	tempX = x;
	do
	{
		tempX += 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);

	if (count < 5)
	{
		for (int i = 0; i < count-1; i++)
		{
			removeSquares.pop_back();
		}
	}

	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;

	//Check Up
	do
	{
		tempY -= 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);


	//Check Down
	tempY = y;
	do
	{
		tempY += 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);

	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			removeSquares.pop_back();
		}
	}

	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;
	

	//Check UpRight
	do
	{
		tempY -= 1;
		tempX += 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);


	//Check DownLeft
	tempX = x;
	tempY = y;
	do
	{
		tempY += 1;
		tempX -= 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);
	
	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			removeSquares.pop_back();
		}
	}

	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;

	//Check UpLeft
	do
	{
		tempY -= 1;
		tempX -= 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);


	//Check DownRight
	tempX = x;
	tempY = y;
	do
	{
		tempY += 1;
		tempX += 1;
		if (tempX >= 0 && tempX < 9 && tempY >= 0 && tempY < 9)
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count += 1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				removeSquares.push_back(tempCell);
			}
		}
		else
		{
			tempColor = -1;
		}
	} while (tempColor == color);

	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			removeSquares.pop_back();
		}
	}

	//Clear the blocks to blank
	if (removeSquares.size() >= 4)
	{
		result = true;
		player->Play();
		
		//working on flicker to delete
		//****************************
		for (int i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < removeSquares.size(); j++)
			{
				if (mBoard[removeSquares[j].x][removeSquares[j].y] != selectedOriginalColor)
				{
					mBoard[removeSquares[j].x][removeSquares[j].y] = selectedOriginalColor;
					System::Threading::Thread::Sleep(25);
				}
				else
				{
					mBoard[removeSquares[j].x][removeSquares[j].y] = 7;
					System::Threading::Thread::Sleep(25);
				}
			}
		}
		//****************************
		//reaches all of this code but doesn't change colour

		for (size_t i = 0; i < removeSquares.size(); i++)
		{
			mBoard[removeSquares[i].x][removeSquares[i].y] = 0;
			score = score + 10;
		}
		findCells();
	}
	return result;
}

void Board::selectedFlicker()
{
	if (selected.x != -1 && selected.y != -1)
	{
		if (mBoard[selected.x][selected.y] != selectedOriginalColor)
		{
			mBoard[selected.x][selected.y] = selectedOriginalColor;
		}
		else
		{
			mBoard[selected.x][selected.y] = 7;
		}
	}
}

void Board::spawn()
{
	for (int i = 0; i < 3; i++)
	{
		if (!freecells.empty())
		{
			int space = random->Next(freecells.size());
			int color = random->Next(1, 7);
			mBoard[freecells[space].x][freecells[space].y] = color;

			int tempX = freecells[space].x;
			int tempY = freecells[space].y;
			findCells();
			clear(tempX, tempY);

			if (freecells.empty())
			{
				setHighScore();
				gameOverPlayer->Play();
				gameOver = true;
				return;
			}
		}
		else
		{
			setHighScore();
			gameOverPlayer->Play();
			gameOver = true;
			return;
		}
	}
	state->ChangeState();
	state->AddToState(mBoard, score);
}

void Board::findCells()
{
	freecells.clear();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mBoard[i][j] == 0)
			{
				Cell tempCell;
				tempCell.x = i;
				tempCell.y = j;

				freecells.push_back(tempCell);
			}
		}
	}
}

void Board::undo()
{
	state->UndoState(mBoard, score);
	findCells();
}

void Board::setHighScore()
{
	gcroot<IO::StreamReader^> sr;
	sr = gcnew IO::StreamReader("HighScores.txt");
	highScore = Convert::ToInt32(sr->ReadLine());
	sr->Close();

	gcroot<IO::StreamWriter^> sw;
	sw = gcnew IO::StreamWriter("HighScores.txt");

	if (score > highScore)
	{
		sw->WriteLine(score);
	}
	sw->Close();
}

Board::~Board()
{
	delete random;
	delete[] & mBoard;
	delete[] & cells;
	freecells.clear();
	delete & selected;
	delete & selectedOriginalColor;
	delete state;
}
