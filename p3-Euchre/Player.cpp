#include "Player.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Simple : public Player {
public:
  Simple(const string &player_name) : name(player_name) {}

  const string &get_name() const override { return name; }

  void add_card(const Card &c) override {
    assert(hand.size() < MAX_HAND_SIZE);
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer, int round,
                  Suit &order_up_suit) const override {
    assert(round == 1 || round == 2);

    int trump_cnt = 0;
    Suit proposed_suit;

    if (round == 1) {
      proposed_suit = upcard.get_suit();
      for (const auto &card : hand) {
        if (card.is_trump(proposed_suit) && card.is_face_or_ace()) {
          trump_cnt++;
        }
      }
      if (trump_cnt >= 2) {
        order_up_suit = proposed_suit;
        return true;
      }
    } else if (round == 2) {
      if (is_dealer) {
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
      }
      proposed_suit = Suit_next(upcard.get_suit());
      for (const auto &card : hand) {
        if (card.is_trump(proposed_suit) && card.is_face_or_ace()) {
         trump_cnt++; 
        }
      }
      if (trump_cnt >= 1) {
        order_up_suit = proposed_suit;
        return true;
      }
    }
    return false;
  }
  void add_and_discard(const Card &upcard) override {
    assert(!hand.empty());

    hand.push_back(upcard);
    Suit trump = upcard.get_suit();

    size_t lowest_idx = 0;
    for (size_t i = 0; i < hand.size(); i++) {
      if (Card_less(hand[i], hand[lowest_idx], trump)) {
        lowest_idx = i;
       }
    }
    hand.erase(hand.begin() + lowest_idx);
  }

  Card lead_card(Suit trump) override {
    assert(!hand.empty());
    size_t idx = 0;
    bool ifnonTrump = false;

    for (size_t i = 0; i < hand.size(); i++) {
      if (!ifnonTrump) {
        if (!hand[i].is_trump(trump)) {
          ifnonTrump = true;
          idx = i;
        } else {
          if (Card_less(hand[idx], hand[i], trump)) {
            idx = i;
          }
        }
      } else {
        if (!hand[i].is_trump(trump)) {
          if (Card_less(hand[idx], hand[i], trump)) {
          idx = i;
            }
        }
      }
    }
    Card played = hand[idx];
    hand.erase(hand.begin() + idx);
    return played;
  }

  Card play_card(const Card &led_card, Suit trump) override {
    assert(!hand.empty());

    Suit led_suit = led_card.get_suit();
    if (led_card.is_left_bower(trump)) {
      led_suit = trump;
    }

    vector<size_t> follow_suit_indices;
    for (size_t i = 0; i < hand.size(); i++) {
      Suit card_suit = hand[i].get_suit();
      if (hand[i].is_left_bower(trump)) {
        card_suit = trump;
      }
      if (card_suit == led_suit) {
        follow_suit_indices.push_back(i);
      }
    }

    size_t idx = 0;

    if (!follow_suit_indices.empty()) {
      idx = follow_suit_indices[0];
      for (size_t x : follow_suit_indices) {
        if (Card_less(hand[idx], hand[x], led_card, trump)){
          idx = x;
        }
      }
    } else {
      for (size_t i = 1; i < hand.size(); ++i) {
        if (Card_less(hand[i], hand[idx], led_card, trump)) {
            idx = i;
        }
      }
    }
    Card played = hand[idx];
    hand.erase(hand.begin() + idx);
    return played;
  }

private:
  string name;
  vector<Card> hand;
};

class Human : public Player {
public:
  Human(const string &player_name) : name(player_name) {}

  const string &get_name() const override { return name; }

  void add_card(const Card &c) override {
    assert(hand.size() < MAX_HAND_SIZE);
    hand.push_back(c);
    sort(hand.begin(), hand.end());
  }

  bool make_trump(const Card &upcard, bool is_dealer, int round,
                  Suit &order_up_suit) const override {
    assert(round == 1 || round == 2);

    print_hand();
    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

    string decision;
    cin >> decision;
    if (decision != "pass") {
      order_up_suit = string_to_suit(decision);
      return true;
    }
    return false;
  }

  void add_and_discard(const Card &upcard) override {
    assert(!hand.empty());

    print_hand();
    std::cout << "Discard upcard: [-1]\n";
    std::cout << "Human player " << name
              << ", please select a card to discard:\n";

    int decision;
    cin >> decision;

    if (decision == -1) {
      return;
    } else {
      assert(decision >= 0 && static_cast<size_t>(decision) < hand.size());
      hand.erase(hand.begin() + decision);
      hand.push_back(upcard);
      sort(hand.begin(), hand.end());
    }
  }

  Card lead_card(Suit trump) override {
    assert(!hand.empty());
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";

    size_t decision;
    cin >> decision;
    assert(decision < hand.size());

    Card played = hand[decision];
    hand.erase(hand.begin() + decision);
    return played;
  }

  Card play_card(const Card &led_card, Suit trump) override {
    assert(!hand.empty());
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";

    size_t decision;
    cin >> decision;
    assert(decision < hand.size());

    Card played = hand[decision];
    hand.erase(hand.begin() + decision);
    return played;
  }

private:
  string name;
  vector<Card> hand;

  void print_hand() const {
    for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
  }
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Simple")
    return new Simple(name);
  if (strategy == "Human")
    return new Human(name);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}