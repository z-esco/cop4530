#include <stack>
#include <string>
#include <iostream>


//using namespace cop4530;

bool isOperator(const char c);

bool isOperator(const char c){
    switch(c){
        case '+':
        case '-':
        case '*':
        case '\\':
            return true;
        default:
            return false;
    }
}

BET::BET(){
    tree.data = '\0';
    tree.L = nullptr;
    tree.R = nullptr;
}

BET::BET(const std::string& postfix){
    buildFromPostfix(postfix);
}

BET::BET(const BET& b){
    tree.data = b.tree.data;
    tree.L = b.tree.L;
    tree.R = b.tree.R;
}

BET::~BET(){
    BinaryNode * t = &tree;
    makeEmpty(t);
}


//public functions
bool BET::buildFromPostfix(const std::string& postfix) {
   bool valid = true;
    std::stack<BinaryNode> operands;
    for(int i = 0; i < postfix.length(); i++){
        if(postfix[i] == ' ')
            i++;
        if(!isOperator(postfix[i])){
            BinaryNode n;
            n.data = postfix[i];
            operands.push(n);
        }
        else{
            BinaryNode n1, n2;
            n2 = operands.top();
            operands.pop();    
            n1 = operands.top();
            operands.pop();

            BinaryNode t;
            t.data = postfix[i];t.L = &n1; t.R = &n2;

            operands.push(t);
        }
    }

    tree = operands.top();

    return valid;
}

void BET::printInfixExpression(){
    printInfixExpression(&tree);
    std::cout << std::endl;
}

void BET::printPostfixExpression(){
    printPostfixExpression(&tree);
    std::cout << std::endl;
}

int BET::size(){
    return size(&tree);
}

int BET::leaf_nodes(){
    return leaf_nodes(&tree);
}

bool BET::empty(){
    return tree.data == '\0';
}

//private functions 
void BET::printInfixExpression(BinaryNode *n){
    if(n != NULL){
        if(n->L != nullptr) printInfixExpression(n->L);
        
        std::cout << n->data << " ";

       if(n->R != nullptr) printInfixExpression(n->R);

    }
    else
        return;
}

void BET::makeEmpty(BinaryNode* &t){
    BinaryNode n;
    t = &n;
}
int BET::size(BinaryNode* t){
    int count = 1;
    
    
    if(empty()){
        return 0;
    }

    if(t->L != nullptr)
        count += size(t->L);
    
    if(t->R != nullptr)
        count += size(t->R);
    
    return count;

}

int BET::leaf_nodes(BinaryNode* t){
    int count;

    if(t->L == nullptr) count++;
    else count += leaf_nodes(t->L);
    if(t->R == nullptr) count++;
    else count += leaf_nodes(t->R);

    return count;
}

const BET& BET::operator=(const BET& b){
    tree.data = b.tree.data;
    tree.L = b.tree.L;
    tree.R = b.tree.R;

    return *this;
}



typename BET::BinaryNode* BET::clone(BinaryNode* t){
    BinaryNode n;
    n.data = t->data;
    n.L = clone(t->L);
    n.R = clone(t->R);
    return &n;
}

void BET::printPostfixExpression(BinaryNode* n){
    if(!empty()){
        if(n->L != nullptr){
            printPostfixExpression(n->L);
        }
        
        if(n->R != nullptr){
            printPostfixExpression(n->R);
        }

        std::cout << n->data << " ";
    }
    else
        std::cout << "The tree is empty\n";   
}