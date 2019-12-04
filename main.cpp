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
#define ECHO_FLOAT(precision, str) (ss << fixed << setprecision(precision) << (str) << endl)
#define FLUSH() ss.clear();
#else
#define ECHO(str) (cout << (str) << endl)
#define ECHO_FLOAT(precision, str) (cout <<  fixed << setprecision(precision) << (str) << endl)
#endif

class item {
public:
  item(uint16_t v, uint16_t w) : weight(w), value(v) {
    r = (float)value/(float)weight;
  }

  float R() const {
    return r;
  }

  uint16_t W() const {
    return weight;
  }

  uint16_t V() const {
    return value;
  }

private:
  uint16_t weight;
  uint16_t value;
  float r;
};

bool operator<(const item& i1, const item& i2) {
  return i1.R() < i2.R();
}

ostream& operator<<(ostream& stream, const item& i) {
  return stream << "V: " << i.V() << "; W: " << i.W() << "; R: " << i.R();
}

void max_value(vector<string> commands) {
  uint16_t n;
  uint32_t W;
  { 
    stringstream command_stream(commands[0]);
    command_stream >> n >> W;
  }

  priority_queue<item> items;
  for (auto i = 0; i < n; i++) {
    uint16_t w, v;
    stringstream command_stream(commands[i+1]);
    command_stream >> v >> w;
    items.push({v, w});
  }
  auto value = 0.0f;

  while (!items.empty()) {
    const auto& el = items.top();
    // cout << "Making use of item " << el << endl;
    if (W == 0) {
      // cout << "W = 0, leaving" << endl;
      break;
    }
    const auto available_weight = el.W() < W ? el.W() : W;
    // cout << "Free space: " << available_weight << endl;
    value += available_weight * el.R();
    W -= available_weight;
    items.pop();
  }
  ECHO_FLOAT(4, value);
}

#ifdef TEST
bool compare(vector<string> output) {
  for (const auto &item : output) {
    string str;
    if (ss.eof()) {
      cout << "ss ended";
      return false;
    }
    getline(ss, str);
    if (str != item) {
      cout << str << " != " << item << endl;
      return false;
    } else {
      cout << "[" << str << "] == [" << item << "]" << endl;
    }
  }
  return true;
}


bool test1() {
  max_value({"3 50", "60 20", "100 50", "120 30"});
  return compare({"180.0000"});
}

bool test2() {
  max_value({"1 10", "500 30"});
  return compare({"166.6667"});
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
  vector<string> commands;
  string command;
  while (getline(cin, command)) {
    commands.push_back(command);
  }

  max_value(commands);

  return 0;
#endif
}