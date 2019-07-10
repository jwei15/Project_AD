

#include <iostream>
#include <math.h>
#include "CalculationTree.h"

//If we ever use this constructor
//We must have guaranteed suffix is legit
//Our NaiveParser can help us with that
CalculationTree::CalculationTree(TokenTable suffix) {
	std::stack<Node*> Optr_Stack;

	for (TokenTable::iterator it = suffix.begin();
		it != suffix.end(); ++it) {
		Node* node = new Node(*it);
		if (it->second == Variable || it->second == Numeric) {
			Optr_Stack.push(node);
			continue;
		}
		else if (it->second == BinOpt) {
			Node* node_right = Optr_Stack.top();
			Optr_Stack.pop();

			Node* node_left = Optr_Stack.top();
			Optr_Stack.pop();

			node->right = node_right;
			node->left = node_left;

			Optr_Stack.push(node);
			continue;
		}
		else if (it->second == LeftUniOpt) {
			Node* node_left = Optr_Stack.top();
			Optr_Stack.pop();

			node->left = node_left;
			Optr_Stack.push(node);
			continue;
		}
	
	}
	this->root = Optr_Stack.top();
}

void CalculationTree::SuffixTraverse(Node* _node) {
	if (_node == nullptr) {
		std::cout << " ";
	}
	else {
		SuffixTraverse(_node->left);
		SuffixTraverse(_node->right);
		std::cout << _node->_tte.first << " ";
	}
}

void CalculationTree::setVariable_value(Token variable, float value) {
	std::cout << "\nVariable: " << variable << " set to value: " << value << std::endl;
	this->vTov[variable] = value;
}

float CalculationTree::eval(Node* _node) {
	Token token = _node->_tte.first;
	TokenType tokentype = _node->_tte.second;

	if (tokentype == Variable)	return vTov[token];
	if (tokentype == Numeric)	return std::stof(token);

	if (token == "+") return eval(_node->left) + eval(_node->right);
	else if (token == "-") return eval(_node->left) - eval(_node->right);
	else if (token == "*") return eval(_node->left) * eval(_node->right);
	else if (token == "/") return eval(_node->left) / eval(_node->right);
	else if (token == "sin") return sin(eval(_node->left));
	else if (token == "cos") return cos(eval(_node->left));
	else if (token == "@") return eval(_node->left);
	else if (token == "~") return 0 - eval(_node->left);
}

#ifdef CALCULATIONTREE_H
int main()
{
    std::cout << "Hello World!\n"; 
}

#endif