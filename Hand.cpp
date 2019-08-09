#include <iostream>
#include "Hand.h"
#include <sstream>
/*************************************
For SkipBo - Fall 2018 - EN.601.220
Instructor provided code
*************************************/

// for live game play - must not change!
void Hand::display() const {
  int i;
  for (i = 0; i < size(); i++) {
    pile[i].display();
    std::cout << "  ";
  }
  for ( ; i < 5; i++)
    std::cout << "--  ";
}

void Hand::readIn(std::istream & is){
  int handSize;
  is >> handSize;
  for (int i =0 ;i <handSize;i++){
    int value;
    is >>value;
    Card c(value);
    add(c);
  }
}
std::string Hand::toString() const{
  std::stringstream result;
  result << size() << std::endl;
  for(int i = 0;i<size();i++){
    result << pile[i].getValue() << " ";
  }
  result << std::endl;
  return result.str();
}

void Hand::fillHand(DrawPile &draw) {
  while (size() < 5) {
  
    add(draw.draw());
    }
}

