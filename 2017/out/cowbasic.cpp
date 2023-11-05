#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>
#include <string>
#include <cctype>

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

/*  tokens:
Literals: string && number
PLUS: +
EQUALS: =
O-BRACE: {
C-BRACE: }
O-PAREN: (
C-PAREN: )
MOO: MOO // loop

    Syntax:
Statements: "RETURN <expression>", "<identifier> = <expression>", "<literal> MOO { <statements> }"
Expression: <literal>, <identifier>, ( <expression> + <expression> )
*/

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// std::string getNextToken(std::string superString, std::string substr) {

// }

std::vector<std::string> split(std::string superString, char delim) {
    std::vector<std::string> tokens;
    std::string temp = "";
    for(int i = 0; i<superString.length(); i++) {
        if(superString[i] == delim) {
            tokens.push_back(temp);
            temp = "";
        }else temp+=superString[i];
    }
    tokens.push_back(temp);
    return tokens;
}

std::vector<Token> lex(std::string program) {
    std::vector<std::string> tokens = split(program, ' ');
    std::vector<Token> Tokens;
    for(int i = 0; i<tokens.size(); i++) {
        if(tokens[i] == "=") {
            Token T;
            T.type = EQUALS;
            T.value = "=";
            Tokens.push_back(T);
        }else if(tokens[i] == "+") {
            Token T;
            T.type = PLUS;
            T.value = "+";
            Tokens.push_back(T);
        }else if(tokens[i] == "(") {
            Token T;
            T.type = O_PAREN;
            T.value = "(";
            Tokens.push_back(T);
        }else if(tokens[i] == ")") {
            Token T;
            T.type = C_PAREN;
            T.value = ")";
            Tokens.push_back(T);
        }else if(tokens[i] == "{") {
            Token T;
            T.type = O_BRACE;
            T.value = "{";
            Tokens.push_back(T);
        }else if(tokens[i] == "}") {
            Token T;
            T.type = C_BRACE;
            T.value = "}";
            Tokens.push_back(T);
        }else if(tokens[i] == "MOO") {
            Token T;
            T.type = MOO;
            T.value = "MOO";
            Tokens.push_back(T);
        }else if(tokens[i] == "\n") {
            Token T;
            T.type = END;
            T.value = "\n";
            Tokens.push_back(T);
        }else if(is_number(tokens[i])){
            Token T;
            T.type = NUMBER;
            T.value = tokens[i];
            Tokens.push_back(T);
        }else if(tokens[i] != ""){
            // std::cout << a.length() << std::endl;
            // std::cout << is_number(a) << std::endl;
            Token T;
            T.type = WORD;
            T.value = tokens[i];
            Tokens.push_back(T);
        }
    }
    return Tokens;
}

std::vector<Node> parse(std::vector<Token> Tokens) {
    std::vector<Node> AST;
    int cursor = 0;
    while(cursor != Tokens.size()) {
        // std::cout << cursor << std::endl;
        // std::cout << Tokens[cursor].type << std::endl;
        if(Tokens[cursor].type == WORD) {

            if(((cursor+1) < Tokens.size()) && Tokens[cursor+1].type == EQUALS) {
                                       
                // equal situation
                Node N;
                N.type = DECLARATION;
                N.value = Tokens[cursor].value;
                
                // parse expression until "END"
                cursor+=2;
                // std::cout << Tokens[cursor+1].type << std::endl;
                std::vector<Token> exp;
                                // std::cout << "here" << std::endl;
                while(Tokens[cursor].type != END) {
                    // parse expression
                    exp.push_back(Tokens[cursor]);
                    cursor++;
                    if(cursor == Tokens.size() || Tokens[cursor].type == END) break;
                }
                // std::cout << "here" << std::endl;
                // std::cout << "end" << std::endl;
                Node N2;
                N2.type = EXPRESSION;
                N2.value = ")";
                N2.children = parse(exp);
                // N.children = parse(exp);
                N.children = {N2};
                // Node N2;
                // N2.type = EXPRESSION;
                // N2.value = Tokens[cursor].value;
                // N2.children = N.children;
                // N.children = {N2};
                AST.push_back(N);
            }else if(Tokens[cursor].value == "RETURN") {
                                                                // std::cout << "IM STUCK IN HERE IM STUCK IN HERE" << std::endl;
                // return <variable>
                Node N;
                N.type = STATEMENT;
                N.value = Tokens[cursor+1].value;
                AST.push_back(N);
                cursor+=2;
            }else {
                // single expression, Non-Literal
                Node N;
                N.type = EXPRESSION;
                N.value = Tokens[cursor].value;
                AST.push_back(N);
                cursor++;
            }
            // break;
            }else if(Tokens[cursor].type == NUMBER) {
                // std::cout << "here" << std::endl;
            if(((cursor+1) < Tokens.size()) && Tokens[cursor+1].type == MOO) {
                // std::cout << "here" << std::endl;
                // std::cout << AST.size() << std::endl;

                /*syntax:
                <iterations> MOO {
                    <statements>
                }*/
                Node N;
                N.type = LOOP;
                N.value = Tokens[cursor].value;
                cursor+=3;
                std::vector<Token> statements;
                int nestings = 1;
                while(nestings != 0) {
                    if(Tokens[cursor].type == O_BRACE) nestings++;
                    else if(Tokens[cursor].type == C_BRACE) nestings--;
                    if(nestings == 0) break;
                    statements.push_back(Tokens[cursor]);
                    cursor++;
                }
                // std::cout << statements.size() << std::endl;
                cursor++;
                N.children = parse(statements);
                AST.push_back(N);
            }else {
                // std::cout << "here" << std::endl;
                // single expression, Literal
                Node N;
                N.type = LITERAL;
                N.value = Tokens[cursor].value;
                AST.push_back(N);
                cursor++;
            }
            // break;
            }else if(Tokens[cursor].type == O_PAREN) {
            // expressions can be nested. Addition is always in the form ( x ) + ( y ) + ...
            // parse expression until C_PAREN
            cursor++;
            std::vector<Token> exp;
            int nestings = 1;
            while(nestings != 0) {
                if(Tokens[cursor].type == O_PAREN) nestings++;
                else if(Tokens[cursor].type == C_PAREN) nestings--;
                if(nestings == 0) break;
                exp.push_back(Tokens[cursor]);
                cursor++;
            }
            Node N;
            N.type = EXPRESSION;
            N.value = Tokens[cursor].value;
            N.children = parse(exp);
            AST.push_back(N);
            cursor++;
            // break;
            }else if(Tokens[cursor].type == PLUS) {
            // addition
            Node N;
            N.type = EXPRESSION;
            N.value = Tokens[cursor].value;
            AST.push_back(N);
            cursor++;
            }else if(Tokens[cursor].type != END) {
                std::cout << "error" << std::endl;
                std::cout << Tokens[cursor].type << std::endl;
                cursor++;
            }else cursor++;
        }
        return AST; // 🐶🐶🐶
    }   

