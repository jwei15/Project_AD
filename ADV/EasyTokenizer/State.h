#pragma once

#include "Context.h"
#include "Prerequisite.h"

#include <iostream>

class Context;
class State {
public:
	virtual Token getNextToken() = 0;
	State* nextState();
	void setContext(Context* context);
	Context* _context ;

	bool isAlphaOrDigitOrUnderline(char c);
	bool isSpace(char c);
	bool isOtherRecognizable(char c);
};

class State_AlphaOrDigitOrUnderline : public State {
	Token getNextToken() override;
};


class State_Space : public State {
	Token getNextToken() override;
};

class State_OtherRecognizable : public State {
	Token getNextToken() override;
};