#include <vector>
#include <iostream>
#include "FaceUpPile.h"

#ifndef _BUILDPILE_H
#define _BUILDPILE_H

class BuildPile: public FaceUpPile {
 public:
  BuildPile() {}
  bool build(Card c);
  void clearBuildPile(){
    pile.clear();
  }
};


#endif
