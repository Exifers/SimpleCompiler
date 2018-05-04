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
    std::experimental::make_optional<U>(stack_.back()[key]);
  }
  return std::experimental::nullopt;
}

template <typename T, typename U>
void
ScopedMap<T, U>::push() {
  if (stack_.size() == 0) {
    stack_.push_back(std::map<T, U>());
    return;
  }
  auto& last = stack_.back();
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
