#include "types.hh"
#include "typeChecker.hh"

#include <iostream>

void
TypeChecker::operator()(IfStmt& e) {
  super_type::operator()(e);
  if (e.cond_get()->type_get() != BOOL) {
    std::cerr << "If statment must contain a boolean" << std::endl;  
    std::exit(1);
  }
}

void
TypeChecker::operator()(AddExpr& e) {
  e.lhs_get()->accept(*this);
  e.rhs_get()->accept(*this);
  if (e.lhs_get()->type_get() != INT
   || e.rhs_get()->type_get() != INT) {
    std::cerr << "Incorect type in add expression" << std::endl;
    std::exit(1);
  }
  e.type_set(INT); 
}

void
TypeChecker::operator()(EqualExpr& e) {
  e.lhs_get()->accept(*this);
  e.rhs_get()->accept(*this);
  if (e.lhs_get()->type_get() != e.rhs_get()->type_get()) {
    std::cerr << "== operand types mismatch" << std::endl;
    std::exit(1);
  }
  e.type_set(BOOL);
}

void
TypeChecker::operator()(IntNode& e) {
  e.type_set(INT);
}

void
TypeChecker::operator()(SimpleVar& e) {
  /* the langage handles only one type now, so ... */
  e.type_set(INT);
}
