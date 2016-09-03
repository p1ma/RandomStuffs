#include "optimize.hpp"
#include <iostream>

using namespace std;

Optimize *pOpti;

int main(int argc, char **argv){
  cout << "\tTest optimization" << endl;
  pOpti = new Optimize(argv[1]);
  cout << pOpti->printMax() << std::endl;
  cout << pOpti->printSystem() << std::endl;
  int *result = pOpti->simplex();
  delete pOpti;
  delete result;
  return 0;
}
