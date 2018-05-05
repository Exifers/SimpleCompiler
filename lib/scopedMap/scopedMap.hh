#pragma once

#include <vector>
#include <map>
#include <utility>
#include <experimental/optional>

template <typename T, typename U>
class ScopedMap {
  public:
    /** Constructor: initializes an empty map in a vector of length one. */
    ScopedMap();
    void add(T key, U value);
    std::experimental::optional<U> get(T key);
    bool has(T key);
    void push();
    void pop();
    void dump();
  private:
    std::vector<std::map<T,U>> stack_;
};

#include "scopedMap.hxx"
