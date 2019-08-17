#pragma once

#include "../EasyTokenizer/TokenLookUpTable.h"
#include "../EasyTokenizer/Prerequisite.h"

struct Node {
public:
	Node(TokenTableElement tte) { _tte = tte; }
	~Node();
	TokenTableElement _tte;
	Node* left = nullptr;
	Node* right = nullptr;
};

