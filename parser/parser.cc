#include <iostream>

#include <lexer/lexer.hh>

#include "parser.hh"

ProgNode *
Parser::parse(bool debug) {
  debug_ = debug;
  return parseProgNode();
}

void
Parser::tokens_set(std::vector<Token> tokens) {
  tokens_ = tokens;
}

std::experimental::optional<Token>
Parser::peek() const {
  if ((int) tokens_.size() == tokenIndex_)
    return std::experimental::nullopt;
  return std::experimental::optional<Token>(tokens_[tokenIndex_]);
}

std::experimental::optional<Token>
Parser::eat() {
  if ((int) tokens_.size() == tokenIndex_)
    return std::experimental::nullopt;
  if (debug_) {
    std::cout << "Eating : " << tokens_[tokenIndex_].name_get() << std::endl;
  }
  return tokens_[tokenIndex_++];
}

ProgNode *
Parser::parseProgNode() {
  ProgNode *res = new ProgNode();
  while (peek()
      &&(peek()->name_get() == "VAR"
      || peek()->name_get() == "IF"
      || peek()->name_get() == "PRINT")) {
    res->push(parseStmtNode());
  }
  return res;
}

StmtNode *
Parser::parseStmtNode() {
  if (peek()->name_get() == "VAR") {
    eat();  
    auto id = eat(); 
    eat();
    auto num = eat();
    auto res = new VarDec(id->value_get(), num->value_get());
    return res;
  }
  else if (peek()->name_get() == "IF") {
    eat(); 
    eat();
    auto cond = parseExprNode();
    eat();
    eat();
    auto prog = parseProgNode();
    eat(); 
    IfStmt *res = new IfStmt(cond, prog);
    if (peek()->name_get() == "ELSE") {
      eat();
      eat();
      auto elseProg = parseProgNode();
      res->elseProg_set(elseProg);
      eat();
    }
    return res;
  }
  else if (peek()->name_get() == "PRINT") { 
    eat();
    auto str = eat();
    auto res = new PrintStmt(str->value_get());
    return res;
  }
  else {
    std::cerr << "Unknown token at the beginning of a statement : "
      << peek()->name_get() << std::endl; 
    std::exit(1);
  }
  return nullptr;
}

ExprNode *
Parser::parseExprNode() {
  auto numOrVar = eat();
  ExprNode *lhs;
  if (numOrVar->name_get() == "INT") {
    lhs = new IntNode(numOrVar->value_get());
  }
  else if (numOrVar->name_get() == "ID") {
    lhs = new SimpleVar(numOrVar->value_get());
  }
  else {
    std::cerr << "First member of expression is neither INT or ID" << std::endl;
    std::exit(1);
  }
  if (peek()->name_get() == "PLUS") {
    eat();
    auto exp = parseExprNode(); 
    auto res = new AddExpr(lhs, exp);
    return res;
  }
  if (peek()->name_get() == "DEQUAL") {
    eat(); 
    auto exp = parseExprNode();
    auto res = new EqualExpr(lhs, exp);
    return res;
  }
  return lhs;
}
