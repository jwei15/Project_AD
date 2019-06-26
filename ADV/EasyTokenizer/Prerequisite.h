#pragma once

#include <map>
#include <vector>
#include <string>

enum TokenType {
	LeftUniOpt,
	RightUniOpt,
	BinOpt,
	Numeric,
	Variable,
	L_parentheis,
	R_parenthesis,
	Invalid
};

using Expression = std::string;
using Token = std::string;
using TokenTable = std::vector<std::pair<Token, TokenType>>;
using TokenTableElement = std::pair<Token, TokenType>;