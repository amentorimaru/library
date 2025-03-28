#pragma once

#include <chrono>
using namespace std;

namespace amentorimaru{
namespace other{
struct Timer {
  chrono::system_clock::time_point start;

  Timer() { reset(); }
  void reset() { 
    start = chrono::system_clock::now(); 
  }

  long long elapsed() {
    auto end = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
  }
  long long operator()() { return elapsed(); }
};
} // end of other
} // end of amentorimaru