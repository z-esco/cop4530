//prefix driver file using stack class

#include "stack.h"
#include <ctype.h>
#include <string>

using namespace cop4530;

bool isNum(std::string s);
bool isOpenParen(std::string s);
bool isOperator(std::string s);
bool higher(std::string s);
bool isCloseParen(std::string s);

bool isNum(std::string s){
    bool alNum = true;
    for(int i = 0; i < s.length(); i++){
        if(!(std::isalnum(s[i]) || s[i] == '_'))
            alNum = false;
    }

    return alNum;
}

bool isOpenParen(std::string s){
    if(s == "(")
        return true;
    else   
        return false;
}
bool isCloseParen(std::string s){
    if(s == ")")
        return true;
    else   
        return false;
}

bool isOperator(std::string s){
    switch(s[0]){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}

bool higher(std::string s){
    if(s == "*" || s == "/"){
    return true;
    }
    else
    return false;
}

int main(){
    Stack<std::string> ops, nums;

    std::string s, parse;
    std::istream& in = std::cin;
    std::ostream& os = std::cout;

    int space;

        os << "Input next infix stream (type 'exit' to quit): ";
        in >> s;
        do{ // go till end of expression

             if(isNum(s)) // push operands
                nums.push(s);

            if(isOperator(s)){
                if(ops.empty()) // push operators on empty stack
                    ops.push(s);
                else if(isOpenParen(s)) // push operators into expression  on open paren
                    ops.push(s);
                else if(isCloseParen(s)){
                    while(!isOpenParen(ops.top())){
                        nums.push(ops.top());
                        ops.pop();
                    }
                    ops.pop();
                }
                else if(higher(s)){ // push all operators of lower precedence into expression
                    bool highPrec;
                    while(!highPrec){
                        if(higher(ops.top()) || isOpenParen(ops.top())){
                            highPrec = true;
                            ops.push(s);
                        }
                        else{
                            ops.push(s);
                        }
                    }
                }
                else{
                    if(higher(ops.top())){
                        nums.push(s);
                    }
                    else
                        ops.push(s);

                }

            }
            s.clear();
            in >> s;
        }while(in.peek() != '\n');
            while(!ops.empty()){
                if(isOpenParen(ops.top()) || isCloseParen(ops.top())){
                    ops.pop();
                }
                else{
                    nums.push(ops.top());
                    ops.pop();
                }
            }
        nums.print(os);
        Stack<std::string> exp;

        for(int i = 0; i < nums.size(); i++){
            exp.push(nums.top());
            nums.pop();
        }

        int and1, and2, total;

        while(!exp.empty()){
            std::string s2 = exp.top();
            if(isNum(s2)){
                and1 = stoi(s2);
                exp.pop();
                s2 = exp.top(); 
                if(isNum(s2)){
                    and2 = stoi(s2);
                    exp.pop();
                }
            }

            s2 = exp.top();

            switch(s2[0]){
                case '+':
                    total += and1 + and2;
                case '-':
                    total += and1 - and2;
                case '*':
                    total += and1 * and2;
                case '/':
                    total += and1 / and2;
            }
        }
        
        std::cout << "total: " << total << std::endl;
    return 0;
}