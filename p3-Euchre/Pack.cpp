#include "Card.hpp"
#include "Pack.hpp"
#include <array>
#include <string>

using namespace std;
  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack() {
    int index = 0;
    for (int i = SPADES; i <= DIAMONDS; i++) {
      for (int j = NINE; j <= ACE; j++) {
        Suit suit = static_cast<Suit>(i);
        Rank rank = static_cast<Rank>(j);

        cards[index] = Card(rank, suit);
        index++;
      }
    }
    next = 0;
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(std::istream &pack_input) {
    string rank_input;
    string of_input;
    string suit_input;

    for (int i = 0; i < PACK_SIZE; i++) {
      pack_input >> rank_input >> of_input >> suit_input;
      Rank rank = string_to_rank(rank_input);
      Suit suit = string_to_suit(suit_input);
      cards[i] = Card(rank, suit);
    }
    next = 0;
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    return cards[next++];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle() {
    for (int times = 0; times < 7; times++) {
      array<Card, PACK_SIZE> cards2;
      int cnt = 0;

      for (int i = 0; i < 12; i++) {
      cards2[cnt] = cards[12 + i];
      cnt++;
      cards2[cnt] = cards[i];
      cnt++;
      }
      cards = cards2;
    }
    next = 0;
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const {
    return next == 24;
  }

