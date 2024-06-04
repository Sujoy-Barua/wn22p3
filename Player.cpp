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

#include "Player.h"

using namespace std;

class Simple : public Player {
private:
  string name;
  vector<Card> p_hand;
  int count_facetrump(const string upcardSuit, int counter) const {
    counter = 0;
    for (size_t i = 0; i < p_hand.size(); i++) {
      if (p_hand[i].is_face_or_ace() 
          && p_hand[i].is_trump(upcardSuit)) {
        counter++;
      }
    }
    return counter;
  }

public:
  Simple(const string &name_in)
  : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    p_hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, string &order_up_suit) const override {
    int count_face_of_trump = 0;

    
    if (round == 1) {
      count_face_of_trump = count_facetrump(upcard.get_suit(), count_face_of_trump);
      if (count_face_of_trump >= 2) {
        count_face_of_trump = 0;
        order_up_suit = upcard.get_suit();
        return true;
      } else {
        count_face_of_trump = 0;
        return false;
      }
    } 
    else {
      if (is_dealer) {
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
      } 
      else {
        count_face_of_trump = count_facetrump(Suit_next(upcard.get_suit()),
                               count_face_of_trump);
        if (count_face_of_trump >= 1) {
          count_face_of_trump = 0;
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        } 
        else {
          count_face_of_trump = 0;
          return false;
        }
      }
    }
  }

  void add_and_discard(const Card &upcard) override {
    p_hand.push_back(upcard);
    int curMin = 0;
    for (size_t i = 0; i < p_hand.size(); i++) {
      if (Card_less(p_hand[i], p_hand[curMin], upcard.get_suit())) {
        curMin = i;
      }
    }
    p_hand.erase(p_hand.begin() + curMin);
  }

  Card lead_card(const string &trump) override {
    bool has_nontrump = false;
    vector<Card> nontrumpCards;
    vector<int> index_nontrump;
    int curMax = 0;

    for (size_t i = 0; i < p_hand.size(); i++) {
      if (!(p_hand[i].is_trump(trump))) {
        has_nontrump = true;
        nontrumpCards.push_back(p_hand[i]);
        index_nontrump.push_back(i);
      }
    }

    if (has_nontrump) {
      for (size_t i = 0; i < nontrumpCards.size(); i++) {
        if (Card_less(nontrumpCards[curMax], nontrumpCards[i], trump)) {
          curMax = i;
        }
      }
      p_hand.erase(p_hand.begin() + index_nontrump[curMax]);
      return nontrumpCards[curMax];
    }
    else //if (!has_nontrump) 
    {
      for (size_t i = 0; i < p_hand.size(); i++) {
        if (Card_less(p_hand[curMax], p_hand[i], trump)) {
            curMax = i;
        }
      }
      Card return_card = p_hand[curMax];
      p_hand.erase(p_hand.begin() + curMax);
      return return_card;
    }
  }

  Card play_card(const Card &led_card, const string &trump) override {
    bool can_follow_suit = false;
    int curMin = 0;
    int curMax = 0;
    vector<Card> ledsuitCards;
    vector<int> index_ledsuit;
    for (size_t i = 0; i < p_hand.size(); i++) {
      if (p_hand[i].get_suit(trump) == led_card.get_suit(trump)) {
        can_follow_suit = true;
        ledsuitCards.push_back(p_hand[i]);
        index_ledsuit.push_back(i);
      }
    }

    if (can_follow_suit) {
      for (size_t i = 0; i < ledsuitCards.size(); i++) {
        if (Card_less(ledsuitCards[curMax], ledsuitCards[i], led_card, trump)) {
          curMax = i;
        }
      }
      p_hand.erase(p_hand.begin() + index_ledsuit[curMax]);
      return ledsuitCards[curMax];
    }
    else {
      for (size_t i = 0; i < p_hand.size(); i++) {
        if (!(Card_less(p_hand[curMin], p_hand[i], led_card, trump))) {
          curMin = i;
        }
      }
      Card return_card = p_hand[curMin];
      p_hand.erase(p_hand.begin() + curMin);
      return return_card;
    }
  }
};

class Human : public Player {
private:
  string name;
  vector<Card> p_hand;
  void print_hand() const {
    for (size_t i = 0; i < p_hand.size(); ++i) {
      cout << "Human player " << name << "'s hand: "
          << "[" << i << "] " << p_hand[i] << "\n";
    }
  }

public:
  Human(const string &name_in)
  : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    p_hand.push_back(c);
    sort(p_hand.begin(), p_hand.end());
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, string &order_up_suit) const override {
    string input;
    print_hand();
    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
    cin >> input;
    if (input == "Spades") {
      order_up_suit = Card::SUIT_SPADES;
      return true;
    }
    else if (input == "Hearts") {
      order_up_suit = Card::SUIT_HEARTS;
      return true;
    }
    else if (input == "Clubs") {
      order_up_suit = Card::SUIT_CLUBS;
      return true;
    }
    else if (input == "Diamonds") {
      order_up_suit = Card::SUIT_DIAMONDS;
      return true;
    }
    else //if (input == "pass") 
    {
      return false;
    }
  }

  void add_and_discard(const Card &upcard) override {
    sort(p_hand.begin(), p_hand.end());
    int discardIndex;
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    cin >> discardIndex;
    if (discardIndex >= 0 && discardIndex < p_hand.size()) {
      p_hand.erase(p_hand.begin() + discardIndex);
      p_hand.push_back(upcard);
      sort(p_hand.begin(), p_hand.end());
    }
  }

  Card lead_card(const string &trump) override {
    int cardIndex;
    sort(p_hand.begin(), p_hand.end());
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    cin >> cardIndex;
    Card return_card = p_hand[cardIndex];
    p_hand.erase(p_hand.begin() + cardIndex);
    return return_card;
  }

  Card play_card(const Card &led_card, const string &trump) override {
    return Human::lead_card(trump);
  }
};

Player * Player_factory(const string &name, const string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new Simple(name);
  }
  else if (strategy == "Human") {
    return new Human(name);
  } 
  else {
    return nullptr;
  }
}

ostream & operator<<(ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}