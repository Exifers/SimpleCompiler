#include "default.hh"

#include <parser/nodes.hh>

#include <iostream>

void
DefaultVisitor::operator()(ProgNode& e) {
  auto stmts = e.stmts_get();
  for (auto it = stmts.begin(); it != stmts.end(); it++) {
    (**it).accept(*this);
  }
}

void
DefaultVisitor::operator()(StmtNode& e) {
  std::cout << "stmt" << std::endl;
  e = e;
}

void
DefaultVisitor::operator()(ExprNode& e) {
  std::cout << "expr" << std::endl;
  e = e;
}

void
DefaultVisitor::operator()(VarDec& e) {
  std::cout << "VarDec" << std::endl;
  e = e;
}

void
DefaultVisitor::operator()(IfStmt& e) {
  std::cout << "IfNode" << std::endl;
  (*e.cond_get()).accept(*this); 
  (*e.prog_get()).accept(*this);
  if (e.elseProg_get() != nullptr) {
    (*e.elseProg_get()).accept(*this);
  }
}

void
DefaultVisitor::operator()(PrintStmt& e) {
  std::cout << "PrintStmt" << std::endl;
  e = e;
}

void
DefaultVisitor::operator()(AddExpr& e) { 
  std::cout << "AddExpr" << std::endl;
  (*e.lhs_get()).accept(*this);
  (*e.rhs_get()).accept(*this);
}

void
DefaultVisitor::operator()(EqualExpr& e) {
  std::cout << "EqualExpr" << std::endl;
  (*e.lhs_get()).accept(*this);
  (*e.rhs_get()).accept(*this);
}

void
DefaultVisitor::operator()(IntNode& e) {
  std::cout << "IntNode" << std::endl;
  e = e;
}

void
DefaultVisitor::operator()(SimpleVar& e) {
  std::cout << "SimpleVar" << std::endl;
  e = e;
}
