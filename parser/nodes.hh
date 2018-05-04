#pragma once

#include "fwd.hh"

#include <visitor/default.hh>

#include <vector>
#include <string>

class ProgNode {
  public:
    void push(StmtNode *stmtnode) { stmts_.push_back(stmtnode); }
    std::vector<StmtNode*>& stmts_get() { return stmts_; }
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
    std::vector<StmtNode*> stmts_;
};

class StmtNode {
  public:
    virtual ~StmtNode() = 0;
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
};

class VarDec : public StmtNode {
  public:
    VarDec(std::string id, std::string num)
      : id_(id), num_(num)
    {}
    virtual void accept(DefaultVisitor& v) { v(*this); }
    std::string id_get() { return id_; }
    std::string num_get() { return num_; }
  private:
    std::string id_;
    std::string num_;
};

class IfStmt : public StmtNode {
  public:
    IfStmt (ExprNode *cond, ProgNode *prog)
      : cond_(cond), prog_(prog), elseProg_(nullptr)
    {}
    void elseProg_set(ProgNode *elseProg) { elseProg_ = elseProg; }
    ExprNode *cond_get() const { return cond_; }
    ProgNode *prog_get() const { return prog_; }
    ProgNode *elseProg_get() const { return elseProg_; }
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
    ExprNode *cond_; 
    ProgNode *prog_;
    ProgNode *elseProg_;
};

class PrintStmt : public StmtNode {
  public:
    PrintStmt(std::string str)
      : str_(str)
    {}
    virtual void accept(DefaultVisitor& v) { v(*this); }
    std::string str_get() { return str_; }
  private:
    std::string str_;
};

class ExprNode {
  public:
    virtual ~ExprNode() = 0;
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
};

class AddExpr : public ExprNode {
  public:
    AddExpr(ExprNode *lhs, ExprNode *rhs)
      : lhs_(lhs), rhs_(rhs) 
    {}
    ExprNode *lhs_get() const { return lhs_; }
    ExprNode *rhs_get() const { return rhs_; }
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
    ExprNode *lhs_;
    ExprNode *rhs_;
};

class EqualExpr : public ExprNode {
  public:
    EqualExpr(ExprNode *lhs, ExprNode *rhs)
      : lhs_(lhs), rhs_(rhs) 
    {}
    ExprNode *lhs_get() const { return lhs_; }
    ExprNode *rhs_get() const { return rhs_; }
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
    ExprNode *lhs_;
    ExprNode *rhs_;
};

class IntNode : public ExprNode {
  public:
    IntNode(std::string integer)
      : integer_(integer)
    {}
    virtual void accept(DefaultVisitor& v) { v(*this); }
    std::string integer_get() { return integer_; }
  private:
    std::string integer_;
};

class SimpleVar : public ExprNode {
  public:
    SimpleVar(std::string name)
      : name_(name)
    {}
    std::string name_get() { return name_; }
    void def_set(VarDec *def) { def_ = def; }
    virtual void accept(DefaultVisitor& v) { v(*this); }
  private:
    std::string name_;
    VarDec *def_ = nullptr;
};
