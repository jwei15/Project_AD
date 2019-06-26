#pragma once

#include "../EasyTokenizer/TokenLookUpTable.h"
#include "../EasyTokenizer/Prerequisite.h"

class Node {
public:
	Node();
	~Node();

private:
	TokenTableElement* _tte;
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
