#pragma once

#include <vector>
#include <string>

class TokenInfo {
  public:
    TokenInfo(std::string name, std::string pattern);
    std::string name_get();
    std::string pattern_get();
  protected:
    std::string name_; 
    std::string pattern_;
};

class Token {
  public:
    Token(std::string name, std::string value);
    std::string name_get() const;
  protected:
    std::string name_;
    std::string value_;
};

/** General lexer */
class Lexer {
  public:
    void addToken(std::string pattern, std::string name);
    void setBlank(std::string pattern);
    std::vector<Token> scan(std::string input, bool debug = false);
  private: 
    std::vector<TokenInfo> tokensLibrary_;
    std::string blanks_ = " \n\r\t";
    Token getToken(const char *value);
};
