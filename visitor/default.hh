#pragma once

#include <parser/fwd.hh>

class DefaultVisitor {
  public:
    virtual void operator()(ProgNode& e);
    virtual void operator()(StmtNode& e);
    virtual void operator()(ExprNode& e);
    virtual void operator()(IfStmt& e);
    virtual void operator()(PrintStmt& e);
    virtual void operator()(AddExpr& e);
    virtual void operator()(EqualExpr& e);
    virtual void operator()(IntNode& e);
    virtual void operator()(VarDec& e);
    virtual void operator()(SimpleVar& e);
    virtual void operator()(Test& e);
    virtual void operator()(Label& e);
    virtual void operator()(BasicBlock& e);
    virtual void operator()(Jump& e);
    virtual void operator()(CJump& e);
    virtual void operator()(Add& e);
    virtual void operator()(Compare& e);
};
