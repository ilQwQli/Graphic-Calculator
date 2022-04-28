#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/token_children.h"

using namespace std;

class ShuntingYard{
public:
    ShuntingYard();
    ShuntingYard(const Queue<Token*> &infix);
    void set_infix(Queue<Token*> infix);
    Queue<Token*> postfix();
    Queue<Token*> postfix(Queue<Token*> &infix);
    Queue<Token*> tk_vector(vector<string> v);
private:
    Queue<Token*> _infix;
};

#endif // SHUNTING_YARD_H
