

#include "Tokenizer.h"

//y = -1.5 * sin(x) + 12!;
//y = sin((x + 1) * 2);

Tokenizer::Tokenizer() {

}

Tokenizer::Tokenizer(Expression exp) {
	_context = new Context(exp);

	_context->_State_Space->setContext(_context);
	_context->_State_AlphaOrDigitOrUnderline->setContext(_context);
	_context->_State_OtherRecognizable->setContext(_context);
	//std::cout << "_context at: " << _context << std::endl;
	//std::cout << "State _ context at" << _context->_State_AlphaOrDigitOrUnderline->_context << std::endl;
}


void Tokenizer::setContext(Expression exp) {
	delete _context;
	token_table.clear();

	_context = new Context(exp);
	_context->_State_Space->setContext(_context);
	_context->_State_AlphaOrDigitOrUnderline->setContext(_context);
	_context->_State_OtherRecognizable->setContext(_context);
}

bool Tokenizer::isEnd() {
	return _context->isEnd();
}

Token Tokenizer::getNextToken() {
	Token token;
	token = _context->currentState->getNextToken();
	_context->currentState = _context->currentState->nextState();
	return token;
}

void Tokenizer::Tokenize() {
	while (!isEnd()) {
		Token tk = getNextToken();
		if (tlut.TypeOf(tk) != Invalid) {
			token_table.push_back(std::make_pair(tk, tlut.TypeOf(tk)));
		}
	}
	RegularizeTokenTable();
}

void Tokenizer::RegularizeTokenTable() {
	TokenTableElement* last = nullptr;
	for (TokenTable::iterator it = token_table.begin();
		it != token_table.end(); ++it) {
		if ( it->first == "+" ) {
			if (!last || last->first == "(") {
				it->first = "@";
				it->second = LeftUniOpt;
			}
		}
		else if (it->first == "-") {
			if (!last || last->first == "(") {
				it->first = "~";
				it->second = LeftUniOpt;
			}
		}
		last = &(*it);
	}
}

void Tokenizer::showTokenizeResult() {
	std::cout << "Tokenizer Result: ";
	for (TokenTable::iterator it = token_table.begin(); it != token_table.end(); ++it)
		std::cout << it->first << " ";
	std::cout << std::endl;
}


TokenTable Tokenizer::getTokenTable() {
	return token_table;
}

#ifdef TOKENIZER_H
int main() {
	//Tokenizer test = Tokenizer("y = sin (25*x) + 12*x + 2! - 14*(cos(15-x))");
	Tokenizer test;
	test.setContext("y = sin(25*x) + 19960610 - 12!");
	test.Tokenize();
	test.showTokenizeResult();

	test.setContext("y = -12 + tan(25*x)");
	test.Tokenize();
	test.showTokenizeResult();
	return 0;
}
#endif