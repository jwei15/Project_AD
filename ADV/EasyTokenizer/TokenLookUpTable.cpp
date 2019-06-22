
#include "TokenLookUpTable.h"

//	<------- Constructor that initialized with some pre-defined optrs ------->

TokenLookUpTable::TokenLookUpTable() {
	//where Left Uniary Operator belongs 
	opt_lookup_table.insert(std::make_pair("sin", LeftUniOpt));
	opt_lookup_table.insert(std::make_pair("cos", LeftUniOpt));
	opt_lookup_table.insert(std::make_pair("tan", LeftUniOpt));
	opt_lookup_table.insert(std::make_pair("sqrt", LeftUniOpt));
	opt_lookup_table.insert(std::make_pair("~", LeftUniOpt));	//stands for negative
	opt_lookup_table.insert(std::make_pair("@", LeftUniOpt));	//stands for positive

	//where Right Uniary Operator belongs
	opt_lookup_table.insert(std::make_pair("!", RightUniOpt));	//fact

	//where Binary Operator belongs
	opt_lookup_table.insert(std::make_pair("+", BinOpt));
	opt_lookup_table.insert(std::make_pair("-", BinOpt));
	opt_lookup_table.insert(std::make_pair("*", BinOpt));
	opt_lookup_table.insert(std::make_pair("/", BinOpt));
	opt_lookup_table.insert(std::make_pair("=", BinOpt));


	opt_lookup_table.insert(std::make_pair("(", L_parentheis));
	opt_lookup_table.insert(std::make_pair(")", R_parenthesis));

}

//	<------- If this token is a number ------->

bool TokenLookUpTable::isNumeric(std::string token) {
	return std::regex_match(token, std::regex("([1-9][0-9]*)(.*)([0-9]+)"));
}

//	<------- If this token is a vairable ------->

bool TokenLookUpTable::isVariable(std::string token) {
	return std::regex_match(token, std::regex("[_a-zA-Z][_a-z0-9A-Z]*"));
}

//	<------- return the type of a token ------->

TokenType TokenLookUpTable::TypeOf(std::string token) {
	if (opt_lookup_table.find(token) != opt_lookup_table.end()) {
		return  opt_lookup_table[token];
	}
	else if (isNumeric(token)) {
		return Numeric;
	}
	else if (isVariable(token)) {
		return Variable;
	}
	return Invalid;
}


//	<------- test stub for TokenLookUpTable ------->


#ifdef TOKENLOOKUPTABLE_H

int main() {
	TokenLookUpTable* ttlt = new TokenLookUpTable();
	std::cout << ttlt->TypeOf("_thereisacow1337") << std::endl;
	std::cout << ttlt->TypeOf("+") << std::endl;
	delete ttlt;
	return 0;
}

#endif