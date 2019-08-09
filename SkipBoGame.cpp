#include <iostream>
#include <fstream>
#include <sstream>
#include "SkipBoGame.h"
#include <string>

/* for live game play - must not change format!

drawPile  build_a  build_b  build_c  build_d
playerName  stock_0  
discards: discard_1 discard_2 discard_3 discard_4
hand: card_5 card_6 card_7 card_8 card_9
 */
void SkipBoGame::display() const {
  std::cout << "Draw: ";
  draw.display();
  std::cout << "  Build Piles: ";
  for (int j = 0; j < 4; j++) {
    build[j].display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp].display();
}

/* for saving state - must not change format!

shuffle numplayers currplayer
PlayerCurp [display]
PlayerCurp+1 [display]
[etc for all players]
Draw [display]
Build_a [display]
Build_b [display]
Build_c [display]
Build_d [display]
*/
std::string SkipBoGame::toString() const {
  std::stringstream result;
  int idx;
  result << draw.getRand() << " " << nump << " " << curp << "\n";
  for (int i = 0; i < nump; ++i) {
    idx = (curp+i) % nump;
    result << peep[idx].toString();
  }
  result << "Draw " << draw.toString(); 
  for (int j = 0; j < 4; j++) {
    result << "Build_" << char('a'+j) << " ";
    result << build[j].toString();  
  }
  return result.str();
}

bool SkipBoGame::checkFullBuild(){
    for (int i = 0; i < 4;i++){
      if(build[i].size() == 12){
        for (int k = 0 ; k < 12;k++){
          Card c = Card(build[i].getCardValue(k));
          outofgame.addCard(c);
        }
	char buildPile;
        build[i].clearBuildPile();
	switch(i){
	case '0':{ buildPile = 'a'; break;}
	case '1':{ buildPile = 'b'; break;}
	case '2':{ buildPile = 'c'; break;}
	case '3':{ buildPile = 'd'; break;}
	}
	  
	std::cout << "build pile " << buildPile << " full, set aside" <<std::endl <<std::endl;;
	return 1;
      }
    }
    return 0;
}

void SkipBoGame::readIn(std::istream &is) {

  std::string shuffle;
  int num_players;
  int cur_player;
  
  is >> shuffle;
  
  is >> num_players;
  is >> cur_player;
  nump = num_players;
  curp = cur_player;
  
  for(int i = 0; i < num_players; i++){
    Player temp;
    temp.readIn(is);
    peep.push_back(temp);
  }

  std::string pilename;
  int size;
  is >> pilename;
  is >> size;
  
  draw.readInSize(is,size);
  
  for(int i = 0;i < 4;i++){
    is >> pilename;
    BuildPile b;
    b.readIn(is);
    build.push_back(b);
  }

}

int SkipBoGame::readGame(bool shuffle, std::string save_file) {
  rand = shuffle;
  std::ifstream is(save_file);
  if (is.fail()) {
    std::cout << "invalid program usage: can't open input game file" << std::endl;
    return 1;
  }
  readIn(is);
  
  //randomizes first player and shuffles deck
  if (rand) {
    curp = std::rand() % nump;
    draw.shuffle();
  }

  std::cout << std::endl;
  
  return 0;
}

int SkipBoGame::makeGame(bool shuffle, int num_players, int stock_size, std::string deck_name) {
  rand = shuffle;
  nump = num_players;
  
  //make the players
  for (int k = 0; k < nump; k++){
    Player p(k);
    peep.push_back(p);
  }
  
  //create buildpiles
  for (int i = 0; i < 4; ++i) {
    BuildPile b;
    build.push_back(b);
  }
  
  //create a drawpile
  std::ifstream is(deck_name);
  if (is.fail()) {
    std::cout << "invalid program usage: can't open deck file" << std::endl;
    return 1;
  }
  draw.readIn(is);
  
  //shuffles the deck and randomizes first player
  if (rand) {
    curp = std::rand() % nump;
    draw.shuffle();
  }
  
  //make stock piles
  if (nump == 6) {
    if (stock_size > 20 || stock_size < 1) {
      std::cout << "num players is 6" << std::endl;
      std::cout << "invalid program usage: bad stock size" << std::endl;
      return 1;
    }
  }
  else if (stock_size > 30 || stock_size < 1) {
    std::cout << "num players is " << nump << std::endl;
    std::cout << "invalid program usage: bad stock size" << std::endl;
    return 1;
  }
  else {
    for(int k = 0; k < stock_size; k++){
      for(int j = curp; j < curp+nump; j++){
	Card add = draw.draw();
	peep[j % nump].addStock(add);
      }
    }
  }
  return 0;
}

