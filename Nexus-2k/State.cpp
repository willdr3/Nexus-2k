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
	
	scoreStates.push_back(score);
}

void State::UndoState(int(&mBoard)[9][9], int &score)
{
	if (currentState > 0)
	{
		currentState = currentState - 1;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				mBoard[i][j] = 0;
			}
		}

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
