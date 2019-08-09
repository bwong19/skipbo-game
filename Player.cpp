#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"

Player::Player(int num){
  std::stringstream ss;
  ss << "Player" << num;
  name = ss.str();

  // creates discard piles
  for (int i = 0; i < 4; ++i) {
    PlayPile d;
    discard.push_back(d);
  }
}

// for live game play - must not change!
void Player::display() const {
  std::cout << "Current ";
  std::cout << name << ":  Stock{0}: " ;
  stock.display();
  std::cout << std::endl;
  std::cout << "   Discards{1-4}: ";
  for (int i = 0; i < 4; ++i) {
    discard[i].display();
    std::cout << "  ";
  }
  std::cout << std::endl;
  std::cout << "   Hand{5-9}: ";
  hand.display();
  std::cout << std::endl;
}

/* saving state format - must not change!
PlayerName
Stock size
01 02 03  ...
...
Hand size
01 02 03 04 05
Discard1 size
01 02 03 04 ...
...
Discard2 size
...
Discard3 size
...
Discard4 size
...
*/
std::string Player::toString() const {
  std::stringstream result;
  result << name << "\n";
  result << "Stock " << stock.toString();
  result << "Hand " << hand.toString();
  for (int i = 0; i < 4; ++i) {
    result << "Discard" << i << " " << discard[i].toString();
  }
  return result.str();
}

void Player::readIn(std::istream &is){
  std::string pname,pilename;
  is >> pname;
  name = pname;
  
  is >> pilename;
  stock.readIn(is);
  is >> pilename;
  hand.readIn(is);
  for(int i =0;i<4;i++){
    is >> pilename;
    PlayPile d;
    d.readIn(is);
    discard.push_back(d);
  }

}

Card Player::takeFromStock(){
  Card c = stock.takeTop();
  return c;
}

Card Player::viewFromStock() {
  return stock.viewTop();
}

Card Player::takeFromHand(int index){
  if (index >= hand.size()) {
    Card c = Card(-1);
    return c;
  }
  Card c = hand.getCard(index);
  hand.removeCard(index);
  return c;
}

Card Player::viewFromHand(int index) {
  return hand.getCard(index);
}
