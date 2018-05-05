#include "printer.hh"

#include <iostream>
#include <parser/nodes.hh>

void
Printer::operator()(IfStmt& e) {
  std::cout << "if (";
  (*e.cond_get()).accept(*this);
  std::cout << ") {\n";
  (*e.prog_get()).accept(*this);
  std::cout << "}\n";
  if (e.elseProg_get()) {
    std::cout << "else {\n";
    (*e.elseProg_get()).accept(*this);
    std::cout << "}";
  }
}

void
Printer::operator()(PrintStmt& e) {
  std::cout << "print " << e.str_get() << std::endl;
}

void
Printer::operator()(AddExpr& e) {
  (*e.lhs_get()).accept(*this);
  std::cout << " + "; 
  (*e.rhs_get()).accept(*this);
}

void
Printer::operator()(EqualExpr& e) {
  (*e.lhs_get()).accept(*this);
  std::cout << " == "; 
  (*e.rhs_get()).accept(*this);
}

void
Printer::operator()(IntNode& e) {
  std::cout << e.integer_get();
}

void
Printer::operator()(VarDec& e) {
  std::cout << "var " << e.id_get();
  if (showBindings_)
    std::cout << " /*" << &e << "*/";
  std::cout << " = " << e.num_get() << std::endl;
}

void
Printer::operator()(SimpleVar& e) {
  std::cout << e.name_get();
  if (showBindings_)
    std::cout << " /*" << e.def_get() << "*/";
  std::cout << std::endl;
}

void
Printer::operator()(Test& e) {
  std::cout << "Test<";
  (*e.cond_get()).accept(*this);
  std::cout << ">" << std::endl;
}

void
Printer::operator()(Label& e) {
  std::cout << "Label<" << e.uid_get() << ">" << std::endl;
}

void
Printer::operator()(BasicBlock& e) {
  (*e.prog_get()).accept(*this);
}

void
Printer::operator()(Jump& e) {
  std::cout << "Jump<" << e.label_get()->uid_get() << ">" << std::endl;
}

void
Printer::operator()(CJump& e) {
  std::cout << "CJump<" << e.label_get()->uid_get() << ">" << std::endl;
}
