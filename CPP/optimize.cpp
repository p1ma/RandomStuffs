#include "optimize.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <errno.h>

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
	this->system[w - 1] = new int[WIDTH + 1];
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
	this->system[w-1][z] = std::stoi(line);
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
	}else{
	  elem = "-";
	}
      }
      if( j < WIDTH ){
        elem.append(std::to_string(this->system[i][j]));
	elem.append("*x");
	elem.append(std::to_string((j+1)));
	elem.append(" ");
      }else{
	elem.append("<= ");
	elem.append(std::to_string(this->system[i][j]));
	elem.append("\n");
	}
      result.append(elem);
      elem = "";
    }
    result.append("\n");
  }
    return result;
}
