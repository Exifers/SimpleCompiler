#include <parser/nodes.hh>

class TypeChecker : public DefaultVisitor {
  public:
    using super_type = DefaultVisitor;
    using DefaultVisitor::operator();
    void operator()(AddExpr& e) override;
    void operator()(EqualExpr& e) override;
    void operator()(IntNode& e) override;
    void operator()(SimpleVar& e) override;
    void operator()(IfStmt& e) override;
};
