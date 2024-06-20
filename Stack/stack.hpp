//Definitions for the stack class

using namespace cop4530;

template <class T>
Stack<T>::Stack(){list = std::vector<T>(); length = 0;}

template <class T>
Stack<T>::~Stack(){}

template <class T>
Stack<T>::Stack(const Stack<T>& s){
    length = s.length;
    list = s.list;
}

template <class T>
Stack<T>::Stack(Stack<T>&& s){list = s.list; length = s.length;}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s){
    length = s.length;
    list = s.list;
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& s){std::swap(list, s.list); std::swap(length, s.length);}

template <class T>
bool Stack<T>::empty() const{return list.empty();}

template <class T>
void Stack<T>::clear(){return list.clear();}

template <class T>
void Stack<T>::push(const T& x){list.push_back(x);}

template <class T>
void Stack<T>::push(T&& x){list.push_back(x); length++;}

template <class T>
void Stack<T>::pop(){list.pop_back();length--;}

template <class T>
T& Stack<T>::top(){
    auto itr = list.end();
    itr--;
    return *itr;}

template <class T>
const T& Stack<T>::top() const{return list.cbegin();}

template <class T>
int Stack<T>::size() const{return length;}

template <class T>
void Stack<T>::print(std::ostream& os, char ofc) const {
    auto itr = list.begin();
    while(itr!= list.end()){
        os << *itr << ofc;
        itr++;
    }

    std::cout << std::endl; 
    
}

template <class T>
std::vector<T> Stack<T>::getList() const{
    return list;
}

//non-member functions
template <class T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a){
    a.print(os);
    std::cout << std::endl;
    return os;
}

template <class T>
bool operator==(const Stack<T>& lhs, const Stack<T>& rhs){
    bool same = true;
    std::vector<T> r,l;
    r = rhs.getList();
    l = lhs.getList();

    if(lhs.size() != rhs.size())
        return !same;
    else{
        for(int i = 0; i < rhs.size(); i++){
            if(l.back() != r.back()){
                same = false;
                break;
            }
            l.pop_back();
            r.pop_back();
        }

    return same;
    }
}

template <class T>
bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs){
    return !(lhs == rhs);
}

template <class T>
bool operator<=(const Stack<T>& a, const Stack<T>& b){
    bool gtr = true;

    if(a.size() > b.size())
        return !gtr;
    else if(b.size() > a.size())
        return gtr;
    else{
       auto A = a.getList().begin();
        auto B = b.getList().begin();

        while(A != a.getList().end()){
            if(&A > &B)
                gtr = false;
            A++;B++;
        }
        return gtr;
    }

}