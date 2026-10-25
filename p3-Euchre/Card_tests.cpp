#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_properties) {
    ASSERT_TRUE(Card(JACK, SPADES).is_face_or_ace());
    ASSERT_TRUE(Card(QUEEN, HEARTS).is_face_or_ace());
    ASSERT_TRUE(Card(KING, CLUBS).is_face_or_ace());
    
    ASSERT_FALSE(Card(TEN, SPADES).is_face_or_ace());
    ASSERT_FALSE(Card(NINE, HEARTS).is_face_or_ace());
}

// 3. Tests standard evaluation and Bower recognition properties
TEST(test_card_bower_and_trump_rules) {
    Suit trump = SPADES;

    Card right_bower(JACK, SPADES);
    Card left_bower(JACK, CLUBS);
    Card normal_trump(ACE, SPADES);
    Card non_trump(ACE, HEARTS);

    ASSERT_TRUE(right_bower.is_right_bower(trump));
    ASSERT_FALSE(left_bower.is_right_bower(trump));

    ASSERT_TRUE(left_bower.is_left_bower(trump));
    ASSERT_FALSE(right_bower.is_left_bower(trump));

    ASSERT_TRUE(right_bower.is_trump(trump));
    ASSERT_TRUE(left_bower.is_trump(trump)); 
    ASSERT_TRUE(normal_trump.is_trump(trump));
    ASSERT_FALSE(non_trump.is_trump(trump));
}

TEST(test_card_operators) {
    Card two_spades(TWO, SPADES);
    Card three_spades(THREE, SPADES);
    Card two_hearts(TWO, HEARTS);
    Card two_spades_dup(TWO, SPADES);

    ASSERT_TRUE(two_spades < three_spades);
    ASSERT_TRUE(two_spades <= three_spades);
    ASSERT_FALSE(two_spades > three_spades);
    ASSERT_TRUE(two_spades < two_hearts);
    ASSERT_TRUE(two_hearts > two_spades);
    ASSERT_TRUE(two_spades == two_spades_dup);
    ASSERT_TRUE(two_spades <= two_spades_dup);
    ASSERT_TRUE(two_spades >= two_spades_dup);
    ASSERT_FALSE(two_spades != two_spades_dup);
}


TEST(test_card_less_functions) {
    Suit trump = SPADES;
    Card right_bower(JACK, SPADES);
    Card left_bower(JACK, CLUBS);
    Card ace_trump(ACE, SPADES);
    Card king_trump(KING, SPADES);
    Card ace_led(ACE, HEARTS);
    Card nine_led(NINE, HEARTS);
    Card off_suit(KING, DIAMONDS);

    ASSERT_TRUE(Card_less(left_bower, right_bower, trump)); 
    ASSERT_TRUE(Card_less(ace_trump, left_bower, trump));  
    ASSERT_TRUE(Card_less(king_trump, ace_trump, trump));   
    ASSERT_TRUE(Card_less(off_suit, king_trump, trump));    
    
    ASSERT_TRUE(Card_less(off_suit, nine_led, ace_led, trump)); 
    ASSERT_TRUE(Card_less(nine_led, ace_led, ace_led, trump));  

    ASSERT_FALSE(Card_less(king_trump, ace_led, ace_led, trump)); 
}


TEST_MAIN()
