#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string getFName();
template <typename T>
    list<T> mySort(map<T, int> table);
template <typename T>
    void printList(list<T> l);
template <typename T>
    void printTen(list<T> l);



int main(){

    map<char, int> chars;
    map<string, int> words;
    map<long int, int> nums;

    ifstream in;

    string file = getFName();

    in.open(file);
    if(in.good()){
        char c;
        while(!in.eof()){
            in.get(c);
            tolower(c);
            chars[c]++;
        }
    }
    in.close();


    in.open(file);
    if(in.good()){
        char c;
        string s;
        while(!in.eof()){
            do{
                in.get(c);
                if(isalpha(c)){
                    tolower(c);
                    s += c;
                }
            }while(isalpha(c));
        words[s]++;
        s.clear();
        }
    }
    in.close();

    in.open(file);
    if(in.good()){
        char c;
        string s;
        long int n;
        while(!in.eof()){
            do{
                if(isdigit(in.peek())){                 
                    in.get(c);
                    s += c;
                }
                else
                    in.seekg(1);
            }while(isdigit(c));
        nums[n]++;
        s.clear();
        }
    }
    in.close();

cout << "lklk\n";

    list<char> charList = mySort(chars);
    list<string> wordList = mySort(words);
    list<long> numList = mySort(nums);

    printList(charList);
    printList(wordList);
    printList(numList);

    cout << "Top Ten Lists:\n";
    cout << "Chars:\n";
    printTen(charList);
    cout << "Words:\n";
    printTen(wordList);
    cout << "Numbers:\n";
    printTen(numList);

    return 0;
}

string getFName(){
    string s;

    cout << "Input filename: ";
    cin >> s;

    return s;
}

template <typename T>
list<T> mySort(map<T, int> table){
    list<T> l1;
    auto itr1 = table.begin();
    int smallest = itr1->second;
    int count;
    T key;

    while(!table.empty()){
        itr1 = table.begin();
        while(itr1 != table.end()){
            if(itr1->second < smallest){
                smallest = itr1->second;
                key = itr1->first;
            }
            itr1++;
        }
        l1.push_back(key);
        table.erase(key);
    }

    return l1;
}

template <typename T>
void printList(list<T> l){
    auto itr = l.end();

    while(itr!=l.begin()){
        cout << *itr << endl;
        itr--;
    }
}

template <typename T>
void printTen(list<T> l){
    auto itr = l.end();

    for (int i=0; i<10; i++){
        cout << *itr << endl;
        itr--;
    }
}
