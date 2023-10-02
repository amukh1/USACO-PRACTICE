#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>
#include <string>

enum TType {
    WORD,
    NUMBER,
    PLUS,
    EQUALS,
    O_BRACE,
    C_BRACE,
    O_PAREN,
    C_PAREN,
    MOO,
    END
};

enum Type {
    DECLARATION,
    LITERAL,
    EXPRESSION,
    STATEMENT,
    LOOP
};

struct Token {
    TType type;
    std::string value;
};

struct Node {
    Type type;
    std::string value;
    std::vector<Node> children;
};

struct Interpreter {
    std::map<std::string, int> variables;
};