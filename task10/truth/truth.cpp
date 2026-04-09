#include "truth.hpp"


void fail()
{
    throw std::runtime_error("invalid expression");
}


bool is_operator(TokenType t)
{
    return t == AND_OP || t == OR_OP || t == NOT_OP;
}


int precedence(TokenType t)
{
    if (t == NOT_OP) return 3;
    if (t == AND_OP) return 2;
    if (t == OR_OP) return 1;
    return 0;
}


bool right_associative(TokenType t)
{
    return t == NOT_OP;
}


vector<Token> tokenize(const string& s)
{
    vector<Token> tokens;
    size_t i = 0;

    while (i < s.size())
    {
        if (isspace((unsigned char)s[i]))
        {
            ++i;
            continue;
        }

        if (s[i] == '(')
        {
            tokens.push_back({LPAREN, 0});
            ++i;
            continue;
        }

        if (s[i] == ')')
        {
            tokens.push_back({RPAREN, 0});
            ++i;
            continue;
        }

        if (s.compare(i, 3, "AND") == 0 &&
                (i + 3 == s.size() || !isalpha((unsigned char)s[i + 3])))
        {
            tokens.push_back({AND_OP, 0});
            i += 3;
            continue;
        }

        if (s.compare(i, 2, "OR") == 0 &&
                (i + 2 == s.size() || !isalpha((unsigned char)s[i + 2])))
        {
            tokens.push_back({OR_OP, 0});
            i += 2;
            continue;
        }

        if (s.compare(i, 3, "NOT") == 0 &&
                (i + 3 == s.size() || !isalpha((unsigned char)s[i + 3])))
        {
            tokens.push_back({NOT_OP, 0});
            i += 3;
            continue;
        }

        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            tokens.push_back({VAR, s[i]});
            ++i;
            continue;
        }

        fail();
    }

    if (tokens.empty())
        fail();
    return tokens;
}


void validate_tokens(const vector<Token>& tokens)
{
    bool expect_operand = true;
    int balance = 0;

    for (const auto& t : tokens) {
        if (expect_operand)
        {
            if (t.type == VAR)
                expect_operand = false;
            else if (t.type == NOT_OP) {}
            else if (t.type == LPAREN)
                ++balance;
            else
                fail();
        }
        else
        {
            if (t.type == AND_OP || t.type == OR_OP)
                expect_operand = true;
            else if (t.type == RPAREN)
            {
                --balance;
                if (balance < 0) fail();
            }
            else
                fail();
        }
    }

    if (expect_operand || balance != 0) fail();
}


vector<char> find_l_vars(const vector<Token>& tokens)
{
    vector<char> vars;
    for (const auto& t : tokens)
        if (t.type == VAR && find(vars.begin(), vars.end(), t.var) == vars.end())
            vars.push_back(t.var);
    sort(vars.begin(), vars.end());
    return vars;
}


vector<Token> to_postfix(const vector<Token>& tokens)
{
    vector<Token> output;
    vector<Token> ops;

    for (const auto& t : tokens) {
        if (t.type == VAR)
            output.push_back(t);
        else if (t.type == LPAREN)
            ops.push_back(t);
        else if (t.type == RPAREN)
        {
            while (!ops.empty() && ops.back().type != LPAREN)
            {
                output.push_back(ops.back());
                ops.pop_back();
            }
            if (ops.empty()) fail();
            ops.pop_back();
        }
        else if (is_operator(t.type))
        {
            while (!ops.empty() && is_operator(ops.back().type))
            {
                TokenType top = ops.back().type;
                if (precedence(top) > precedence(t.type) ||
                    (precedence(top) == precedence(t.type) && !right_associative(t.type)))
                {
                    output.push_back(ops.back());
                    ops.pop_back();
                }
                else
                    break;
            }
            ops.push_back(t);
        }
        else
            fail();
    }

    while (!ops.empty())
    {
        if (ops.back().type == LPAREN || ops.back().type == RPAREN)
            fail();
        output.push_back(ops.back());
        ops.pop_back();
    }

    return output;
}


bool get_value(char var, const vector<char>& vars, int mask)
{
    int pos = find(vars.begin(), vars.end(), var) - vars.begin();
    if (pos < 0 || pos >= (int)vars.size())
        fail();
    return (mask >> (vars.size() - 1 - pos)) & 1;
}


bool eval_postfix(const vector<Token>& postfix, const vector<char>& vars, int mask)
{
    vector<bool> st;

    for (const auto& t : postfix)
    {
        if (t.type == VAR)
            st.push_back(get_value(t.var, vars, mask));
        else if (t.type == NOT_OP)
        {
            if (st.empty()) fail();
            bool a = st.back();
            st.back() = !a;
        }
        else if (t.type == AND_OP)
        {
            if (st.size() < 2) fail();
            bool b = st.back(); st.pop_back();
            bool a = st.back(); st.pop_back();
            st.push_back(a && b);
        }
        else if (t.type == OR_OP)
        {
            if (st.size() < 2) fail();
            bool b = st.back(); st.pop_back();
            bool a = st.back(); st.pop_back();
            st.push_back(a || b);
        }
        else
            fail();
    }

    if (st.size() != 1)
        fail();
    return st.back();
}


void print_header(const vector<char>& vars)
{
    for (char c : vars)
        cout << c << ' ';
    cout << "Result\n";
}


void print_table(const vector<Token>& postfix, const vector<char>& vars)
{
    int total = 1 << vars.size();

    for (int mask = 0; mask < total; ++mask)
    {
        for (size_t i = 0; i < vars.size(); ++i)
        {
            cout << ((mask >> (vars.size() - 1 - i)) & 1) << ' ';
        }
        cout << eval_postfix(postfix, vars, mask) << '\n';
    }
}
