#pragma once

#include <lib/scopedMap/scopedMap.hh>
#include <parser/nodes.hh>

class Binder : public DefaultVisitor {
  public: 
    using super_type = DefaultVisitor;
    using DefaultVisitor::operator();
    virtual void operator()(VarDec& e) override;
    virtual void operator()(SimpleVar& e) override;
    virtual void operator()(IfStmt& e) override;
  private:
    ScopedMap<std::string, VarDec*> map_;
};
