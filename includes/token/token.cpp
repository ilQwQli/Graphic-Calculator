#include "token.h"

Token::Token(){
    _token = "";
    _type = -1;
}

Token::Token(string str, int type){
    _token = str;
    _type = type;
}

ostream& operator <<(ostream& outs, const Token& t){
    outs << "|";
    if(t.getValue() != "\0"){
        outs << t.getValue();
    }else{
        outs << " ";
    }
    outs << "|";

    return outs;
}

int Token::type() const{
    return _type;
}

string Token::type_string() const{
    string s = "";
    switch(_type){
        case 1:
            s = "NUMBER";
            break;
        case 2:
            s = "ALPHA";
            break;
        case 3:
            s = "SPACE";
            break;
        case 4:
            s = "OPERATOR";
            break;
        case 5:
            s = "PUNC";
            break;
        case -1:
            s = "UNKNOWN";
            break;
        case -2:
            s = "END";
            break;
    }
    return s;
}

string Token::token_str() const{
    return _token;
}

string Token::getValue() const{
    return _token;
}

void Token::setValue(string op){
    _token = op;
}

int Token::Precedence(){
    return 0;
}

vector<long> Token::getVec() const{

}

