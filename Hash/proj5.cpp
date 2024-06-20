#include "hashtable.h"

  using namespace std;
  using namespace cop4530;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main(){
  char ans;
  int prefSize;

  cout << "Enter preferred hash table capacity: ";
  cin >> prefSize;

  cop4530::HashTable<string, string> ht(prefSize);

  while(ans != 'x'){
    cop4530::Menu();
    cin >> ans;
    
    switch(ans){
      case 'l':
        // cop4530::load(ht);
        break;
      case 'a':
        // cop4530::add(ht);
        break;
      case 'r':
        // cop4530::remove(ht);
        break;
      case 'c':
        // cop4530::change(ht);
        break;
      case 'f':
        // cop4530::find(ht);
        break;
      case 'd':
        // cop4530::dump2(ht);
        break;
      case 's':
        // cop4530::size2(ht);
        break;
      case 'w':
        // cop4530::write(ht);
        break;
      case 'x':
        ans = 'x';
        break;
      default:
        std:: cout <<"\n" << ans << " is not a valid input. Try again\n\n";
        break;
    }
  }
}