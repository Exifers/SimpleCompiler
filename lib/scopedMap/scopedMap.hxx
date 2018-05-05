#include <iostream>

template <typename T, typename U>
ScopedMap<T, U>::ScopedMap() {
  stack_ = std::vector<std::map<T, U>>();
}

template <typename T, typename U>
void
ScopedMap<T, U>::add(T key, U value) {
  if (stack_.size() == 0) {
    stack_.push_back(std::map<T,U>());
  }
  stack_.back()[key] = value; 
}

template <typename T, typename U>
std::experimental::optional<U>
ScopedMap<T, U>::get(T key) {
  if (stack_.size() == 0) {
    return std::experimental::nullopt;
  }
  if (stack_.back().find(key) != stack_.back().end()) {
    return std::experimental::optional<U>(stack_.back()[key]);
  }
  return std::experimental::nullopt;
}

template <typename T, typename U>
bool
ScopedMap<T, U>::has(T key) {
  if (stack_.size() == 0) {
    return false;
  }
  if (stack_.size() == 1) {
    return stack_.back().find(key) != stack_.back().end();
  }
  if (stack_.back().find(key) == stack_.back().end()) {
    return false;
  }
  else {
    return stack_[stack_.size() - 2].find(key) == stack_[stack_.size() - 2].end();
  }
}

template <typename T, typename U>
void
ScopedMap<T, U>::push() {
  if (stack_.size() == 0) {
    stack_.push_back(std::map<T, U>());
    return;
  }
  auto last = stack_.back();
  stack_.push_back(std::map<T, U>());
  for (auto it = last.begin(); it != last.end(); it++) {
    stack_.back()[it->first] = it->second;
  } 
}

template <typename T, typename U>
void
ScopedMap<T, U>::pop() {
  if (stack_.size() != 0) {
    stack_.pop_back();
  }
}

template <typename T, typename U>
void
ScopedMap<T, U>::dump() {
  for (auto it = stack_.begin(); it != stack_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      std::cout << "stack: " << it2->first << ":" << it2->second << std::endl; 
    }
    std::cout << "---" << std::endl;
  }
}
