
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
  delete a;
}
