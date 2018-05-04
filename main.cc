#include <lexer/lexer.hh>
#include <parser/parser.hh>
#include <visitor/printer/printer.hh>

#include <iostream>
#include <fstream>

std::string getSource(std::string filename) {
  std::ifstream src;
  src.open(filename);
  if (!src.is_open()) {
    std::cerr << "Cannot open file : " << filename << std::endl;
    std::exit(1);
  }
  std::string str;
  src.seekg(0, std::ios::end);
  str.reserve(src.tellg());
  src.seekg(0, std::ios::beg);
  str.assign((std::istreambuf_iterator<char>(src)),
             (std::istreambuf_iterator<char>()));
  return str;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage : ./main <file.al>" << std::endl;
    std::exit(1);
  }
  std::string src = getSource(argv[1]); 

  Lexer lexer;
  lexer.addToken("(" , "LPAR");
  lexer.addToken(")" , "RPAR");
  lexer.addToken("if", "IF");
  lexer.addToken("else", "ELSE");
  lexer.addToken("{", "LCBRA");
  lexer.addToken("}", "RCBRA");
  lexer.addToken("print", "PRINT");
  lexer.addToken("+", "PLUS");
  lexer.addToken("==", "DEQUAL");
  lexer.addToken("=", "EQUAL");
  lexer.addToken("var", "VAR");
  lexer.addToken("\".*\"", "STRING");
  lexer.addToken("[0-9][0-9]*", "INT");
  lexer.addToken("[a-zA-Z][a-zA-Z0-9_]*", "ID");

  auto v = lexer.scan(src);
  Parser p;
  p.tokens_set(v);
  auto tree = p.parse();
  Printer visitor = Printer();
  visitor(*tree);
  return 0;
}
