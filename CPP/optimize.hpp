#ifndef _OPTIMIZE_
#define _OPTIMIZE_

#include <string>

#define WIDTH 4
#define HEIGHT 3
#define DELIMITER ','
class Optimize{
private :
int *max;
int **system;
int height;

public :
  Optimize(const std::string &file);
~Optimize();
std::string printMax();
std::string printSystem();

};

#endif // _OPTIMIZE_

