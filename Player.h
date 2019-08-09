#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "PlayPile.h"
#include "Hand.h"
#include <string>

class Player{

 protected:
  std::vector<PlayPile> discard;
  PlayPile stock;
  Hand hand;
  std::string name;
  
 public:
  Player() { }
  Player(int num);
  void display() const;
  std::string toString() const;
  Card takeFromStock();
  Card viewFromStock();
  Card takeFromHand(int index);
  Card viewFromHand(int index);
  int getStockSize() { return stock.size(); }
  void readIn(std::istream &is);
  void addStock(Card c){
    stock.addCard(c);
  }
  bool addDiscard(Card c, int index){
    if (index < 0 || index > 4) return false;
    discard[index].addCard(c);
    return true;
  }
  int getHandSize(){
    return hand.size();
  }
  void fillPlayerHand(DrawPile &draw){
    hand.fillHand(draw);
  }
};
#endif
