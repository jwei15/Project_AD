
#include "Executive.h"

#include <iostream>

#define PI 3.1415926535897932384626

int main()
{
	Tokenizer toker;
	NaiveParser np;

	std::cout << "\n\n======= Starting of demonstration of EasyTokenizer =======\n";
	//toker.setContext("sin(5*x+1)");
	toker.setContext("(x");
	toker.Tokenize();
	np.setExpression(toker.getTokenTable());
	toker.showTokenizeResult();

	std::cout << "\n\n======= Starting of demonstration of NaiveParser =======\n";
	np.inffToSuffix();
	np.showSuffix();
	std::cout << "Parser Result: " << np.ValidityIsGood() << std::endl;
	

	std::cout << "\n\n======= Starting of demonstration of CalculationTree =======\n";
	TokenTable tt = np.get_suffix();
	CalculationTree* tree = new CalculationTree(tt);
	tree->SuffixTraverse(tree->root);
	tree->setVariable_value("x", PI/5);
	std::cout << "\nExpression Result:\n";
	std::cout << tree->eval(tree->root) << " "<< tree->diff(tree->root)<< std::endl;
	return 0;
}

