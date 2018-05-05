#include "assembler.hh"

#include <typeinfo>

void
Assembler::operator()(ProgNode& e) { 
  auto& stmts = e.stmts_get();
  int initialSize = stmts.size();
  for (int i = 1; i <= initialSize; i++) {
    try {
      Test *test = dynamic_cast<Test*>(stmts[initialSize - i]);
      if (!test) {
        try {
          BasicBlock *block = dynamic_cast<BasicBlock*>(stmts[initialSize - i]);
          if (!block)
            continue;
          block->prog_get()->accept(*this);
        }
        catch(const std::bad_cast& e) {
          continue;
        }
        continue;
      }
      toFill_ = &stmts;
      fillIndex_ = initialSize - i + 1; /* test is not moving */
      test->cond_get()->accept(*this);
      stmts.erase(stmts.begin() + initialSize - i);
    }
    catch (const std::bad_cast& e) {
      continue;
    } 
  } 
}

void
Assembler::operator()(EqualExpr& e) {
  /* Results of the computations : */
  auto res1 = new VarDec();
  auto res2 = new VarDec();
  auto pair = std::pair<VarDec*, VarDec*>(res1, res2);
  varStack_.push_back(pair);
  toFill_->insert(toFill_->begin() + fillIndex_++, res1);
  toFill_->insert(toFill_->begin() + fillIndex_++, res2);

  e.lhs_get()->accept(*this);
  e.rhs_get()->accept(*this);

  varStack_.pop_back();

  /* Compare node : */
  toFill_->insert(toFill_->begin() + fillIndex_++,
    new Compare(res1->id_get(), res2->id_get())); 
}

void
Assembler::operator()(AddExpr& e) {
  /* Results of the computations : */
  auto res1 = new VarDec();
  auto res2 = new VarDec();
  auto pair = std::pair<VarDec*, VarDec*>(res1, res2);
  varStack_.push_back(pair);
  toFill_->insert(toFill_->begin() + fillIndex_++, res1);
  toFill_->insert(toFill_->begin() + fillIndex_++, res2);

  /* Calculation done here : */
  e.lhs_get()->accept(*this);
  e.rhs_get()->accept(*this);

  varStack_.pop_back();
  auto& ourRes = varStack_.back();
  VarDec *container = ourRes.first->num_get() == "" ? ourRes.first : ourRes.second;

  toFill_->insert(toFill_->begin() + fillIndex_++,
    new Add(container->id_get(), res1->id_get()));
  toFill_->insert(toFill_->begin() + fillIndex_++,
    new Add(container->id_get(), res2->id_get()));

  container->num_set("0");
}

void
Assembler::operator()(IntNode& e) {
  auto container = varStack_.back().first->num_get() == "" ?
    varStack_.back().first : varStack_.back().second;
  container->num_set(e.integer_get());
}

void
Assembler::operator()(SimpleVar& e) { 
  auto container = varStack_.back().first->num_get() == "" ?
    varStack_.back().first : varStack_.back().second;
  container->num_set(e.def_get()->num_get());
}
