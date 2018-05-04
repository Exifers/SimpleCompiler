#include <experimental/optional>

#include <lexer/lexer.hh>

#include "nodes.hh"

class Parser {
  public:
    ProgNode *parse(bool debug = false);
    void tokens_set(std::vector<Token> tokens);
  private:
    ProgNode *parseProgNode();
    StmtNode *parseStmtNode();
    ExprNode *parseExprNode();

    std::vector<Token> tokens_;
    int tokenIndex_ = 0;
  
    std::experimental::optional<Token> peek() const;
    std::experimental::optional<Token> eat();

    bool debug_ = false;
};
