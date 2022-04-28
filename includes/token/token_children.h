#ifndef TOKEN_CHILDREN_H
#define TOKEN_CHILDREN_H

#include "token.h"

class ResultSet : public Token{
public:
    ResultSet();
    ResultSet(vector<long> recnos);
    vector<long> getVec()const;

private:
    vector<long> _recnos;
};

class Relational : public Token{
public:
    Relational();
    Relational(string op);
    int type() const;
    string getValue() const;
    void setValue(string op);
    int Precedence();
    ResultSet* eval(const map_sl& fieldMap, const vector<mmap_sl*>& index, Token* left, Token* right);
private:
    string _op;
};

class Logical : public Token{
public:
    Logical();
    Logical(string op);
    int type() const;
    string getValue() const;
    void setValue(string op);
    int Precedence();
    ResultSet* eval(vector<long> left, vector<long> right);
private:
    string _op;
};



class TokenStr : public Token{
public:
    TokenStr();
    TokenStr(string token_str);
    int type() const;
    string getValue() const;
    void setValue(string token_str);
private:
    string _token_str;
};

class LParen : public Token{
public:
    LParen();
    int type() const;
    string getValue() const;
    int Precedence();
private:
    string _op;
};

class RParen : public Token{
public:
    RParen();
    int type() const;
    string getValue() const;
    int Precedence();
private:
    string _op;
};


#endif //TOKEN_CHILDREN_H
