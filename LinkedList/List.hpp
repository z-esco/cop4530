//#include "List.h"

using namespace cop4530;

template <class T>
List<T>::const_iterator::const_iterator(){
    current = nullptr;
}

template <class T>
const T& List<T>::const_iterator::operator*() const{
    return retrieve();
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++(){
    current = current -> next;
    return *this;
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
    const_iterator old = *this;
    ++(old);
    return old;
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--(){
    current = current -> prev;
    return *this;
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    const_iterator old = *this;
    --(old);
    return old;
}

template <class T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator &rhs) const{
    return current == rhs.current;
}

template <class T>
bool List<T>::const_iterator::operator !=(const List<T>::const_iterator &rhs) const{
    return !(*this == rhs);
}

template <class T>
T& List<T>::const_iterator::retrieve() const{
    return current->data;
}

template <class T>
List<T>::const_iterator::const_iterator(Node *p): current{p}{};

///////////////////////// Iterator Defintions ////////////////////
template <class T>
List<T>::iterator::iterator(){
    const_iterator::current = nullptr;
}

template <class T>
T& List<T>::iterator::operator*(){
    return const_iterator::retrieve();
}

template <class T>
const T& List<T>::iterator::operator*() const{
    return const_iterator::operator*();
}

template <class T>
typename List<T>::iterator&  List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator++(int){
    iterator old = *this;
    ++(*this);
    return old;
}

template <class T>
typename List<T>::iterator&  List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator--(int){
    iterator old = *this;
    --(*this);
    return old;
}

template <class T>
List<T>::iterator::iterator(Node* p){
    this->current = p;
}

///////////////////////// List Definitions /////////////////////
template <class T>
List<T>::List(){init();}

//copy constructor
template <class T>
List<T>::List(const List &rhs){
    init();
    for(auto & x: rhs)
        push_back(x);
}

//move constructor
template <class T>
List<T>::List(List<T>&& rhs){
    theSize = rhs.size();
    head = rhs.head;
    tail = rhs.tail;

    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

//constructs elements with value val
template <class T>
List<T>::List(int num, const T& val){
    theSize = 1;
    head = new Node;
    tail = new Node;
    head -> next = tail;
    tail -> prev = head;
    for(int i = 0; i< num; i++)
        push_back(val);
}

//construct elements with [start,end]
template <class T>
List<T>::List(const_iterator start, const_iterator end){
   init();
    while(start.current != end.current){
        push_back(start.const_iterator::retrieve());
        start++;
    }
}

//constructs a list with all elements in iList
template <class T>
List<T>::List(std::initializer_list<T> iList){
    init();
    int size = iList.size();

    auto itr = iList.begin();
    for(int i = 0; i < size; i++){
        push_back(*itr);
        itr++;
    }
}

//destructor
template <class T>
List<T>::~List(){
    clear();
    delete head;
    delete tail;
}

//assignment operators
//copy=
template <class T>
const List<T>& List<T>::operator=(const List<T> &rhs){
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
}
//move=
template <class T>
List<T>& List<T>::operator=(List<T> && rhs){
    std::swap(theSize, rhs.size());
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

//sets list elements to initializer list
template <class T>
List<T>& List<T>::operator=(std::initializer_list<T> iList){    
    for(auto x: iList){
        push_back(x);
    }

    return *this;
}


//init function
template <class T>
void List<T>::init(){
    theSize = 0;
    head = new Node;
    tail = new Node;
    head -> next = tail;
    tail -> prev = head;
}

// member funcitons

//returns size
template <class T>
int List<T>::size() const{
    return theSize;
}

//returns is empty bool
template <class T>
bool List<T>::empty() const{
    if(theSize == 0){
        return true;
    }
    else
        return false;
}

// deletes all elements
template <class T>
void List<T>::clear(){

    while(!empty())
        pop_front()
;}

//puts elements in reverse order
template <class T>
void List<T>::reverse(){
    auto itr = begin();
    for(auto x: *this){
        push_front(x);
        erase(itr);
        itr++;
    }
}

//references first element
template <class T>
T& List<T>::front(){
    auto itr = begin();

    return *itr;
}

template <class T>
const T& List<T>::front() const{
    auto itr = begin();

    return *itr;
}

//references last element
template <class T>
T& List<T>::back(){return *--end();}

template <class T>
const T& List<T>::back() const{return *--end();}

//insert to the beginning
template <class T>
void List<T>::push_front(const T& val){
    insert(begin(), val);
}

//insert at end
template <class T>
void List<T>::push_back(const T& val){

        insert(end(), val);
}

//move versions of inserts
template <class T>
void List<T>::push_front(T&& val){
    insert(begin(), std::move(val));
}

template <class T>
void List<T>::push_back(T&& val){
    insert(end(), std::move(val));
}

//deletes at front
template <class T>
void List<T>::pop_front(){
    erase(begin());
}

//deletes at back
template <class T>
void List<T>::pop_back(){
    erase(--end());
}

//removes all elements = val
template <class T>
void List<T>::remove(const T& val){
    auto itr = begin();
    for(auto x: *this){
        if(x == val){
            erase(itr);
        }
    itr++;
    }
}

// removes all elements that return true for pred
template <class T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){
    auto itr = begin();

    for(auto x: *this){
        if(pred(x))
            remove(x);
       itr++;
    }
}

//prints
template <class T>
void List<T>::print(std::ostream& os, char ofc) const{
    for(auto x: *this){
        std::cout << x << ofc;
    }
    std::cout << std::endl;
}

// returns iterator for front
template <class T>
typename List<T>::iterator List<T>::begin(){
    List::iterator itr;
    itr.current = head->next;
    
    return itr;
}

//returns const_iterator for front
template <class T>
typename List<T>::const_iterator List<T>::begin() const{
    List::const_iterator itr;
    itr.current = head->next;
    
    return itr;
}

//returns iterator for back
template <class T>
typename List<T>::iterator List<T>::end(){
    List::iterator itr = tail;

    return itr;
}

//returns const_iterator for end
template <class T>
typename List<T>::const_iterator List<T>::end() const{
    List::const_iterator itr;
    itr.current = tail->prev;
    
    return --itr;
}

//inserts val ahead of itr
template <class T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, const T& val){
    Node *p = itr.current;
    ++theSize;
    return List<T>::iterator(p->prev = p-> prev -> next = new Node(val, p->prev, p));
}

//move version of insert
template <class T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, T&& val){
    Node *p = itr.current;
    ++theSize;
    return List<T>::iterator(p->prev = p-> prev -> next = new Node(std::move(val), p->prev, p));
}

//erase one element
template <class T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr){
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;

    delete p;
    --theSize;

    return retVal;
}

//erase [start,end]
template <class T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end){
    for(iterator itr = start; itr!= end;)
        itr = erase(itr);

    return end;
}

////////////////////////////Misc Functions/////////////////////////////////
//comparsion overload
template <typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs){
    bool equal = true;
    auto itr1 = lhs.begin();
    auto itr2 = rhs.begin();

    if(lhs.size() == rhs.size()){
        while(itr1 != rhs.end()){

            if(*itr1 != *itr2)
                equal = false;
            
            itr1++;
            itr2++;
        }
    }
    else
        equal = false;

    return equal;
}

template <class T>
bool operator!=(const List<T>& lhs, const List<T>& rhs){
    auto itr1 = lhs.begin();
    auto itr2 = rhs.begin();

    if(lhs.size() == rhs.size()){
        while(itr1 != rhs.end()){
            if(*itr1 != itr2)
                return true;
        }
    }

    else
        return true;

    return false;
}

//ostream overload
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l){
    l.print(os);
    return os;
}