#include <vector>
#include <iostream>
#include "FaceUpPile.h"

#ifndef _PLAYPILE_H
#define _PLAYPILE_H

class PlayPile: public FaceUpPile {
 public:
  PlayPile() {}
  Card play();
  Card takeTop(){ 
    if(size() != 0){
    	Card c = pile.back();
    	pile.pop_back();
    	return c;
    }
    std::cout << "illegal command, try again " << std::endl; //make sure dont say twice
    Card c(-1);
    return c;
  }
  Card viewTop() {
    if (size() == 0) {
      Card c(-1);
      return c;
    }
    return pile.back();
  }
};



#endif
