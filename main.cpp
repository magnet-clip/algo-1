#include <algorithm>
#include <climits>
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) { AssertEqual(b, true, hint); }

class TestRunner {
 public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (runtime_error& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

 private:
  int fail_count = 0;
};

struct Segment {
  int start, end;
};

bool operator<(const Segment& a, const Segment& b) { return a.start < b.start; }

vector<int> optimal_points(vector<Segment>& segments) {
  vector<int> points;

  sort(segments.begin(), segments.end());
  size_t i = 0;
  while (i < segments.size()) {
    auto containing_segment = segments[i];
    while (++i < segments.size()) {
      if (segments[i].start > containing_segment.end)
        break;  // this segment sticks completely out from containing one

      if (segments[i].start > containing_segment.start)
        containing_segment.start = segments[i].start;
      if (segments[i].end < containing_segment.end)
        containing_segment.end = segments[i].end;
    }
    points.push_back(containing_segment.end);
  }
  return points;
}

void TestNoSegments() {
  vector<Segment> empty;
  AssertEqual(optimal_points(empty).size(), 0, "0");
}

void TestOneSegment() {
  vector<Segment> one{{1, 2}};
  AssertEqual(optimal_points(one).size(), 1, "{1,2}");

  vector<Segment> two{{1, 1}};
  AssertEqual(optimal_points(two).size(), 1, "{1,1}");
}

void TestTwoSegments() {
  vector<Segment> a{{1, 2}, {1, 2}};
  AssertEqual(optimal_points(a).size(), 1, "Two equivalent segments");

  vector<Segment> b{{1, 2}, {3, 4}};
  AssertEqual(optimal_points(b).size(), 2, "Two non-overlapping segments");

  vector<Segment> c{{1, 3}, {2, 4}};
  AssertEqual(optimal_points(c).size(), 1, "Two overlapping segments");

  vector<Segment> d{{1, 3}, {3, 4}};
  AssertEqual(optimal_points(d).size(), 1,
              "Two segments overlapping in single point");

  vector<Segment> e{{2, 4}, {1, 3}};
  AssertEqual(optimal_points(e).size(), 1, "Two overlapping unsorted segments");
}

void TestThreeSegments() {
  vector<Segment> x;
  x = {{1, 6}, {1, 6}, {1, 6}};
  AssertEqual(optimal_points(x).size(), 1, "Three equal");

  x = {{1, 6}, {2, 5}, {3, 4}};
  AssertEqual(optimal_points(x).size(), 1, "Three one in another");

  x = {{2, 5}, {1, 6}, {3, 4}};
  AssertEqual(optimal_points(x).size(), 1, "Three one in another unsorted");

  x = {{2, 5}, {3, 7}, {4, 5}};
  AssertEqual(optimal_points(x).size(), 1,
              "Three segments, second sticks out and third in second");

  x = {{2, 4}, {3, 7}, {5, 6}};
  AssertEqual(
      optimal_points(x).size(), 2,
      "Three segments, second sticks out and third in second but out of first");
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestNoSegments, "No segments");
  runner.RunTest(TestOneSegment, "One segment");
  runner.RunTest(TestTwoSegments, "Two segments");
  runner.RunTest(TestThreeSegments, "Three segments");
}

int main() {
  // RunAllTests();

  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}