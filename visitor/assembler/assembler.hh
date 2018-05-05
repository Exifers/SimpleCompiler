#include <parser/nodes.hh>

#include <vector>
#include <utility>

class Assembler : public DefaultVisitor {
  public:
    using DefaultVisitor::operator();
    virtual void operator()(ProgNode& e) override;
    virtual void operator()(EqualExpr& e) override;
    virtual void operator()(IntNode& e) override;
    virtual void operator()(SimpleVar& e) override;
    virtual void operator()(AddExpr& e) override;
  private:
    std::vector<StmtNode*> *toFill_;
    int fillIndex_;
    std::vector<std::pair<VarDec*, VarDec*>> varStack_;
};
