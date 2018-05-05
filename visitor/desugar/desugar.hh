#pragma once

#include <visitor/default.hh>

class Desugar : public DefaultVisitor {
  public:
    using DefaultVisitor::operator();
    void operator()(ProgNode& e) override;
};
