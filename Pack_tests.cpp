// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());
}

// Add more tests here

static const int PACK_SIZE = 24;


TEST(test_pack_istream_ctor) {
  const string filename = "pack.in";
  ifstream ifs(filename);
  assert(ifs.is_open());
  Pack pack(ifs);
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_pack_reset) {
  Pack pack;
  pack.deal_one();
  pack.reset();
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_pack_empty) {
  Pack pack;
  for (int i = 0; i < PACK_SIZE - 1; ++i) {
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
  }
  pack.deal_one();
  ASSERT_TRUE(pack.empty());
}

TEST(test_pack_shuffle) {
  Pack pack;
  pack.shuffle();
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_KING, Card::SUIT_CLUBS));
}

TEST_MAIN()
