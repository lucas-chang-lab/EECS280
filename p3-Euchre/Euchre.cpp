#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"

using namespace std;

class Game {
public:
  Game(const string &pack_filename, const string &shuffle_arg, 
       int points_to_win, const vector<pair<string, string>> &player_info) 
    : points_to_win(points_to_win), hand_count(0), 
      score_team1(0), score_team2(0), ordered_up_team(-1) {
    
    ifstream fin(pack_filename);
    if (!fin.is_open()) {
      cout << "Error opening " << pack_filename << endl;
      exit(1); 
    }
    pack = Pack(fin);
    do_shuffle = (shuffle_arg == "shuffle");

    for (const auto &p : player_info) {
      players.push_back(Player_factory(p.first, p.second));
    }
  }

  ~Game() {
    for (size_t i = 0; i < players.size(); ++i) {
      delete players[i];
    }
  }

  void play() {
    while (score_team1 < points_to_win && score_team2 < points_to_win) {
      play_hand();
      hand_count++;
    }

    if (score_team1 >= points_to_win) {
      cout << players[0]->get_name() << " and " 
           << players[2]->get_name() << " win!\n";
    } else {
      cout << players[1]->get_name() << " and " 
           << players[3]->get_name() << " win!\n";
    }
  }

private:
  std::vector<Player*> players;
  Pack pack;
  int points_to_win;
  bool do_shuffle;
  int hand_count;
  int score_team1; 
  int score_team2; 
  
  Suit trump;
  int ordered_up_team;

  void shuffle() {
    if (do_shuffle) {
      pack.shuffle();
    } else {
      pack.reset();
    }
  }

  void deal(int dealer_idx) {
    int p1 = (dealer_idx + 1) % 4;
    int p2 = (dealer_idx + 2) % 4;
    int p3 = (dealer_idx + 3) % 4;
    int d  = dealer_idx;

    deal_cards(players[p1], 3);
    deal_cards(players[p2], 2);
    deal_cards(players[p3], 3);
    deal_cards(players[d],  2);

    deal_cards(players[p1], 2);
    deal_cards(players[p2], 3);
    deal_cards(players[p3], 2);
    deal_cards(players[d],  3);
  }

  void deal_cards(Player* p, int num) {
    for (int i = 0; i < num; ++i) {
      p->add_card(pack.deal_one());
    }
  }

  bool run_making_round(int round, int dealer_idx, Card upcard) {
    for (int i = 1; i <= 4; ++i) {
      int current = (dealer_idx + i) % 4;
      Suit order_up_suit = (round == 1) ? upcard.get_suit() : Suit();
      
      if (!players[current]->make_trump(upcard, (current == dealer_idx), 
                                       round, order_up_suit)) {
        cout << players[current]->get_name() << " passes\n";
        continue;
      }

      trump = order_up_suit;
      cout << players[current]->get_name() << " orders up " 
           << trump << "\n\n";
        
      if (round == 1) {
        players[dealer_idx]->add_and_discard(upcard);
      }
      ordered_up_team = (current % 2 == 0) ? 0 : 1;
      return true;
    }
    return false;
  }

  int play_trick(int leader_idx, int &team1_tricks, int &team2_tricks) {
    Card led_card = players[leader_idx]->lead_card(trump);
    cout << led_card << " led by " << players[leader_idx]->get_name() << "\n";

    Card winning_card = led_card;
    int winner_idx = leader_idx;

    for (int i = 1; i < 4; ++i) {
      int current = (leader_idx + i) % 4;
      Card played = players[current]->play_card(led_card, trump);
      cout << played << " played by " << players[current]->get_name() << "\n";

      if (Card_less(winning_card, played, led_card, trump)) {
        winning_card = played;
        winner_idx = current;
      }
    }

    cout << players[winner_idx]->get_name() << " takes the trick\n\n";
    if (winner_idx % 2 == 0) {
      team1_tricks++;
    } else {
      team2_tricks++;
    }
    return winner_idx;
  }

  void play_hand() {
    int dealer_idx = hand_count % 4;
    cout << "Hand " << hand_count << "\n"
         << players[dealer_idx]->get_name() << " deals\n";

    shuffle();
    deal(dealer_idx);

    Card upcard = pack.deal_one();
    cout << upcard << " turned up\n";

    ordered_up_team = -1;
    
    bool made = run_making_round(1, dealer_idx, upcard);
    if (!made) {
      run_making_round(2, dealer_idx, upcard);
    }

    int leader_idx = (dealer_idx + 1) % 4;
    int team1_tricks = 0;
    int team2_tricks = 0;

    for (int trick = 0; trick < 5; ++trick) {
      leader_idx = play_trick(leader_idx, team1_tricks, team2_tricks);
    }

    announce_hand_winners(ordered_up_team, team1_tricks, team2_tricks);
  }

  void update_team1_score(int ordered_up_team, int team1_tricks) {
    if (ordered_up_team == 0) {
      if (team1_tricks == 5) {
        cout << "march!\n";
        score_team1 += 2;
      } else {
        score_team1 += 1;
      }
    } else {
      cout << "euchred!\n";
      score_team1 += 2;
    }
  }

  void update_team2_score(int ordered_up_team, int team2_tricks) {
    if (ordered_up_team == 1) {
      if (team2_tricks == 5) {
        cout << "march!\n";
        score_team2 += 2;
      } else {
        score_team2 += 1;
      }
    } else {
      cout << "euchred!\n";
      score_team2 += 2;
    }
  }

  void announce_hand_winners(int ordered_up_team, int team1_tricks, 
                             int team2_tricks) {
    if (team1_tricks > team2_tricks) {
      cout << players[0]->get_name() << " and " 
           << players[2]->get_name() << " win the hand\n";
      update_team1_score(ordered_up_team, team1_tricks);
    } else {
      cout << players[1]->get_name() << " and " 
           << players[3]->get_name() << " win the hand\n";
      update_team2_score(ordered_up_team, team2_tricks);
    }

    cout << "\n" 
         << players[0]->get_name() << " and " << players[2]->get_name() 
         << " have " << score_team1 << " points\n"
         << players[1]->get_name() << " and " << players[3]->get_name() 
         << " have " << score_team2 << " points\n\n";
  }
};

bool validate_arguments(int argc, char* argv[]) {
  if (argc != 12) return false;
  
  string shuffle_arg = argv[2];
  if (shuffle_arg != "shuffle" && shuffle_arg != "noshuffle") return false;

  int pts = stoi(argv[3]);
  if (pts < 1 || pts > 100) return false;

  for (int i = 0; i < 4; ++i) {
    string type = argv[5 + i * 2];
    if (type != "Simple" && type != "Human") return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  if (!validate_arguments(argc, argv)) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
         << "NAME4 TYPE4" << endl;
    return 1;
  }

  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << " ";
  }
  cout << endl;

  string pack_filename = argv[1];
  string shuffle_arg = argv[2];
  int points_to_win = stoi(argv[3]);

  vector<pair<string, string>> player_info;
  for (int i = 0; i < 4; ++i) {
    player_info.push_back({argv[4 + i * 2], argv[5 + i * 2]});
  }

  Game game(pack_filename, shuffle_arg, points_to_win, player_info);
  game.play();

  return 0;
}
