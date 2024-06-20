//namespace cop4530{
#include <vector>
#include <string>
    class BET{
        private:
        //nested node class
        struct BinaryNode{
            char data = '\0';
            BinaryNode *L = nullptr;
            BinaryNode *R = nullptr;

            // BinaryNode(const char & d = '\0', BinaryNode *r = nullptr, BinaryNode *l = nullptr)
            // : data{d}, R{r}, L{l} {}
            // BinaryNode( char && d, BinaryNode *r = nullptr, BinaryNode *l = nullptr)
            // : data{std::move(d)}, R{r}, L{l} {}
        };

        BinaryNode tree;
        void printInfixExpression(BinaryNode *n);
        void makeEmpty(BinaryNode* &t);
        BinaryNode* clone(BinaryNode* t);
        void printPostfixExpression(BinaryNode* n);
        int size(BinaryNode* t);
        int leaf_nodes(BinaryNode *t);
        
        


        public:
            BET();
            BET(const std::string& postfix);
            BET(const BET& b);
            ~BET();
            bool buildFromPostfix(const std::string& postfix);
            const BET& operator=(const BET& b);
            void printInfixExpression();
            void printPostfixExpression();
            int size();
            int leaf_nodes();
            bool empty();

    };

#include "bet.hpp"
//}