std::string JSONIFY(std::vector<Node> AST) {
    std::string json = "[";
    for(int i = 0; i<AST.size(); i++) {
        json += "{";
        json += "\"type\":";
        switch(AST[i].type) {
            case DECLARATION:
            json += "\"declaration\",";
            break;
            case LITERAL:
            json += "\"literal\",";
            break;
            case EXPRESSION:
            json += "\"expression\",";
            break;
            case STATEMENT:
            json += "\"statement\",";
            break;
            case LOOP:
            json += "\"loop\",";
            break;
        }
        json += "\"value\":\"" + AST[i].value + "\"";
        if(AST[i].children.size() > 0) {
            json += ",\"children\":" + JSONIFY(AST[i].children);
        }
        json += "}";
        if(i != AST.size() - 1) json += ",";
    }
    json += "]";
    return json;
}

int interpret(Interpreter* I, std::vector<Node> AST) {
    for(int i = 0; i<AST.size(); i++) {
        switch(AST[i].type) {
            case DECLARATION:
            I->variables[AST[i].value] = interpret(I, AST[i].children);
            break;
            case LITERAL:
            return std::stoi(AST[i].value);
            break;
            case EXPRESSION:
            // if expression is single, return the value at that variable
            if(AST[i].children.size() == 0) return I->variables[AST[i].value];
            else if(AST[i].children.size() == 1) return interpret(I, AST[i].children);
            else {
                // addition
                int sum = 0;
                for(int j = 0; j<AST[i].children.size(); j++) {
                    sum += interpret(I, AST[i].children[j].children);
                }
                return sum;
            }
            break;
            case STATEMENT:
            return I->variables[AST[i].value];
            break;
            case LOOP:
            for(int j = 0; j<std::stoi(AST[i].value); j++) {
                interpret(I, AST[i].children);
            }
            break;
        }
    }
    return 0;
}

int main() {
    std::string program;

    std::fstream file;
    file.open("cowbasic.in", std::ios::in);

    // empty contents of file into string (multiline)
    std::string line;
    while(std::getline(file, line)) {
        program += " " + line + " \n";
    }
    file.close();

    std::vector<Token> Tokens = lex(program);
    // output tokens
    // for(int i = 0; i<Tokens.size(); i++) {
    //     std::cout << Tokens[i].type << " ";
    // }
    std::vector<Node> AST = parse(Tokens);

    // std::cout << std::endl;
    // std::cout << AST.size() << std::endl;

    // log ast TYPES
    // for(int i = 0; i<AST.size(); i++) {
    //     std::cout << AST[i].type << std::endl;
    // }
    file.open("cowbasic.out", std::ios::out);
    // file << JSONIFY(AST);
    // file.close();

    // interpreting
    Interpreter I;

    // std::cout << interpret(&I, AST) << std::endl;
    file << interpret(&I, AST);
    file.close();

    return 0;
}