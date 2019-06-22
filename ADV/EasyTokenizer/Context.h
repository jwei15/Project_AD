#pragma once

#include "State.h"
#include "Prerequisite.h"
#include <queue>

class State;
class Context {
public:
	Context(Expression exp);

	State* currentState = nullptr;

	char curr();
	char next();
	bool isEnd();


	State* _State_Space = nullptr;
	State* _State_AlphaOrDigitOrUnderline = nullptr;
	State* _State_OtherRecognizable = nullptr;
private:
	Expression _exp;
	int _index;	//To record which position we are in
	std::queue<char> char_Q;


};