#include "bet.h"

//using namespace cop4530;

int main(){

BET tr;
std::string s = "a b + c -";

    tr.buildFromPostfix(s);

    tr.printInfixExpression();
    std::cout << "Size: " << tr.size() << std::endl;

    if(tr.empty()) std::cout << "The tree is empty.";

    tr.printPostfixExpression();

    std::cout << "Leaf Nodes: " << tr.leaf_nodes() << std::endl;
    
    std::string p = "e r * i -";

    tr.buildFromPostfix(p);

    BET tr2(p);

    BET tr3 = tr2;

    tr2. printInfixExpression();
    tr3.printInfixExpression();

    return 0;
}