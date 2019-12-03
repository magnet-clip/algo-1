#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

//#define TEST

#ifdef TEST
stringstream ss;
#define ECHO(str) (ss << (str) << endl)
#define FLUSH() ss.clear();
#else
#define ECHO(str) (cout << (str) << endl)
#endif

unsigned int _change(priority_queue<unsigned int>& coins, unsigned int amount) {
  unsigned int count = 0;
  while (!coins.empty() && amount > 0) {
    // cout << "Amount to change left: " << amount << " and current coin is " << coins.top() << endl;
    if (coins.top() <= amount) {
      amount -= coins.top();
      count++;
    } else {
      coins.pop();
    }
  }
    
  // cout << "Amount to change left: " << amount << " and number of coins spent is " << count << endl;

  if (amount == 0) {
    return count;
  } else {
    return 0;
  }
}

unsigned int change_count(const vector<unsigned int>& coins, unsigned int amount) {
  priority_queue<unsigned int> queue;
  for (const auto& coin: coins) {
    queue.push(coin);
  }
  return _change(queue, amount);
}

#ifdef TEST


bool test1() {
  vector<unsigned int> coins{1, 5, 10};
  return change_count(coins, 6) == 2;
}

bool test2() {
  vector<unsigned int> coins{1, 5, 10};
  return change_count(coins, 28) == 6;
}


#endif

int main() {
#ifdef TEST
  auto tests = {test1, test2};
  auto i = 0;
  bool failed = false;
  for (auto test : tests) {
    i++;
    if (!test()) {
      cout << "TEST " << i << " FAILED" << endl;
      failed = true;
    } else {
      cout << "TEST " << i << " OK" << endl;
    }
    FLUSH();
  }

  if (failed) {
    cout << "SOME TESTS FAILED" << endl;
  } else {
    cout << "ALL TESTS PASSED" << endl;
  }

  return 0;

#else
  vector<unsigned int> coins{1, 5, 10};
  unsigned int amount;
  cin >> amount;
  cout << change_count(coins, amount) << endl;
  return 0;
#endif
}