#include <vector>
#include <iostream>
#include "Pile.h"
#include <istream>
#include <string>

#ifndef _DRAWPILE_H
#define _DRAWPILE_H

class DrawPile: public Pile {
 protected:
  bool rand;
 public:
  DrawPile() {}
  virtual void display() const;
  Card draw() {
    if (size() != 0) {
      Card c = pile.back();
      pile.pop_back();
      return c;
    }
    return 0;
  } 
  void readIn(std::istream &is);
  void readInSize(std::istream &is, int size);
  void setRand(bool b){
    rand = b;
  }
  std::string getRand() const;
  void shuffle();
  void replace(DrawPile& ndraw);
};


#endif
