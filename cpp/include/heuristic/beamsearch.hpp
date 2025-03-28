#pragma once

#include <vector>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

namespace amentorimaru{

struct Beam{
  double score;
  long long hash() const {
    return 0LL;
  }
};

static bool operator < (const Beam& lhs, const Beam& rhs){
  return lhs.score < rhs.score || (lhs.score==rhs.score && lhs.hash() < rhs.hash());
}
static bool operator > (const Beam& lhs, const Beam& rhs){
  return lhs.score > rhs.score || (lhs.score==rhs.score && lhs.hash() > rhs.hash());
}


template <typename B>
struct BeamSearch{
  priority_queue<B,vector<B>,greater<B>> que;
  int beam_size = 0;

  bool run(){
    assert(que.size());
    assert(beam_size > 0);
    priority_queue<B,vector<B>,greater<B>> next_que;
    auto old_que = que;
    while(!old_que.empty()){
      auto v0 = old_que.top();
      old_que.pop();
      auto res = v0.search();
      for(auto& v:res){
        next_que.push(v);
        if(next_que.size() > beam_size)
          next_que.pop();
      }
    }
    if(next_que.empty())return false;
    que = next_que;
    return true;
  }
};

template <typename B>
struct HashedBeamSearch{
  multiset<B> beam_set;
  unordered_map<long long, B> hashed;
  int beam_size = 0;

  bool run(){
    assert(beam_set.size());
    assert(beam_size > 0);
    multiset<B> next_set;
    auto old_set = beam_set;
    for(auto& v0:old_set){
      auto res = v0.search();
      for(auto& v : res){
        auto h0 = v.hash();
        if(hashed.find(h0) == hashed.end()) {
          hashed[h0] = v;
          next_set.insert(v);
        } else if (hashed[h0] < v){
          next_set.erase(hashed[h0]);
          hashed[h0] = v;
          next_set.insert(v);
        }
        if(next_set.size() > beam_size){
          next_set.erase(next_set.begin());
        }
      }
    }
    if(next_set.empty())
      return false;
    beam_set = next_set;
    return true;
  }
};


} // end of namespace