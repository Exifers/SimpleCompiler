#include <lexer/lexer.hh>

#include <iostream>

int main(void) {
  Lexer lexer;
  lexer.addToken("(", "LPAR");
  lexer.addToken(")", "RPAR");
  lexer.addToken("[0-9][0-9]*", "INT");
  lexer.addToken("if", "IF");
  lexer.addToken("else", "ESLE");
  lexer.addToken("{", "LCBRA");
  lexer.addToken("}", "RCBRA");
  lexer.addToken("print", "PRINT");
  lexer.addToken("\".*\"", "STRING");
  lexer.addToken("+", "PLUS");
  lexer.addToken("==", "DEQUAL");

  auto v = lexer.scan("( ( ) ) 91 ( \"abc\" if else { }");
  for(auto it = v.begin(); it != v.end(); it++) {
    std::cout << it->name_get() << std::endl;
  } 
  return 0;
}
