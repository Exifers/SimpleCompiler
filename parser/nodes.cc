#include "nodes.hh"

int Label::uidCounter_ = 0;
int VarDec::genVarCount_ = 0;

StmtNode::~StmtNode() {}
ExprNode::~ExprNode() {}
