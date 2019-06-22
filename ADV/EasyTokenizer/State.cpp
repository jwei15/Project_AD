
#include "State.h"

void State::setContext(Context* context) {
	_context = context;
}

bool State::isAlphaOrDigitOrUnderline(char c) {
	return ('0' <= c && '9' >= c) ||
		('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c) ||
		(c == '_');
};

bool State::isSpace(char c) {
	return c == ' ';
}

bool State::isOtherRecognizable(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '='
		|| c == '(' || c == ')';
}

Token State_AlphaOrDigitOrUnderline::getNextToken() {
	std::cout << "======= In Alpha Mode\n";
	Token token = "";
 	char c = _context->curr();
	while (isAlphaOrDigitOrUnderline(c)) {
		token += c;
		c = _context->next();	
	}
	std::cout << "	Token is: " << token << "\n	Next is: " << c << std::endl << "\n";
	return token;
}


Token State_Space::getNextToken() {
	std::cout << "\n======= In Space Mode\n";
	Token token = "";
	char c = _context->curr();
	while (isSpace(c)) {
		token += c;
		c = _context->next();
	}
	std::cout << "	Token is: " << token << "\n	Next is: "<< c <<std::endl<<"\n";
	return token;
}


Token State_OtherRecognizable::getNextToken() {
	std::cout << "\n======= In Other Mode\n";
	Token token = "";
	char c = _context->curr();
	while (isOtherRecognizable(c)) {
		token += c;
		c = _context->next();
	}
	std::cout << "	Token is: " << token << "\n	Next is: " << c << std::endl << "\n";
	return token;
}

State* State::nextState() {
	char c = _context->curr();
	if (isAlphaOrDigitOrUnderline(c)) {
		return _context->_State_AlphaOrDigitOrUnderline;
	}
	if (isSpace(c)) {
		return _context->_State_Space;
		//return new State_Space();
	}
	if (isOtherRecognizable(c)) {
		return _context->_State_OtherRecognizable;
		//return new State_OtherRecognizable();
	}
}
