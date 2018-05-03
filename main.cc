#include <lexer/lexer.hh>

#include <iostream>

int main(void) {
  Lexer lexer;
  lexer.addToken("(", "LPAR");
  lexer.addToken(")", "RPAR");
  lexer.addToken("[0-9][0-9]*", "INT");
  auto v = lexer.scan("( ( ) ) 98a");
  for(auto it = v.begin(); it != v.end(); it++) {
    std::cout << it->name_get() << std::endl;
  } 
  return 0;
}
