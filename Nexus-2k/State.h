#pragma once
#ifndef _STATE
#define _STATE

#include <vector>

struct StateCell
{
	int stateNo, x, y, color;
};

class State
{
	int currentState, totalStates;
	std::vector<StateCell> states;
	std::vector<int> scoreStates;

public:
	State();
	void ChangeState();
	void AddToState(const int (&mBoard)[9][9], const int &score);
	void UndoState(int(&mBoard)[9][9], int &score);
	void RedoState(int(&mBoard)[9][9], int &score);
	~State();
};

#endif