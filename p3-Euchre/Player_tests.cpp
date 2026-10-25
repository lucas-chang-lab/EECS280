#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_basics) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Player * lucas = Player_factory("Lucas", "Human");
    ASSERT_EQUAL("Lucas", lucas->get_name());
    ostringstream os;
    os << *alice;
    ASSERT_EQUAL(os.str(), "Alice");
    delete alice;
    delete lucas;
}

TEST(test_simple_player) {
  Player * bob = Player_factory("Bob", "Simple");
    Suit ordered_suit;

    bob->add_card(Card(TWO, DIAMONDS)); bob->add_card(Card(THREE, DIAMONDS));
    bob->add_card(Card(NINE, SPADES));  bob->add_card(Card(TEN, CLUBS)); bob->add_card(Card(JACK, HEARTS));
    ASSERT_FALSE(bob->make_trump(Card(ACE, DIAMONDS), false, 1, ordered_suit));
    delete bob;

    bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, CLUBS)); bob->add_card(Card(ACE, SPADES)); // Both count as Spades Trump
    bob->add_card(Card(NINE, HEARTS)); bob->add_card(Card(TEN, HEARTS)); bob->add_card(Card(TWO, DIAMONDS));
    ASSERT_TRUE(bob->make_trump(Card(KING, SPADES), false, 1, ordered_suit));
    ASSERT_EQUAL(ordered_suit, SPADES);
    delete bob;

    bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(KING, CLUBS)); bob->add_card(Card(NINE, SPADES)); // Upcard Spades -> Next is Clubs
    bob->add_card(Card(TEN, HEARTS)); bob->add_card(Card(TWO, DIAMONDS)); bob->add_card(Card(THREE, DIAMONDS));
    ASSERT_TRUE(bob->make_trump(Card(ACE, SPADES), false, 2, ordered_suit));
    ASSERT_EQUAL(ordered_suit, CLUBS);
    delete bob;

    bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(TWO, SPADES)); bob->add_card(Card(THREE, SPADES));
    bob->add_card(Card(FOUR, HEARTS)); bob->add_card(Card(FIVE, DIAMONDS)); bob->add_card(Card(SIX, DIAMONDS));
    ASSERT_TRUE(bob->make_trump(Card(ACE, SPADES), true, 2, ordered_suit));
    ASSERT_EQUAL(ordered_suit, CLUBS);
    delete bob;
}

TEST(test_simple_player_gameplay) {
    Player * bob = Player_factory("Bob", "Simple");
   
    bob->add_card(Card(KING, SPADES)); bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(JACK, CLUBS));  bob->add_card(Card(JACK, SPADES)); bob->add_card(Card(NINE, HEARTS));
    bob->add_and_discard(Card(TEN, SPADES));
    for(int i=0; i<5; ++i) {
        ASSERT_FALSE(bob->lead_card(SPADES) == Card(NINE, HEARTS));
    }
    delete bob;

    bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, SPADES)); bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(TEN, HEARTS)); bob->add_card(Card(ACE, HEARTS)); bob->add_card(Card(NINE, DIAMONDS));
    ASSERT_EQUAL(bob->lead_card(SPADES), Card(ACE, HEARTS));
    delete bob;

    bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS)); bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(ACE, SPADES));  bob->add_card(Card(KING, CLUBS)); bob->add_card(Card(TEN, DIAMONDS));
    ASSERT_EQUAL(bob->play_card(Card(TEN, HEARTS), SPADES), Card(QUEEN, HEARTS));
    delete bob;

    bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, CLUBS)); bob->add_card(Card(NINE, CLUBS)); bob->add_card(Card(TEN, HEARTS));
    ASSERT_EQUAL(bob->play_card(Card(NINE, SPADES), SPADES), Card(JACK, CLUBS));
    delete bob;
}

TEST(test_human_player_stream_inputs) {
    streambuf * orig_cin = cin.rdbuf();

    {
        Player * human = Player_factory("Siri", "Human");
        Suit order_suit;
        stringstream stream_bidding("pass Hearts");
        cin.rdbuf(stream_bidding.rdbuf());

        human->add_card(Card(TWO, SPADES));
        ASSERT_FALSE(human->make_trump(Card(ACE, HEARTS), false, 1, order_suit));
        ASSERT_TRUE(human->make_trump(Card(ACE, HEARTS), false, 1, order_suit));
        ASSERT_EQUAL(order_suit, HEARTS);

        delete human;
    }

    {
        Player * human = Player_factory("Siri", "Human");
        stringstream stream_discard1("-1 0"); 
        cin.rdbuf(stream_discard1.rdbuf());

        human->add_card(Card(TWO, SPADES));
        human->add_and_discard(Card(ACE, HEARTS)); 
        ASSERT_EQUAL(human->lead_card(SPADES), Card(TWO, SPADES));

        delete human;
    }

    {
        Player * human = Player_factory("Siri", "Human");
        stringstream stream_discard2("0 0");
        cin.rdbuf(stream_discard2.rdbuf());

        human->add_card(Card(TWO, SPADES));
        human->add_and_discard(Card(ACE, HEARTS)); // Discards TWO of SPADES, hand becomes [ACE of HEARTS]
        ASSERT_EQUAL(human->lead_card(SPADES), Card(ACE, HEARTS));

        delete human;
    }

    cin.rdbuf(orig_cin);
}


TEST_MAIN()
