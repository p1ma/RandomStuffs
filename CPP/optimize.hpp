#ifndef _OPTIMIZE_
#define _OPTIMIZE_

#include <string>

#define WIDTH 2
#define HEIGHT 3
#define DELIMITER ','
class Optimize{
private :
int *max;
int **system;
int **standard;
int height;
int selectColumn();
int selectLine(int const &pivot);
void pivotProduces(int const &pivotLine,int const &pivotColumn);
bool const finish();
std::string result();

public :
  Optimize(const std::string &file);
~Optimize();
std::string printMax();
std::string printSystem();
std::string printStandardForm();
int *simplex(); // execute simplex method

};

#endif // _OPTIMIZE_

