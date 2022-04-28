#ifndef RPN_H
#define RPN_H

#include <iostream>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../table/typedefs.h"
#include "../token/token_children.h"

using namespace std;

class RPN{
public:
    RPN();
    RPN(const Queue<Token*> &postfix);
    vector<long> eval(const map_sl& fieldMap, const vector<mmap_sl*>& index);
private:
    Queue<Token*> _postfix;
};

#endif // RPN_H