bool validMoveFrom(std::string s) {
  if (s.length() > 1) return false;
  if (isdigit(s[0])) return true;
  return false;
}
bool validMoveTo(std::string s) {
  if (s.length() > 1) return false;
  if (isdigit(s[0]) || (s[0] >= 'a' && s[0] <= 'd')) return true;
  return false;
}





using std::cout;
using std::endl;
using std::string;
using std::cin;

int main(int argc, char* argv[]) {
  SkipBoGame game;
  int number_players, stock_size;
  // makes new game
  if (argc == 5) {
    string shuf = argv[1];
    bool shuffle;
    if (!shuf.compare("true") || !shuf.compare("1")) shuffle = 1;
    else if (!shuf.compare ("false") || !shuf.compare("0")) shuffle = 0;
    else {
      cout << "invalid program usage: invalid first argument" << endl;
      return 1;
    }
    
    try {
      number_players = std::stoi(argv[2]);
    }
    catch (const std::invalid_argument& e) {
      cout << "invalid program usage: invalid second argument" << endl;
      return 1;
    }
    
    try {
      stock_size = std::stoi(argv[3]);
    }
    catch (const std::invalid_argument& e) {
      cout << "invalid program usage: invalid third argument" << endl;
      return 1;
    }
    
    if (number_players < 2 || number_players > 6) {
      cout << "invalid program usage: num players must be 2-6" << endl;
      return 1;
    }
    
    // if makeGame returns an error, return it in the main
    if (game.makeGame(shuffle, number_players, stock_size, argv[4]))
      return 1;
    cout << "num players is " << number_players << endl;
    cout << "stock size is " << stock_size << endl;
    cout << endl;
  }
  
  // opens saved game
  else if (argc == 3) {
    string shuf = argv[1];
    bool shuffle;
    
    if (!shuf.compare("true") || !shuf.compare("1")) shuffle = 1;
    else if (!shuf.compare ("false") || !shuf.compare("0")) shuffle = 0;
    else {
      cout << "invalid program usage: invalid first argument" << endl;
      return 1;
    }
    
    // if readGame returns an error, return it in the main
    if (game.readGame(shuffle, argv[2]))
      return 1;
  }  
  else {
    cout << "invalid program usage: invalid number of arguments" << endl;
    return 1;
  }
  
  
  // STARTS GAME
  char input;
  int winner = 0; // if winner = 1, player 0 wins, if winner = 2, player 1 wins, etc.
  do {
    if (winner)
      break;
    cout << " >> Player" << game.getCurp() << " turn next" << endl << "(p)lay, (s)ave, or (q)uit ? ";

    //input checking
    string check_inp;
    cin >> check_inp;
    if(check_inp.length() != 1) {
      cout << "illegal command, try again" << endl;
      continue;
    }
    input = check_inp[0];
    
    
    if(input == 'q'){
      cout << "thanks for playing" << endl;
      break;
    }
    else if(input == 's'){
      cout << "save filename: ";
      string filename;
      if((cin >> filename)){
	if(!filename.find(".cpp") || !filename.find(".h")){ 
	  cout << "invalid filename, try again" << endl; // prevents user from overriding any important files
	  break;
	}
	std::ofstream fout(filename);
	fout << game.toString();
	break;
      }
      
    }
    
    else if (input == 'p'){
      game.getCurPlayer().fillPlayerHand(game.getDraw());//fill each players hand to 5
      char input2;
      bool endTurn = false;
      while(!endTurn) {
	if (game.getCurPlayer().getStockSize() == 0) {
	  winner = game.getCurp()+1;
	  break;
	}
	if (endTurn)
	  endTurn = false;
	game.display();
	cout << "(m)ove [start] [end] or (d)raw ? ";
	
	
	//input checking
	std::string checkLength;
	cin >> checkLength;
	if (checkLength.length() != 1 && checkLength.length() != 0) {
	  cout << "illegal command, try again" << endl << endl;
	  continue;
	}
	else if(checkLength.length()==0){
	  cin >> input2;
	}
	else
	  input2 = checkLength[0];


	//when user inputs (d)raw
	if(input2 == 'd'){
	  if(game.getCurPlayer().getHandSize() != 0){
	    cout << "illegal command, try again" << endl << endl;
	    continue;
	  }
	  else{
	    game.getCurPlayer().fillPlayerHand(game.getDraw());  
	  }
	}
	//when user inputs (m)ove
	else if (input2 == 'm'){
	  bool moved = false;
	  string in1,in2;
          int moveFrom;
	  char  moveTo;
	  
	  if (!(cin >> in1) || !validMoveFrom(in1)) {
	    cout << "illegal command, try again" << endl << endl;
	    continue;
	  }
	  if (!(cin >> in2) || !validMoveTo(in2)) {
	    cout << "illegal command, try again" << endl << endl;
	    continue;
	  }

	  moveFrom = in1[0]-'0';
	  moveTo = in2[0];
	  
	  switch(moveTo){
	  case 'a':{
	    if(moveFrom == 0){
	      Card c = game.getCurPlayer().viewFromStock();
	      if(!game.getBuildPile(0).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromStock();
	      moved = true;
	      if(game.checkFullBuild()){
		continue;
	      }
	    }
	    else if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(!game.getBuildPile(0).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromHand(moveFrom-5);
	      moved = true;
	    }
	    break;
	  }
	  case 'b':{
	    if(moveFrom == 0){
	      Card c = game.getCurPlayer().viewFromStock();
	      if(!game.getBuildPile(1).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromStock();
	      moved = true;
	      if(game.checkFullBuild()){
		continue;
	      }
	    }
	    else if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(!game.getBuildPile(1).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromHand(moveFrom-5);
	      moved = true;
	    }
	    break;
	  }
	  case 'c':{
	    if(moveFrom == 0){
	      Card c = game.getCurPlayer().viewFromStock();
	      if(!game.getBuildPile(2).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromStock();
	      moved = true;
	      if(game.checkFullBuild()){
		continue;
	      }
	    }
	    else if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(!game.getBuildPile(2).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromHand(moveFrom-5);
	      moved = true;
	    }
	    break;
	  }
	  case 'd':{
	    if(moveFrom == 0){
	      Card c = game.getCurPlayer().viewFromStock();
	      if(!game.getBuildPile(3).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromStock();
	      moved = true;
	      if(game.checkFullBuild()){
		continue;
	      }
	    }
	    else if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(!game.getBuildPile(3).build(c) || c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      c = game.getCurPlayer().takeFromHand(moveFrom-5);
	      moved = true;
	    }
	    break;
	  }
	  case '1':{
	    if (moveFrom >= 0 && moveFrom <= 4) {
	      cout << "illegal command, try again" << endl << endl;
	      continue;
	    }      
	    if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      } 
	      if(!game.getCurPlayer().addDiscard(c,0)){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      else{
		c = game.getCurPlayer().takeFromHand(moveFrom-5);
		moved = true;
		endTurn = true;
	      }
	    }
	    break;
	  }
	  case '2':{
	    if (moveFrom >= 0 && moveFrom <= 4) {
	      cout << "illegal command, try again" << endl << endl;
	      continue;
	    }
	    if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      } 
	      if(!game.getCurPlayer().addDiscard(c,1)){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      else{
		c = game.getCurPlayer().takeFromHand(moveFrom-5);
		moved = true;
		endTurn = true;
	      }
	    }
	    break;
	  }
	  case '3':{
	    if (moveFrom >= 0 && moveFrom <= 4) {
	      cout << "illegal command, try again" << endl << endl;
	      continue;
	    }
	    if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      if(!game.getCurPlayer().addDiscard(c,2)){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      else{
		c = game.getCurPlayer().takeFromHand(moveFrom-5);
		moved = true;
		endTurn = true;
	      }
	    }
	    break;
	  }
	  case '4':{
	    if (moveFrom >= 0 && moveFrom <= 4) {
	      cout << "illegal command, try again" << endl << endl;
	      continue;
	    }
	    if(moveFrom < 10 && moveFrom > 4){
	      Card c = game.getCurPlayer().viewFromHand(moveFrom-5);
	      if(c.getValue() == -1){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      } 
	      if(!game.getCurPlayer().addDiscard(c,3)){
		cout << "illegal command, try again" << endl << endl;
		continue;
	      }
	      else{
		c = game.getCurPlayer().takeFromHand(moveFrom-5);
		moved = true;
		endTurn = true;
	      }
	    }
	    break;
	  }
	  default:{
	    cout << "illegal command, try again" << endl << endl;
	    continue;
	    break;
	  }
	  }
	  if (!moved) {
	    cout << "illegal command, try again" << endl << endl;
	    continue;
	  }
	  
	}
	//belongs to else if(m)
    	else {
	  cout << "illegal command, try again" << endl << endl;
	  continue;
	}
	cout << endl;
	if (endTurn) {
	  game.display();
	  game.incrementCurp();
	  cout << endl;
	}
      }
    }
    else {
      cout << "illegal command, try again" << endl << endl;
      continue;
    }

  }while(input != 'q' || winner);

  if (winner)
    cout << "GAME OVER - Player" << winner - 1 << " wins!" << endl;
}
