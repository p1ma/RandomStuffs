#include "optimize.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <errno.h>
#include <limits>
#include <cstdlib>

// constructor
Optimize::Optimize(const std::string &file){
  std::ifstream pFile;
  pFile.open(file.c_str(), std::ifstream::in);

  if(pFile.is_open()){
    int index = 0;
    int j = 0, z = 0, w = 0;
    this->max = new int[WIDTH];
    this->system = new int*[HEIGHT];
    for(std::string line ; getline(pFile,line); index++){
      size_t pos = 0;
      std::string val = "";
      if(index != 0){
	this->system[w - 1] = new int[WIDTH + 1 + HEIGHT];
      }
      while((pos = line.find(DELIMITER)) != std::string::npos){
	val = line.substr(0,pos);
	if(index == 0){
	  this->max[j] = std::stoi(val);
	  j++;
	}else{
	  this->system[w - 1][z] = std::stoi(val);
	  z++;
	}
	line.erase(0, (pos + 1));
      }
      if(index != 0){
	this->system[w-1][HEIGHT + z] = std::stoi(line);
      }
      w++;
      z = 0;
      index++;
    }
  }else{
    std::cerr << "FILE DOES NOT EXIST" << std::endl;
  }
}

// destructor
Optimize::~Optimize(){
  delete this->max;
  for(int i = 0 ; i < HEIGHT ; i++){
    delete[] this->system[i];
  }
  delete[] this->system;
}

// print max array
std::string Optimize::printMax(){
  std::string result = "Maximize( ", elem = "";
  for(int i = 0 ; i < WIDTH ; i++){
    if(this->max[i] > 0 && i != 0){
      elem.append("+");
    }
    elem.append(std::to_string(this->max[i]));
    result.append(elem + "*x");
    result.append(std::to_string((i+1)));
    elem = "";
  }
  result.append(" )");
  return result;
}

// print system
std::string Optimize::printSystem(){
  std::string elem = "";
  std::string result = "";
  for(int i = 0 ; i < HEIGHT ; i++){
    for(int j = 0 ; j < (WIDTH + 1) ; j++){
      if(j != 0 && j != WIDTH){
	if(this->system[i][j] > 0){
	  elem = "+";
	}
      }
      if( j < WIDTH ){
        elem.append(std::to_string(this->system[i][j]));
	elem.append("*x");
	elem.append(std::to_string((j+1)));
	elem.append(" ");
      }else{
	elem.append("<= ");
	elem.append(std::to_string(this->system[i][j + HEIGHT]));
	elem.append("\n");
	}
      result.append(elem);
      elem = "";
    }
    result.append("\n");
  }
    return result;
}

// execute simplex method
int *Optimize::simplex(){
  int *result = new int[WIDTH];
  result = {0};

  // canonical form -> standard form : add slacks variables
  for(int i = 0 ; i < HEIGHT ; i++){
    this->system[i][WIDTH + i] = 1;
  }

  // standard = max + system
  this->standard = new int*[HEIGHT + 1];
  for(int w = 0 ; w < HEIGHT + 1 ; w++){
    this->standard[w] = new int[WIDTH + HEIGHT + 1];
    this->standard[w] = {0};
    if(w != HEIGHT){
      this->standard[w] = this->system[w];
    }else{
      this->standard[w] = this->max;
    }
  }

  int pivotColumn = 0;
  int pivotLine = 0;

  while(!Optimize::finish()){
  // choose the greater value from max array
  pivotColumn = Optimize::selectColumn();
  std::cout << "Selected Column : " << pivotColumn << ", coefficient = " << this->standard[HEIGHT][pivotColumn] << std::endl;

  // choose the minimum value
  pivotLine = Optimize::selectLine(pivotColumn);
  std::cout << "Selected Line : " << pivotLine << ", coefficient = " << this->standard[pivotLine][WIDTH + HEIGHT] << std::endl;

  std::cout << "Select pivot ( " << pivotLine << " , " << pivotColumn << " ) value = " << this->standard[pivotLine][pivotColumn] << std::endl;

  Optimize::pivotProduces(pivotLine,pivotColumn); // execute pivot produces on this->system
  }
  std::cout << Optimize::printStandardForm() << std::endl;
  std::cout << Optimize::result();

  return result;
}

int Optimize::selectColumn(){
  int max = 0;
  int index = 0;
  for(int i = 0; i < WIDTH ; i++){
    if(this->standard[HEIGHT][i] > max){
      max = this->standard[HEIGHT][i];
      index = i;
    }
  }
  return index;
}

int Optimize::selectLine(int const &pivot){
  int min = std::numeric_limits<int>::max();
  int index = 0;
  int factor = 0;
  for(int i = 0 ; i < HEIGHT ; i++){
    if(this->standard[i][pivot] != 0){
      factor = (this->standard[i][WIDTH + HEIGHT] / this->standard[i][pivot]);
    }else{
      factor = std::numeric_limits<int>::max();
    }
    if(factor < min){
      min = factor;
      index = i;
    }
  }
  return index;
}

// execute pivot produces
void Optimize::pivotProduces(int const &pivotLine,int const &pivotColumn){
  // Eij' = Eij - [(Aij / pivotValue) * this->system[pivotLine][j])
  int Aij = 0;
  int pivotValue = this->standard[pivotLine][pivotColumn];
  for(int line = 0 ; line < HEIGHT + 1 ; line ++){
    Aij = this->standard[line][pivotColumn] ;
    for(int column = 0 ; column < (WIDTH + HEIGHT + 1) ; column ++){
      if(line != pivotLine){
	if(pivotValue != 0){
	  this->standard[line][column] = this->standard[line][column] - ((Aij / pivotValue) * this->standard[pivotLine][column]);
	}
      }
    }
  }
  return;
}

std::string Optimize::printStandardForm(){
  std::string result = "", elem = "";
  int e = 1;
for(int i = 0 ; i < HEIGHT + 1; i++){
    for(int j = 0 ; j < (WIDTH + HEIGHT + 2) ; j++){
      if(j < WIDTH + HEIGHT){
	if(j != 0 && j != WIDTH + HEIGHT){
	if(this->standard[i][j] >= 0){
	  elem = "+";
	}
      }
      if( j < WIDTH ){
        elem.append(std::to_string(this->standard[i][j]));
	elem.append("*x");
	elem.append(std::to_string((j+1)));
	elem.append(" ");
      }
      if(j >= WIDTH && j < WIDTH + HEIGHT){
	elem.append(std::to_string(this->standard[i][j]));
	elem.append("*e");
	elem.append(std::to_string(e));
	elem.append(" ");
	e++;
      }
      result.append(elem);
      elem = "";
      }
    }
        result.append("<= ");
	result.append(std::to_string(this->standard[i][WIDTH + HEIGHT]));
	result.append("\n");
	e = 1;
 }
 return result;
}

// return true if the max function has all positives members
bool const Optimize::finish(){
  bool b = true;
  for(int i = 0 ; i < WIDTH + HEIGHT ; i++){
    if(this->standard[HEIGHT][i] > 0){
      b = false;
      break;
    }
  }
  return b;
}

std::string Optimize::result(){
  std::string res = "";
  res.append("Maximum = " + std::to_string(abs(this->standard[HEIGHT][WIDTH + HEIGHT]))); 
  res.append("\n");
  for(int i = 0 ; i < HEIGHT ; i++){
    res.append("\t-Number of x" + std::to_string(i + 1));
    res.append(" = " + std::to_string(this->standard[i][WIDTH + HEIGHT]));
    res.append("\n");
  }
  return res;
}
