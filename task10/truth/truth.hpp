#ifndef TRUTH_H_INCLUDED
#define TRUTH_H_INCLUDED


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <stdexcept>

using namespace std;


enum TokenType
{
    VAR,
    AND_OP,
    OR_OP,
    NOT_OP,
    LPAREN,
    RPAREN
};

struct Token
{
    TokenType type;
    char var;
};


void fail();
bool is_operator(TokenType t);
int precedence(TokenType t);
bool right_associative(TokenType t);
vector<Token> tokenize(const string& s);
void validate_tokens(const vector<Token>& tokens);
vector<char> find_l_vars(const vector<Token>& tokens);
vector<Token> to_postfix(const vector<Token>& tokens);
bool get_value(char var, const vector<char>& vars, int mask);
bool eval_postfix(const vector<Token>& postfix, const vector<char>& vars, int mask);
void print_header(const vector<char>& vars);
void print_table(const vector<Token>& postfix, const vector<char>& vars);



#endif