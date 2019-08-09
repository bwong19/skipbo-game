#include "PlayPile.h"

Card PlayPile::play() {
  Card c = pile[size()-1];
  pile.pop_back();
  return c;
}
