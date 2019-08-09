#include <vector>
#include <iostream>
#include "Card.h"

#ifndef _PILE_H
#define _PILE_H

class Pile {
 protected:
  std::vector<Card> pile;

 public:
  Pile() { }
  
  int size() const { return pile.size(); }

  virtual void addCard(const Card& c) { pile.push_back(c); }

  int getCardValue(int index){
    return pile[index].getValue();
  }

  std::string toString() const;  // for saving state

  void readIn(std::istream & is);  // students to write this, companion to toString()

  virtual void display() const = 0;  // for live game play, must override
};


#endif
