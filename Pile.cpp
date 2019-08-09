#include <vector>
#include "Pile.h"

// for saving game state - must not change!
std::string Pile::toString() const {
  std::string result;
  result.append(std::to_string(size()));
  result.append("\n");
  // add all the pile elements to the string, at most 20 per line
  for (int i=0; i < size(); ++i) {
    if (i % 20 == 0 && i != 0)
      result.append("\n");
    else if (i != 0)
      result.append(" ");
    result.append(pile[i].toString());
  }
  result.append("\n");
  return result;
}

#include <iostream>
void Pile::readIn(std::istream & is){
  int size;
  is >> size;
  
  for (int i = 0; i < size ; ++i) {
    int value;
    is >> value;
    Card c(value);
    addCard(c);
  }
}
