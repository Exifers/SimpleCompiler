#include "desugar.hh"

#include <typeinfo>
#include <iostream>

#include <parser/nodes.hh>

void
Desugar::operator()(ProgNode& e) {
  auto& stmts = e.stmts_get();
  int initialSize = stmts.size();
  for (int i = 1; i <= initialSize; i++) {
    try {
      IfStmt* stmt = dynamic_cast<IfStmt*>(stmts[initialSize - i]);
      if (!stmt) {
        continue;
      }
      auto stmtSave = *stmt;
      stmts.erase(stmts.begin() + initialSize - i);
      
      Label *progLabel = new Label();
      Label *endLabel  = new Label();

      stmts.insert(stmts.begin() + initialSize - i, endLabel);
      stmtSave.prog_get()->accept(*this);
      stmts.insert(stmts.begin() + initialSize - i, new BasicBlock(stmtSave.prog_get()));
      stmts.insert(stmts.begin() + initialSize - i, progLabel);
      stmts.insert(stmts.begin() + initialSize - i, new Jump(endLabel));
      if (stmtSave.elseProg_get()) {
        stmtSave.elseProg_get()->accept(*this);
        stmts.insert(stmts.begin() + initialSize - i, new BasicBlock(stmtSave.elseProg_get()));
      }
      stmts.insert(stmts.begin() + initialSize - i, new CJump(progLabel));
      stmts.insert(stmts.begin() + initialSize - i, new Test(stmtSave.cond_get())); 
    }
    catch (const std::bad_cast& e) {
      continue;
    }
  }
}
