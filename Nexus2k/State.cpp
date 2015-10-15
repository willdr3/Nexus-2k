#include "stdafx.h"
#include "State.h"


State::State()
{
	currentState = -1;
	totalStates = -1;
}

void State::ChangeState()
{
	currentState = currentState + 1;
	totalStates = totalStates + 1;
}

//takes current state of board, and score, stores them in vectors
void State::AddToState(const int(&mBoard)[9][9], const int &score)
{
	if (currentState < totalStates)
	{
		int count = 0;

		for (size_t i = 0; i < states.size(); i++)
		{
			if (states[i].stateNo < currentState)
			{
				count = count + 1;
			}
		}

		states.erase(states.begin() + count, states.end());

		scoreStates.erase(scoreStates.begin() + currentState, scoreStates.end());

		totalStates = currentState;
	}

	//iterate through board storing each cells value
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if (mBoard[i][j] > 0)
			{
				StateCell tempCell;
				tempCell.stateNo = currentState;
				tempCell.x = i;
				tempCell.y = j;
				tempCell.color = mBoard[i][j];
				states.push_back(tempCell);
			}
		}
	}
	
	//store score
	scoreStates.push_back(score);
}

//method to retrieve boards states from one turn back in the vectors
void State::UndoState(int(&mBoard)[9][9], int &score)
{
	if (currentState > 0)
	{
		currentState = currentState - 1;

		//set all board values to 0
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				mBoard[i][j] = 0;
			}
		}

		//reset board values according to vector
		for (size_t i = 0; i < states.size(); i++)
		{
			if (states[i].stateNo == currentState)
			{
				mBoard[states[i].x][states[i].y] = states[i].color;
			}
		}

		score = scoreStates[currentState];
	}
	else
	{
		//if at start of vector
		System::Windows::Forms::MessageBox::Show("Game start reached, cannot undo any further.");
	}
}

State::~State()
{
	states.clear();
	scoreStates.clear();
	delete &totalStates;
	delete &currentState;
	delete[] &states;
	delete[] &scoreStates;
}
