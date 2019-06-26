#pragma once

#include <map>
#include <regex>
#include <iostream>

#include "Prerequisite.h"

class TokenLookUpTable {
public:
	TokenLookUpTable();

	bool isVariable(std::string token);
	bool isNumeric(std::string token);

	TokenType TypeOf(std::string token);

private:
	std::map<std::string, TokenType> opt_lookup_table;	
};

