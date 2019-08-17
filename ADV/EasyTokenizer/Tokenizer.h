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
	Tokenizer();
	Tokenizer(Expression exp);

	Token getNextToken();

	void setContext(Expression exp);
	void Tokenize();

	bool isEnd();

	void RegularizeTokenTable();
	void showTokenizeResult();


	TokenTable getTokenTable();
private:
	Context* _context;
	TokenLookUpTable tlut;
	TokenTable token_table;
};

