#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include "BuildPile.h"
#include "DrawPile.h"
#include "Player.h"
class SkipBoGame {
 protected:
  std::vector<Player> peep;
  DrawPile draw;
  DrawPile outofgame;
  std::vector<BuildPile> build;
  int curp = 0;
  int nump;
  bool rand;
  
 public:
  Player& getCurPlayer() {return peep[curp];}
  int getCurp() {return curp;}
  void incrementCurp(){
    if(curp == (int)(peep.size()-1)){
      curp = 0;
    }
    else{curp+=1;}
  }
  void setCurp(int n) {curp = n;}
  bool checkFullBuild();
  DrawPile& getDraw() {return draw;}
  int readGame(bool shuffle, std::string save_file);
  int makeGame(bool shuffle, int num_players, int stock_size, std::string deck_name);
  void display() const;
  std::string toString() const;
  void readIn(std::istream &is);
  BuildPile& getBuildPile(int index){
    return build[index];
  }
};

#endif
