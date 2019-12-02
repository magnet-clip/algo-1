#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

#define TEST

#ifdef TEST
stringstream ss;
#define ECHO(str) (ss << (str) << endl)
#define FLUSH() ss.clear();
#else
#define ECHO(str) (cout << (str) << endl)
#endif


unsigned int change_count(const vector<unsigned int>& coins, unsigned int amount) {
  // TODO greedy change
}

#ifdef TEST


bool test1() {
  vector<unsigned int> coins{1, 5, 10};
  return change_count(coins, 2) == 2;
}

#endif

int main() {
#ifdef TEST
  auto tests = {test1};
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
 

  return 0;
#endif
}