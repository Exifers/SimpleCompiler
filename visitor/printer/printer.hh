#pragma once

#include <visitor/default.hh>

class Printer : public DefaultVisitor {
  public:
    using super_type = DefaultVisitor;
    using super_type::operator();
    virtual void operator()(IfStmt& e) override;
    virtual void operator()(PrintStmt& e) override;
    virtual void operator()(AddExpr& e) override;
    virtual void operator()(EqualExpr& e) override;
    virtual void operator()(IntNode& e) override;
    virtual void operator()(VarDec& e) override;
    virtual void operator()(SimpleVar& e) override;
  private:
};
