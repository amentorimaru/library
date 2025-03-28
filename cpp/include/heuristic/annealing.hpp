#pragma once

// 焼きなまし
#include "../other/timer.hpp"
#include "../random/random.hpp"
#include <math>

namespace amentorimaru{

template <typename F, typename S, typename R>
R BasicAnnealing(F f, int time_limit, double start_temp, double end_temp, S calc_score, R first) {
  assert(start_temp <= end_tmp);
  R res = first;
  R now = first;
  auto score = calc_score(first);
  auto now_score = score;
  other::Timer timer;
  while(1) {
    if(timer() > time_limit) {
      break;
    }
    double temp = start_temp + (end_temp - start_temp) * timer() / time_limit;
    auto next = f(now);
    auto next_score = calc_score(next);
    double diff = next_score - now_score;
    if(exp(diff/temp) > random::rnd()){
      if(score < next_score){
        score = next_score;
        res = next;
      }
      now_score = next_score;
      now = next;
    }
  }

  return res;
};

} // end of namespace