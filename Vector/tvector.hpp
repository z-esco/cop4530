// #include "tvector.h"

//TVector class defintions

//default constructor
template <class T>
    TVector<T>::TVector(){
        capacity = SPARECAPACITY;
        size = 0;
        array = new T[SPARECAPACITY];
    }
//parameterized constructor
template <class T>
    TVector<T>::TVector(T val, int num){
        capacity = num;
        size = num;
        array = new T[capacity];
        for(int i = 0; i < capacity; i++)
            array[i] = val;
        }
//destructor
template <class T>
    TVector<T>::~TVector(){
        if(array != 0)
            delete[] array;
    }
//copy constructor and assignment operator overload
template <class T>
    TVector<T>::TVector(const TVector<T>& v){
        capacity = v.capacity;
        size = v.size;
        
        array = new T[capacity];
        for(int i = 0; i < capacity; i++)
            array[i] = v.array[i]; 
    }
template <class T>
    TVector<T>& TVector<T>::operator= (const TVector<T>& v){
        size = v.size;
        capacity = v.capacity;

        if(this != &v){
            delete[] array;
            array = new T[capacity];
            for(int i = 0; i < capacity; i++)
                array[i] = v.array[i];
        }
        
        return *this;
    }
    //move constrcutor and move assignment overload
template <class T>
    TVector<T>::TVector(TVector<T> &&v){
        capacity = v.capacity;
        size = v.size;
        array = v.array;

        v.size = v.capacity = 0;
        v.array = nullptr;
    }
template <class T>
    TVector<T>& TVector<T>::operator=(TVector<T> &&v){
        std::swap(size, v.size);
        std::swap(capacity, v.capacity);
        std::swap(array, v.array);

        return *this;
    }

    //empty check, clear function, get size function
template <class T>
    bool TVector<T>::IsEmpty() const{
       bool empty;
       if(size == 0){
            empty = true;
       } 
       return empty;
    }
template <class T>
    void TVector<T>::Clear(){
        delete[] array;
        array = new T[capacity];
    }
template <class T>
    int TVector<T>::GetSize() const{
        return size;
    }

    //Insert at end and remove last element functions
template <class T>
    void  TVector<T>::InsertBack(const T& d){
        if(size <= capacity){
            array[size] = d;
            size++;
        }
        else{
            this->SetCapacity(capacity*2);
            TVector temp;
            temp.SetCapacity(capacity);
        }

}
template <class T>
    void TVector<T>::RemoveBack(){
        size--;

        this->SetCapacity(capacity);
    } 

    //returns first element and last element function
template <class T>
    T& TVector<T>::GetFirst() const{return array[0];}

template <class T>
    T& TVector<T>::GetLast() const{return array[size-1];}

    //returns iterators (front/back)
template <class T>
    TVectorIterator<T> TVector<T>::GetIterator() const{
        TVectorIterator<T> itr;
        itr.index = 0;
        itr.ptr = array;
        itr.vsize = size;

        return itr;
    }
template <class T>
    TVectorIterator<T> TVector<T>::GetIteratorEnd() const{
        TVectorIterator<T> itr;

        while(itr.HasNext())
            itr.Next();
        return itr;
    }

template <class T>
    void TVector<T>::SetCapacity(unsigned int c){
        capacity = c;
        T* temp = new T[capacity];
        for(int i = 0; i < size; i++){
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
    }

template <class T>
    TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d){
        int itrInd;
        itrInd = pos.index;

        T temp1 = d;
        T temp2 = array[pos.index];

        if(size == capacity)
            this->SetCapacity(capacity*2);

        while(pos.HasNext()){
            array[pos.index] = temp1;
            temp1 = temp2;
            temp2 = array[pos.index];
            pos.Next();
        }
        
        this->InsertBack(temp2);
        
        while(pos.index != itrInd)
            pos.Previous();

        return pos;
    }

template <class T>
    TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos){
        int itrInd = pos.index;
        
        while(pos.HasNext()){
            array[pos.index] = array[pos.index];
            pos.Next();
        }

        this->RemoveBack();

        while (pos.index != itrInd)
            pos.Previous();

        return pos;
    }

template <class T>
    TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2){
        int remSize = pos2.index - pos1.index;
        int itrInd = pos1.index;

        while(pos2.HasNext()){
            array[pos1.index] = array[pos2.index];
            pos1.Next();
            pos2.Next();
        }

        for(int i = 0; i < remSize; i++)
            this->RemoveBack();

        while(pos1.index != itrInd)
            pos1.Previous();

        return pos1;

    }

template <class T>
    void TVector<T>::Print(std::ostream& os, char delim) const{
        for(int i = 0; i < size; i++)
            std:: cout << array[i] << delim;
    }

//iterator class defintions
    //default constructor
template <class T>
    TVectorIterator<T>::TVectorIterator(){
        index = 0;
        ptr = NULL;
        vsize = 0;
    }

//confirms next item available
template <class T>
    bool TVectorIterator<T>:: HasNext() const{
        bool has = true;
        if(index == vsize-1)
            has = false;
        
        return has;
    }

//confirms previous item available
template <class T>
    bool TVectorIterator<T>::HasPrevious() const{
        bool has = true;
        if(index <= 0)
            has = false;
        
        return has;
    }

//moves iterator forward
template <class T>
    TVectorIterator<T> TVectorIterator<T>::Next(){
        if(this->HasNext()){
            index++;
        }
        
        return *this;
    }

//moves iterator back
template <class T>
    TVectorIterator<T> TVectorIterator<T>::Previous(){
        if(this->HasPrevious()){
            index--;
        }
        
        return *this;
    } 

template <class T>
    T& TVectorIterator<T>::GetData() const{
        return ptr[index];
    }

template <class T>
    TVector<T> operator+(const TVector<T> & t1, const TVector<T>&t2){
        int size = t1.GetSize() + t2.GetSize();

        TVector<T> temp(t1.GetFirst(), size);
        temp.Clear();


        TVectorIterator<T> itr1 = t1.GetIterator();
        TVectorIterator<T> itr2 = t2.GetIterator();

        while(itr1.HasNext() == true){
            temp.InsertBack(itr1.GetData());
            itr1.Next();
        }

        while(itr2.HasNext() == true){
            temp.InsertBack(itr2.GetData());
            itr2.Next();
        }
        return temp;
    }