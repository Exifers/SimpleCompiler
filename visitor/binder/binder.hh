#pragma once

class Binder : public DefaultVisitor {
  public: 
    virtual void operator()(VarDec& e);
    virtual void operator()(SimpleVar& e);
};
