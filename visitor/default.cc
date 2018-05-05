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
  e = e;
}

void
DefaultVisitor::operator()(ExprNode& e) {
  e = e;
}

void
DefaultVisitor::operator()(VarDec& e) {
  e = e;
}

void
DefaultVisitor::operator()(IfStmt& e) {
  (*e.cond_get()).accept(*this); 
  (*e.prog_get()).accept(*this);
  if (e.elseProg_get() != nullptr) {
    (*e.elseProg_get()).accept(*this);
  }
}

void
DefaultVisitor::operator()(PrintStmt& e) {
  e = e;
}

void
DefaultVisitor::operator()(AddExpr& e) { 
  (*e.lhs_get()).accept(*this);
  (*e.rhs_get()).accept(*this);
}

void
DefaultVisitor::operator()(EqualExpr& e) {
  (*e.lhs_get()).accept(*this);
  (*e.rhs_get()).accept(*this);
}

void
DefaultVisitor::operator()(IntNode& e) {
  e = e;
}

void
DefaultVisitor::operator()(SimpleVar& e) {
  e = e;
}

void
DefaultVisitor::operator()(Test& e) {
  e = e;
}

void
DefaultVisitor::operator()(Label& e) {
  e = e;
}

void
DefaultVisitor::operator()(BasicBlock& e) {
  e = e;
}

void
DefaultVisitor::operator()(Jump& e) {
  e = e;
}

void
DefaultVisitor::operator()(CJump& e) {
  e = e;
}
