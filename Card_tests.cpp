// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card d;
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    ASSERT_EQUAL(Card::RANK_TWO, d.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, d.get_suit());
}

// Add more test cases here

TEST(test_card_face_or_ace) {
    Card c(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card g(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(true, c.is_face_or_ace());
    ASSERT_EQUAL(true, d.is_face_or_ace());
    ASSERT_EQUAL(true, e.is_face_or_ace());
    ASSERT_EQUAL(true, f.is_face_or_ace());
    ASSERT_EQUAL(false, g.is_face_or_ace());
}

TEST(test_card_is_left_bower)  {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, c.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_EQUAL(false, c.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(false, d.is_left_bower(Card::SUIT_SPADES));
    ASSERT_EQUAL(true, d.is_left_bower(Card::SUIT_CLUBS));
}

TEST(test_card_is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    ASSERT_EQUAL(true, c.is_right_bower(Card::SUIT_SPADES));
    ASSERT_EQUAL(false, c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, d.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, d.is_right_bower(Card::SUIT_DIAMONDS));
}

TEST(test_card_is_trump) {
    Card c(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    Card e(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card f(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, c.is_trump(Card::SUIT_SPADES));
    ASSERT_EQUAL(true, d.is_trump(Card::SUIT_SPADES));
    ASSERT_EQUAL(true, e.is_trump(Card::SUIT_SPADES));
    ASSERT_EQUAL(false, c.is_trump(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, f.is_trump(Card::SUIT_HEARTS));
}

TEST(test_card_less_w_trump) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card e(Card::RANK_ACE, Card::SUIT_SPADES);
    Card f(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card g(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(false, Card_less(c, d, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(e, c, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(e, c, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(f, c, Card::SUIT_SPADES));
    ASSERT_EQUAL(false, Card_less(c, f, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(d, g, Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(false, Card_less(d, d, Card::SUIT_DIAMONDS));

}

TEST(test_card_less_w_trump_led) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card f(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card g(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card led(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, Card_less(c, d, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(d, e, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(e, f, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(false, Card_less(e, d, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(f, c, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(d, f, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(false, Card_less(f, d, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(true, Card_less(g, d, led, Card::SUIT_SPADES));
    ASSERT_EQUAL(false, Card_less(g, g, led, Card::SUIT_SPADES));

}


TEST(test_comparison_operators) {
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card g(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card f(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card e(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_EQUAL(true, c < d);
    ASSERT_EQUAL(false, d < e);
    ASSERT_EQUAL(true, e < f);
    ASSERT_EQUAL(true, f < g);
    ASSERT_EQUAL(false, g < g);

    ASSERT_EQUAL(true, c <= d);
    ASSERT_EQUAL(false, d <= e);
    ASSERT_EQUAL(true, e <= f);
    ASSERT_EQUAL(true, f <= g)
    ASSERT_EQUAL(true, g <= g);

    ASSERT_EQUAL(false, c > d);
    ASSERT_EQUAL(true, d > e);
    ASSERT_EQUAL(false, e > f);
    ASSERT_EQUAL(false, f > g);
    ASSERT_EQUAL(false, g > g);

    ASSERT_EQUAL(false, c >= d);
    ASSERT_EQUAL(true, d >= e);
    ASSERT_EQUAL(false, e >= f);
    ASSERT_EQUAL(false, f >= g);
    ASSERT_EQUAL(true, g >= g);

    ASSERT_EQUAL(false, c == d);
    ASSERT_EQUAL(false, d == e);
    ASSERT_EQUAL(true, c == c2);
    ASSERT_EQUAL(false, f == g);
    ASSERT_EQUAL(true, g == g);

    ASSERT_EQUAL(true, c != d);
    ASSERT_EQUAL(true, d != e);
    ASSERT_EQUAL(false, c != c2);
    ASSERT_EQUAL(true, f != g);
    ASSERT_EQUAL(false, g != g);
}


TEST(test_printer_operator) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
    ASSERT_NOT_EQUAL(oss.str(), "Three of Clubs");
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
}


TEST(test_card_less_w_trump_led_2) {
    Card adi(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card bar(Card::RANK_KING, Card::SUIT_HEARTS);
    Card chi(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card dab(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card led(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, Card_less(adi, bar, led, Card::SUIT_HEARTS));
    ASSERT_EQUAL(true, Card_less(chi, bar, led, Card::SUIT_HEARTS));
    ASSERT_EQUAL(true, Card_less(dab, bar, led, Card::SUIT_HEARTS));
    ASSERT_EQUAL(false, Card_less(bar, bar, led, Card::SUIT_HEARTS));
    

}
TEST_MAIN()
