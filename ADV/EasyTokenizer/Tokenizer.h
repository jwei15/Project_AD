#pragma once

#include "Context.h"
#include "TokenLookUpTable.h"

#include <vector>
#include <string>
#include <queue>
#include <iostream>


//A tokenizer will deal with the entire expression
class Tokenizer {
public:
	Tokenizer(Expression exp);

	Token getNextToken();

	void Tokenize();

	bool isEnd();

	void showTokenizeResult();
private:
	Context* _context;
	TokenLookUpTable tlut;
	TokenTable token_table;
};

