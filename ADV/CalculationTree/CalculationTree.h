#pragma once


#include <iostream>
#include <stack>
#include "Node.h"

//	<------- A calculation tree takes in a suffix, and forms a tree ------->
class CalculationTree {
public:
	CalculationTree(TokenTable suffix);


	void PreffixTraverse();
	void InffixTraverse();
	void SuffixTraverse(Node* _node);

	void setVariable_value(Token variable, float value);

	float eval(Node* _node);
	Node* root = nullptr;
private:
	std::map<Token, float> vTov;
};