


#include <iostream>
#include "NaiveParser.h"
#include "../EasyTokenizer/TokenLookUpTable.h"

NaiveParser::NaiveParser(){
}

void NaiveParser::setExpression(TokenTable inffix) {
	this->_inffix = inffix;
	CurrentContent = _inffix[ValidityHelperIndex].first;
	CurrentType = _inffix[ValidityHelperIndex].second;
}

void NaiveParser::Next() {
	if (ValidityHelperIndex < _inffix.size() - 1) {
		ValidityHelperIndex++;
		CurrentContent = _inffix[ValidityHelperIndex].first;
		CurrentType = _inffix[ValidityHelperIndex].second;
		std::cout << "current content: " << CurrentContent ;
	}
	else {
		CurrentContent = "#";
		CurrentType = Invalid;
	}
}


//	<------- Before you read this function, please read the README.md file to see how the BNF looks like >-------
//	<------- Sorry that I don't have a better way to make sure that you know what the codes are for>-------
//	<------- To make it easy and clear, just believe that any valid expression should pass the E() ------->
bool NaiveParser::ValidityIsGood() {
	//Next();
	E();
	std::cout << ValidityHelperIndex << std::endl;
	return (ValidityHelperFlag == true && ValidityHelperIndex == _inffix.size() - 1);
}



void NaiveParser::E(){
	std::cout << "In E: " << CurrentContent << std::endl;
	T();	//see if T() can modify the helpervalue accordingly
	
	if (CurrentContent == "+" || CurrentContent == "-") {
		Next();
		T();
	}
}


void NaiveParser::T() {
	std::cout << "In T: " << CurrentContent << std::endl;
	F();
	
	//while (CurrentContent == "*" || CurrentContent == "/") {
	if (CurrentContent == "*" || CurrentContent == "/") {
		Next();
		F();
	}
	
}


//What a F looks like?
//F --> (E)|L(E)|ER|D
void NaiveParser::F() {
	std::cout << "In F(): " << _inffix[ValidityHelperIndex].first << std::endl;
	//case D|DR
	if (CurrentType == Numeric || CurrentType == Variable) {
		Next();
		if (CurrentType == RightUniOpt) {
			Next();
		}
	}
	//case (E)
	else if (CurrentContent == "("){
		Next();
		E();
		//Next();
		if (CurrentContent == ")") 
			Next();
		else {
			std::cout << " set false in (e) ";
			ValidityHelperFlag = false;
		}
	}
	//case L (E)
	else if (CurrentType == LeftUniOpt) {
		Next();
		if (CurrentContent == "(") {
			Next();
			E();
			//Next();
			if (CurrentContent == ")")
				Next();
			else {
				std::cout << " set false in le";
				ValidityHelperFlag = false;
			}
		}
	}
	else {
		std::cout << " set false ";
		ValidityHelperFlag = false;
	}
}


//Please do not touch this, a naive parser is also a fragile parser

void NaiveParser::inffToSuffix() {
	std::stack<TokenTableElement> optrS;
	for (int i = 0; i < _inffix.size(); ++i) {
		TokenTableElement tte = _inffix[i];
		std::cout << "Dealing with " << tte.first<<std::endl;
		//std::cout<<" OptrS size: "<< optrS.size() << std::endl;
		//Left Unary Opt should go directly to optrS
		if (tte.second == LeftUniOpt) {
			optrS.push(tte);
			continue;
		}
		//Right Unary Opt should go directly to result
		else if (tte.second == RightUniOpt) {
			_suffix.push_back(tte);
			continue;
		}
		//Variable and Numbers should go direclty to _suffix
		else if (tte.second == Variable || tte.second == Numeric) {
			_suffix.push_back(tte);
			TokenTableElement peek;
			if (!optrS.empty()) peek = optrS.top();
			while (!optrS.empty() && peek.second == LeftUniOpt) {	//trust me, no RightUniOpt goes to optrS
				_suffix.push_back(peek);
				optrS.pop();
				if (!optrS.empty()) peek = optrS.top();
			}
			continue;
		}
		else if (tte.second == L_parentheis) {
			optrS.push(tte);
			continue;
		}
		else if (tte.second == R_parenthesis) {
			TokenTableElement peek = optrS.top();
			while (!optrS.empty() && peek.second != L_parentheis) {
				_suffix.push_back(peek);
				optrS.pop();
				peek = optrS.top();
			}
			optrS.pop();	//pop the left parenthsis in optrS
			while (!optrS.empty() && optrS.top().second == LeftUniOpt) {
				_suffix.push_back(optrS.top());
				optrS.pop();
			}
			continue;
		}
		else if (tte.second == BinOpt) {
			if (optrS.empty()) {
				optrS.push(tte);
			}
			else {
				if (PriorityOf(tte.first) > PriorityOf(optrS.top().first)) {
					optrS.push(tte);
				}
				else {
					while (!optrS.empty() && PriorityOf(tte.first) <= PriorityOf(optrS.top().first))
					{
						_suffix.push_back(optrS.top());
						optrS.pop();
					}
					optrS.push(tte);
				}
			}
			continue;
		}
	}

	while (!optrS.empty()) {
		_suffix.push_back(optrS.top());
		optrS.pop();
	}
}

void NaiveParser::showSuffix() {
	for (int i = 0; i < _suffix.size(); ++i) {
		std::cout << _suffix[i].first << " ";
	}
	std::cout << "\n";
}


Priority NaiveParser::PriorityOf(Token opt) {
	if (opt == "*" || opt == "/")
		return 2;
	else if (opt == "+" || opt == "-")
		return 1;
	return 0;
}

#ifdef NAIVEPARSER_H
int main()
{
	//atof hates "+ 1.0"
	//I mean, when there are too many unnecessary spaces in the string
	Tokenizer toker;
	NaiveParser np;

	//toker.setContext("(sin(12))!+ ");
	toker.setContext("12*(-x) + sin((5*x) - 132)");
	//toker.setContext("2*(x+2)+x");
	toker.Tokenize();
	np.setExpression(toker.getTokenTable());
	toker.showTokenizeResult();
	np.inffToSuffix();
	np.showSuffix();
	std::cout << "Parser Result: " << np.ValidityIsGood()<<std::endl;
}

#endif

