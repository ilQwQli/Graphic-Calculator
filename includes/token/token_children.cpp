#include "token_children.h"

TokenStr::TokenStr(){

}

TokenStr::TokenStr(string token_str){
    _token_str = token_str;
}

int TokenStr::type() const{
    return TOKEN_STRING;
}

string TokenStr::getValue() const{
    return _token_str;
}

void TokenStr::setValue(string token_str){
    _token_str = token_str;
}



Relational::Relational(){

}

Relational::Relational(string op){
    _op = op;
}

int Relational::type() const{
    return RELATIONAL;
}

string Relational::getValue() const{
    return _op;
}

void Relational::setValue(string op){
    _op = op;
}

int Relational::Precedence(){
    return 3;
}

ResultSet* Relational::eval(const map_sl& fieldMap, const vector<mmap_sl*>& index, Token* left, Token* right){
    vector<long> records_selected;
    if(_op == "="){
        records_selected = (index[fieldMap[left -> getValue()]]) -> at(right -> getValue());
    }else if(_op == ">="){
        mmap_sl::Iterator begin = index[fieldMap[left -> getValue()]] -> lower_bound(right -> getValue());
        mmap_sl::Iterator end = index[fieldMap[left -> getValue()]] -> end();
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }else if(_op == ">"){
        mmap_sl::Iterator begin = index[fieldMap[left -> getValue()]] -> upper_bound(right -> getValue());
        mmap_sl::Iterator end = index[fieldMap[left -> getValue()]] -> end();
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }else if(_op == "<="){
        mmap_sl::Iterator begin = index[fieldMap[left -> getValue()]] -> begin();
        mmap_sl::Iterator end = index[fieldMap[left -> getValue()]] -> upper_bound(right -> getValue());
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }else if(_op == "<"){
        mmap_sl::Iterator begin = index[fieldMap[left -> getValue()]] -> begin();
        mmap_sl::Iterator end = index[fieldMap[left -> getValue()]] -> lower_bound(right -> getValue());
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }
    return new ResultSet(records_selected);
}




Logical::Logical(){

}

Logical::Logical(string op){
    _op = op;
}

int Logical::type() const{
    return LOGICAL;
}

string Logical::getValue() const{
    return _op;
}

void Logical::setValue(string op){
    _op = op;
}

int Logical::Precedence(){
    if(_op == "and"){
        return 2;
    }else{
        return 1;
    }
}

ResultSet* Logical::eval(vector<long> left, vector<long> right){
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<long> result_vector;

    if(_op == "and"){
        set_intersection(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result_vector));
    }

    if(_op == "or"){
        set_union(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result_vector));
    }

    return new ResultSet(result_vector);
}





ResultSet::ResultSet(){

}

ResultSet::ResultSet(vector<long> recnos){
    _recnos = recnos;
}

vector<long> ResultSet::getVec()const{
    return _recnos;
}



LParen::LParen(){
    _op = "(";
}

int LParen::type() const{
    return LEFTPAREN;
}

string LParen::getValue() const{
    return _op;
}

int LParen::Precedence(){
    return 4;
}



RParen::RParen(){
    _op = ")";
}

int RParen::type() const{
    return RIGHTPAREN;
}

string RParen::getValue() const{
    return _op;
}

int RParen::Precedence(){
    return 4;
}
