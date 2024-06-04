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

#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

Card::Card(const string &rank_in, const string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

string Card::get_rank() const {
    return rank;
}

string Card::get_suit() const {
    return suit;
}

string Card::get_suit(const string &trump) const {
    if (Card::is_left_bower(trump)) {
        return trump;
    } else {
        return suit;
    }
}

bool Card::is_face_or_ace() const {
    if (rank == RANK_JACK || rank == RANK_ACE 
        || rank == RANK_KING || rank == RANK_QUEEN) {
        return true;
    } else {
        return false;
    }
}

bool Card::is_right_bower(const string &trump) const {
    if (rank == RANK_JACK && suit == trump) {
        return true;
    } else {
        return false;
    }
}

bool Card::is_left_bower(const string &trump) const {
    if (rank == RANK_JACK) {
        if (trump == SUIT_DIAMONDS && suit == SUIT_HEARTS) {
            return true;
        } else if (trump == SUIT_HEARTS && suit == SUIT_DIAMONDS) {
            return true;
        } else if (trump == SUIT_CLUBS && suit == SUIT_SPADES) {
            return true;
        } else if (trump == SUIT_SPADES && suit == SUIT_CLUBS) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Card::is_trump(const string &trump) const {
    if (suit == trump || Card::is_left_bower(trump)) {
        return true;
    } else {
        return false;
    }
}

void rankComparison (const Card &lhs, const Card &rhs, int &lhs_value, int &rhs_value) {
    for (size_t i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() != RANK_NAMES_BY_WEIGHT[i]) {
            lhs_value++;
        } else if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lhs_value++;
            break;
        }
    }
    for (size_t i = 0; i < NUM_RANKS; i++) {
        if (rhs.get_rank() != RANK_NAMES_BY_WEIGHT[i]) {
            rhs_value++;
        } else if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rhs_value++;
            break;
        }
    }
}

bool operator<(const Card &lhs, const Card &rhs) {
    int lhs_value = 0;
    int rhs_value = 0;
    rankComparison (lhs, rhs, lhs_value, rhs_value);
    if (lhs_value < rhs_value) {
        return true;
    } else if (lhs_value == rhs_value) {
        for (size_t i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() != SUIT_NAMES_BY_WEIGHT[i]) {
                lhs_value++;
            } else if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhs_value++;
                break;
            }
        }
        for (size_t i = 0; i < NUM_SUITS; i++) {
            if (rhs.get_suit() != SUIT_NAMES_BY_WEIGHT[i]) {
                rhs_value++;
            } else if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhs_value++;
                break;
            }
        }
        if (lhs_value < rhs_value) {
            return true;
        } else {
            return false;
        }   
    } else {
    return false;
    }
}

bool operator<=(const Card &lhs, const Card &rhs) {
    if (lhs < rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
}

bool operator>(const Card &lhs, const Card &rhs) {
    if (lhs <= rhs) {
        return false;
    }
    else {
        return true;
    }
}

bool operator>=(const Card &lhs, const Card &rhs) {
    if (lhs < rhs) {
        return false;
    }
    else {
        return true;
    }
}

bool operator==(const Card &lhs, const Card &rhs) {
    if ((lhs.get_rank() == rhs.get_rank()) 
        && (lhs.get_suit() == rhs.get_suit())) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const Card &lhs, const Card &rhs) {
    if ((lhs.get_rank() == rhs.get_rank()) 
        && (lhs.get_suit() == rhs.get_suit())) {
        return false;
    } else {
        return true;
    }
}

string Suit_next(const string &suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    } else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    } else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    } else {
        return Card::SUIT_DIAMONDS;
    }
}

ostream & operator<<(ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const string &trump) {
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a.is_left_bower(trump) && b.is_right_bower(trump)) {
            return true;
        }
        else if (a.is_right_bower(trump) && b.is_left_bower(trump)) {
            return false;
        }
        else if (a.is_left_bower(trump) && b.is_left_bower(trump)) {
            return false;
        }
        else if (a.is_right_bower(trump) && b.is_right_bower(trump)) {
            return false;
        }
        else if (a.is_left_bower(trump) && !b.is_left_bower(trump)) {
            return false;
        }
        else if (a.is_right_bower(trump) && !b.is_right_bower(trump)) {
            return false;
        }
        else if (!a.is_right_bower(trump) && b.is_right_bower(trump)) {
            return true;
        }
        else if (!a.is_left_bower(trump) && b.is_left_bower(trump)) {
            return true;
        }
        else { 
            return a < b;
        }
    } 
    else if (a.is_trump(trump) && !(b.is_trump(trump))) {
        return false;
    }
    else if (!(a.is_trump(trump)) && b.is_trump(trump)) {
        return true;
    }
    else {
        return a < b;
    }
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const string &trump) {
    
    if (a.is_trump(trump) && b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }
    else if ((a.get_suit(trump) != led_card.get_suit(trump)) 
        && (b.get_suit(trump) != led_card.get_suit(trump))) {
        return Card_less(a, b, trump);
    }
    else if (a.is_trump(trump) && (b.get_suit(trump) == led_card.get_suit(trump))) {
        return false;
    }
    else if ((a.get_suit(trump) == led_card.get_suit(trump)) && b.is_trump(trump)) {
        return true;
    }
    else if ((a.get_suit(trump) != led_card.get_suit(trump)) 
    && (b.get_suit(trump) == led_card.get_suit(trump))) {
        return true;
    }
    else if ((a.get_suit(trump) == led_card.get_suit(trump)) 
    && (b.get_suit(trump) != led_card.get_suit(trump))) {
        return false;
    }
    else {
        return a < b;
    }
    
}