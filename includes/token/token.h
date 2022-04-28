#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include "../tokenizer/constants.h"
#include "../table/typedefs.h"

using namespace std;

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token& t);
    virtual int type() const;
    string type_string() const;
    string token_str() const;
    virtual string getValue() const;
    virtual vector<long> getVec() const;
    virtual void setValue(string op);
    virtual int Precedence();
private:
    string _token;
    int _type;
};

#endif //TOKEN_H
