#ifndef _HAND_H
#define _HAND_H

#include <vector>
#include <iostream>
#include "Card.h"
#include "DrawPile.h"

class Hand: public Pile {
 public:
  Hand() { }
  void add(const Card &c) {pile.push_back(c);}
  void fillHand(DrawPile &draw);
  //maybe rewrite play
  //void play(Card c) {
  //for (int i = 0;i<(int)pile.size();i++){
  //  if(c.getValue() == pile[i].getValue()){
  //	pile.erase(pile.begin()+i);	
  //  }
  //}
  //}
  
  
  std::string toString() const;

  void readIn(std::istream & is);
  
  void display() const;
  Card getCard(int index){
    return pile[index];
  }
  void removeCard(int index){
    pile.erase(pile.begin()+index);
  }
};


#endif
