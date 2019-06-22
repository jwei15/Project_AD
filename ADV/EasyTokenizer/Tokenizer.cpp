

#include "Tokenizer.h"

//y = -1.5 * sin(x) + 12!;
//y = sin((x + 1) * 2);

Tokenizer::Tokenizer(Expression exp) {
	_context = new Context(exp);

	_context->_State_Space->setContext(_context);
	_context->_State_AlphaOrDigitOrUnderline->setContext(_context);
	_context->_State_OtherRecognizable->setContext(_context);
	//std::cout << "_context at: " << _context << std::endl;
	//std::cout << "State _ context at" << _context->_State_AlphaOrDigitOrUnderline->_context << std::endl;
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
}

void Tokenizer::showTokenizeResult() {
	for (TokenTable::iterator it = token_table.begin(); it != token_table.end(); ++it)
		std::cout << it->first << " ";
	std::cout << std::endl;
}


//#ifdef TOKENIZER_H
int main() {
	Tokenizer test = Tokenizer("y = sin (25*x) + 12*x + 2! - 14*(cos(15-x))");
	test.Tokenize();
	test.showTokenizeResult();
	return 0;
}
//#endif