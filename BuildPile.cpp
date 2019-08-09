#include "BuildPile.h"

bool BuildPile::build(Card c) {
  //when the pile is 0 the only playable cards are sb and 1 
  if(pile.size() == 0){
    if(c.getValue() != 0 && c.getValue() != 1)
      return false;
    else{
      pile.push_back(c);
      return true;
    }
  }

  //playing sb card always works
  if (c.getValue() == 0){
    pile.push_back(c);
    return true;
  }

  //if the top of the buildpile is an sb card then it needs to be "seen through" 
  if(pile.back().getValue() == 0){
    if((int)pile.size() + 1 == c.getValue())
      return true;
    return false;
  }
  
  //if incrememnts by 1, add it
  if (pile.back().getValue() + 1 == c.getValue()){
    //if c.getValue() is 12 , do something to get rid of cards
    pile.push_back(c);
     return true;
  }
  return false;
}
