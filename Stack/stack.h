//Header file for stack class
//Zack Esco 

#include <iostream>
#include <vector>
namespace cop4530{
    template <typename T>
    class Stack{
        private:
            std::vector<T> list; //internal Stack container
            int length;

        public:

            //constructors/destructors
            Stack();
            ~Stack();
            Stack(const Stack<T>& s);
            Stack(Stack<T>&& s);

            //assignment operator overloads
            Stack<T>& operator=(const Stack<T>& s);
            Stack<T>& operator=(Stack<T> && s);

            //member functions
            bool empty() const; //returns true if stack is empty
            void clear(); //clears stack
            void push(const T& x); //inserts an element at the front
            void push(T&& x); //inserts an element at the front (move version)
            void pop(); //takes element off of the top of the stack
            T& top(); //returns a reference to the top element
            const T& top() const; //returns a const reference to the top element
            int size() const; //returns the size of the stack
            void print(std::ostream& os, char ofc = ' ') const; //print the whole stack
            std::vector<T> getList() const;
    };

    //non-member functions
    template <class T> //operator overloads output operator
    std::ostream& operator<<(std::ostream& os, const Stack<T>& a); 

    template <class T> //operator overloads equality operator
    bool operator==(const Stack<T>& lhs, const Stack<T>& rhs);

    template <class T> //operator overloads anti-equality ooperator
    bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs);

    template <class T> //returns true if every element in stack a is smaller than b
    bool operator <=(const Stack<T>& a, const Stack<T>& b); //false if a.size > b.size
}

#include "stack.hpp"