#include "main.hpp"


#define MAX_LENGTH 2048
#define MAX_TOKENS 2048
#define VARS_USED 26


int main()
{
    string str;
    getline(cin, str);

    if (str.empty())
        return 1;

    vector <Token> tokens = tokenize(str);
    validate_tokens(tokens);
    vector<char> vars = find_l_vars(tokens);
    vector<Token> postfix = to_postfix(tokens);

    print_header(vars);
    print_table(postfix, vars);

    return 0;
}
