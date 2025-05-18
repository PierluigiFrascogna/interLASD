
#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"


using namespace std;

/* ************************************************************************** */

void mytest() {
  
  lasd::Vector<int>* a = new lasd::Vector<int>(10);
  for (int i = 0; i < 10; i++) {
    a->operator[](i) = i;
  }
  cout << "Vector size: " << a->Size() << endl;
  cout << "Vector elements: ";
  for (ulong i = 0; i < a->Size(); i++) {
    cout << a->operator[](i) << " ";
  }
  cout << endl;
  cout << "Vector front: " << a->Front() << endl;
  cout << "Vector back: " << a->Back() << endl;
  cout << "Vector empty: " << (a->Empty() ? "true" : "false") << endl;
  cout << "Vector resize to 5" << endl;
  a->Resize(5);
  cout << "Vector size: " << a->Size() << endl;
  cout << "Vector elements: ";
  for (ulong i = 0; i < a->Size(); i++) {
    cout << a->operator[](i) << " ";
  }
  cout << endl;
  cout << "Vector front: " << a->Front() << endl;
  cout << "Vector back: " << a->Back() << endl;
  cout << "Vector empty: " << (a->Empty() ? "true" : "false") << endl;
  cout << "Vector clear" << endl;
  a->Clear();
  cout << "Vector size: " << a->Size() << endl;
  cout << "Vector empty: " << (a->Empty() ? "true" : "false") << endl;
  cout << "Vector elements: ";
  for (ulong i = 0; i < a->Size(); i++) {
    cout << a->operator[](i) << " ";
  }
  cout << endl;
  cout << "Vector front: " << (a->Empty() ? "N/A" : to_string(a->Front())) << endl;
  cout << "Vector back: " << (a->Empty() ? "N/A" : to_string(a->Back())) << endl;
  cout << "Vector empty: " << (a->Empty() ? "true" : "false") << endl;
  delete a;
}
