#include <iostream>
#include <string>
#include "Card.h"

/*************************************
For SkipBo - Fall 2018 - EN.601.220
Instructor provided code
*************************************/

// for live game play - must not change!
void Card::display() const {
  std::cout << "[";
  if (value == 0) 
    std::cout << "SB";
  else {
    std::cout << value;
  }
  std::cout << "]";
}

// for saving game state - must not change!
std::string Card::toString() const { 
  return std::to_string(value);
}

