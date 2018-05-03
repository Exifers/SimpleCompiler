#include "lexer.hh"

#include <fnmatch.h>
#include <cstring>
#include <iostream>

TokenInfo::TokenInfo(std::string name, std::string pattern)
  : name_(name), pattern_(pattern)
{}

std::string
TokenInfo::name_get() {
  return name_;
}

std::string
TokenInfo::pattern_get() {
  return pattern_;
}

Token::Token(std::string name, std::string value)
  : name_(name), value_(value)
{}

std::string
Token::name_get() const {
  return name_;
}

void
Lexer::addToken(std::string pattern, std::string name) {
  TokenInfo tokenInfo = TokenInfo(name, pattern);
  tokensLibrary_.push_back(tokenInfo);
}

std::vector<Token>
Lexer::scan(std::string input, bool debug) {
  std::vector<Token> res;
  char *value = std::strtok((char *) input.c_str(), (char *) blanks_.c_str()); 
  while (value != nullptr) {
    if (debug) { std::cerr << "Scanning : " << value << std::endl; }
    res.push_back(getToken(value));
    value = std::strtok(nullptr, (char *) blanks_.c_str());
  }
  return res;
}

Token
Lexer::getToken(const char *value) {
  for (auto it = tokensLibrary_.begin(); it != tokensLibrary_.end(); it++) {
    if (regexmatch(it->pattern_get().c_str(), value)) {
      return Token(it->name_get(), std::string(value));
    }
  }
  std::cerr << value << " doesn't match any token" << std::endl;
  exit(1);
}
