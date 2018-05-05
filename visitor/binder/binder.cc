#include "binder.hh"

#include <iostream>

void
Binder::operator()(VarDec& e) {
  if (map_.has(e.id_get())) {
    std::cerr << "Redefinition of variable : " << e.id_get() << std::endl;
    std::exit(1);
  }
  map_.add(e.id_get(), &e);
}

void
Binder::operator()(SimpleVar& e) {
  auto def = map_.get(e.name_get());
  if (def) {
    e.def_set(*def);
  }
  else {
    std::cerr << "Undefined variable : " << e.name_get() << std::endl; 
    std::exit(1);
  }
}

void
Binder::operator()(IfStmt& e) {
  map_.push();
  e.cond_get()->accept(*this);
  e.prog_get()->accept(*this);
  map_.pop();
  if (e.elseProg_get()) {
    map_.push();
    e.elseProg_get()->accept(*this);
    map_.pop();
  }
}
