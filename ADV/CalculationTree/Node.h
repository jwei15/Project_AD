#pragma once

#include "../EasyTokenizer/Prerequisite.h"

class Node {
public:
	Node();
	~Node();

	TokenType type;
	
	Node* left = nullptr;
	Node* right = nullptr;
};

class Tree {
public:
	Tree();
	~Tree();

	float eval(Node root, float x);
private:
	Node* _root;
};

float Tree::eval(Node root, float x) {
	if (TokenType != )
}