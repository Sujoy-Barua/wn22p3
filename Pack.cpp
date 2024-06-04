// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Pack.h"

using namespace std;

Pack::Pack() {
  int CurrentPos = 0; 
  next = 0;
  for (size_t i = 0; i < NUM_SUITS; i++) {
    for (size_t j = 7; j < NUM_RANKS; j++) {
      Card CurrentCard(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i] );
      cards[CurrentPos] = CurrentCard;
      CurrentPos++;
    }
  }
}

Pack::Pack(istream& pack_input) {
  int CurrentPos = 0;
  next = 0;
  string rankinput;
  string suitinput;
  string of;
  for (size_t i = 0; i < NUM_SUITS; i++) {
    for (size_t j = 7; j < NUM_RANKS; j++) {
      pack_input >> rankinput >> of >> suitinput;
      Card CurrentCard(rankinput, suitinput);
      cards[CurrentPos] = CurrentCard;
      CurrentPos++;
    }
  }
}

Card Pack::deal_one() {
  next++;
  return cards[next-1];
}

void Pack::reset() {
  next = 0;
}

void Pack::shuffle() {
  vector<Card> tempPack;
  for (size_t i = 0; i < PACK_SIZE; i++) {
    tempPack.push_back(cards[i]);
  }
  
  int sourceIndex;
  for (size_t i = 0; i < 7; i++) {
    sourceIndex = 12;
    for (size_t j = 0; j < PACK_SIZE; j+=2) {
      cards[j] = tempPack[sourceIndex];
      sourceIndex++;
    }

    sourceIndex = 0;
    for (size_t k = 1; k < PACK_SIZE; k+=2) {
      cards[k] = tempPack[sourceIndex];
      sourceIndex++;
    }

    for (size_t i = 0; i < PACK_SIZE; i++) {
      tempPack[i] = cards[i];
    }
  }

  reset();
}

bool Pack::empty() const {
  return (next == 24);
}

void pack_init(Pack &s) {
  s.test == 4;
}