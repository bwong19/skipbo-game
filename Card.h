#ifndef _CARD_H
#define _CARD_H

/*************************************
For SkipBo - Fall 2018 - EN.601.220
Instructor provided code
*************************************/

class Card {
 public:
 Card(): value(0) { }
 Card(int v) { value = v >= -1 && v <= 12 ? v : 0; }
 int getValue() const { return value; }
 std::string toString() const;  // for printing/file saving
 void display() const;   // live game play

 private:
  int value;  // 0 for skip-bo card
};

#endif
