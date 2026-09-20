/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Statistics Project
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

const double epsilon = 0.00001;

static bool almost_equal(double x, double y) {
  return abs(x - y) < epsilon;
}

void test_sum_small_data_set();

// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  // Call your test functions here

  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(count(data) == 3);
  assert(sum(data) == 6);
  assert(almost_equal(mean(data), 2));
  assert(median(data) == 2);
  assert(min(data) == 1);
  assert(max(data) == 3);
  assert(almost_equal(stdev(data), 1.0));
  assert(almost_equal(percentile(data, 0.4), 1.8));

  vector<double> criteria = {0, 0, 1};
  assert(filter(data, criteria, 1) == vector<double>({3}));

  cout << "PASS!" << endl;
}

// Add the test function implementations here.
