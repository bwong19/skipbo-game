#include <iostream>
#include "DrawPile.h"
#include <cstdlib>


// for live game play - must not change!
void DrawPile::display() const {
  std::cout << "[XX]/" << size();
}

void DrawPile::shuffle(){
  for (int i = 0; i < (int) pile.size(); ++i) {
    int random = std::rand() % pile.size();
    Card temp = pile[i];
    pile[i] = pile[random];
    pile[random] = temp;
  }
}

void DrawPile::readIn(std::istream &is){
  int n; // card number
  while (is >> n) {
    Card c(n);
    pile.push_back(c);
  }
}

void DrawPile::readInSize(std::istream &is, int size){
  int n;
  for(int i = 0;i < size;i++){
    is >> n;
    Card c(n);
    pile.push_back(c);
  }
}
// only works if pile is empty
void DrawPile::replace(DrawPile& ndraw) {
  if (size() != 0) return;

  while (ndraw.size() != 0)
    addCard(ndraw.draw());
}

std::string DrawPile::getRand() const{
  if (rand) return "true";
  return "false";
}
