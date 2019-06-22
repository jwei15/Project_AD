
#include "Context.h"

Context::Context(Expression exp) {
	_exp = exp;
	_index = 0;
	
	_State_Space = new State_Space();
	_State_AlphaOrDigitOrUnderline = new State_AlphaOrDigitOrUnderline();
	_State_OtherRecognizable = new State_OtherRecognizable();

	currentState = _State_Space;
}

char Context::curr() {
	return _exp[_index];
}

char Context::next() {
	if (isEnd())
		return '#';
	return _exp[++_index];
}

bool Context::isEnd() {
	return _index == _exp.size();
}