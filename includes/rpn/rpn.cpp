#include "rpn.h"

RPN::RPN(){

}

RPN::RPN(const Queue<Token*> &postfix){
    _postfix = postfix;
}

vector<long> RPN::eval(const map_sl& fieldMap, const vector<mmap_sl*>& index){
    Queue<Token*> postfix_q = _postfix;
    Stack<Token*> call_stack;
    while(!postfix_q.empty()){
        call_stack.push(postfix_q.pop());
        if(call_stack.top() -> type() == RELATIONAL){
            Token* op = call_stack.pop();
            Token* right = call_stack.pop();
            Token* left = call_stack.pop();
            call_stack.push(static_cast<Relational*>(op) -> eval(fieldMap, index, left, right));
        }
        if(call_stack.top() -> type() == LOGICAL){
            Token* op = call_stack.pop();
            vector<long> right = call_stack.pop() -> getVec();
            vector<long> left = call_stack.pop() -> getVec();
            call_stack.push(static_cast<Logical*>(op) -> eval(left, right));
        }
    }
    vector<long> result = call_stack.pop() -> getVec();
    return result;
}
