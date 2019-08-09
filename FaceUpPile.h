#include <vector>
#include <iostream>
#include "Pile.h"

#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

class FaceUpPile: public Pile {
 public:
  FaceUpPile() {}
  void display() const; 
  //void addTop();
};


#endif
