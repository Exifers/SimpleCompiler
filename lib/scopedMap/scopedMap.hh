#pragma once

#include <vector>
#include <map>
#include <utility>
#include <experimental/optional>

template <typename T, typename U>
class ScopedMap {
  public:
    void add(T key, U value);
    std::experimental::optional<U> get(T key);
    void push();
    void pop();
  private:
    std::vector<std::map<T,U>> stack_;
};

#include "scopedMap.hxx"
