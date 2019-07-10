#pragma once


// When I say this is a naive parser, it means it is naive
// only suffix expression are involed, given that we are only discussing very simple expressions

#include <stack>

#include "../EasyTokenizer/Prerequisite.h"
#include "../EasyTokenizer/Tokenizer.h"
#include "../CalculationTree/CalculationTree.h"

using Priority = int;

class NaiveParser {
public:
	NaiveParser();

	void setExpression(TokenTable Inffix);

	//Translate inffix expression to suffix expression
	//Due to the amibiguity of some optrs, we have to do some transformation in the meantime
	//For example, '-'(negative, not minus) to '~', 
	//			   '+'(positive, not add) to '@'
	
	//Dijkstra hates quick and dirty methods, but I have no better idea
	void inffToSuffix();

	void showSuffix();
	bool ValidityIsGood();

	TokenTable get_suffix() { return _suffix;};
private:
	TokenTable _inffix;
	TokenTable _suffix;

	bool ValidityHelperFlag = true;
	int ValidityHelperIndex = 0;
	Token CurrentContent;
	TokenType CurrentType;

	void Next();

	void D();
	void E();
	void T();
	void F();


	Priority PriorityOf(Token opt);
};