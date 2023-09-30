#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>
#include <string>

#include "cowbasic.h"

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
        }else{
            std::string a = tokens[i];
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
        switch(Tokens[cursor].type) {
            case WORD:
     
            if(((cursor+1) < Tokens.size()) && Tokens[cursor+1].type == EQUALS) {
                                       
                // equal situation
                Node N;
                N.type = DECLARATION;
                N.value = Tokens[cursor].value;
                
                // parse expression until "END"
                cursor+=2;
                // std::cout << Tokens[cursor+1].type << std::endl;
                std::vector<Token> exp;
                while(Tokens[cursor].type != END) {
                    // parse expression
                    exp.push_back(Tokens[cursor]);
                    cursor++;
                    if(cursor == Tokens.size() || Tokens[cursor].type == END) break;
                }
                std::cout << "here" << std::endl;
                // std::cout << "end" << std::endl;
                N.children = parse(exp);
                AST.push_back(N);
            }else if(Tokens[cursor].value == "RETURN") {
                // return <variable>
                Node N;
                N.type = STATEMENT;
                N.value = Tokens[cursor+1].value;
                AST.push_back(N);
            }else {
                // single expression, Non-Literal
                Node N;
                N.type = EXPRESSION;
                N.value = Tokens[cursor].value;
                AST.push_back(N);
            }
            break;
            case NUMBER: 
            if(((cursor+1) < Tokens.size()) && Tokens[cursor+1].type == MOO) {
                /*syntax:
                <iterations> MOO {
                    <statements>
                }*/
                Node N;
                N.type == LOOP;
                N.value = Tokens[cursor].value;
                cursor+=2;
                std::vector<Token> statements;
                int nestings = 1;
                while(nestings != 0) {
                    if(Tokens[cursor].type == O_BRACE) nestings++;
                    else if(Tokens[cursor].type == C_BRACE) nestings--;
                    statements.push_back(Tokens[cursor]);
                    cursor++;
                }
            }else {
                // single expression, Literal
                Node N;
                N.type = LITERAL;
                N.value = Tokens[cursor].value;
                AST.push_back(N);
            }
            break;
            case O_PAREN:
            // expressions can be nested. Addition is always in the form ( x ) + ( y ) + ...
            // parse expression until C_PAREN
            cursor++;
            std::vector<Token> exp;
            int nestings = 1;
            while(nestings != 0) {
                if(Tokens[cursor].type == O_PAREN) nestings++;
                else if(Tokens[cursor].type == C_PAREN) nestings--;
                exp.push_back(Tokens[cursor]);
                cursor++;
            }

            Node N;
            N.type = EXPRESSION;
            N.value = Tokens[cursor].value;
            N.children = parse(exp);
            AST.push_back(N);
            break;
        }
    }
    return AST;
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

int main() {
    std::string program;

    std::fstream file;
    file.open("cowbasic.in", std::ios::in);

    // empty contents of file into string (multiline)
    std::string line;
    while(std::getline(file, line)) {
        program += line + " \n";
    }


    std::vector<Token> Tokens = lex(program);
    // output tokens
    for(int i = 0; i<Tokens.size(); i++) {
        std::cout << Tokens[i].type << " ";
    }
    std::vector<Node> AST = parse(Tokens);

    // std::cout << AST.size() << std::endl;

    // file.close();
    // file.open("cowbasic.out", std::ios::out);
    // file << JSONIFY(AST);
    // file.close();
    // return 0;
}