#include "shunting_yard.h"

ShuntingYard::ShuntingYard(){
    
}

ShuntingYard::ShuntingYard(const Queue<Token*> &infix){
    _infix = infix;
}

Queue<Token*> ShuntingYard::postfix(){
    Queue<Token*> result_queue = Queue<Token*>();
    Stack<Token*> op_stack = Stack<Token*>();
    while(!_infix.empty()){
        Token* current = _infix.front();
        int type = current -> type();
        if(type == TOKEN_STRING){
            result_queue.push(current);
            _infix.pop();
        }else if(type == LOGICAL || type == RELATIONAL){
            if(!op_stack.empty()){          //check for empty, its type, and most importantly check for its precedence
                while(!op_stack.empty() && (op_stack.top() -> type() == LOGICAL || op_stack.top() -> type() == RELATIONAL) && op_stack.top() -> Precedence() >= _infix.front() -> Precedence()){
                    result_queue.push(op_stack.top());    //push into the queue and remove it from stack if its precedence is set
                    op_stack.pop();
                }
                op_stack.push(current);
                _infix.pop();  
            }else{
                op_stack.push(current);         //if empty, then push it into the operator stack
                _infix.pop();  
            }
        }else if(type == LEFTPAREN){
            op_stack.push(current);
            _infix.pop();
        }else if(type == RIGHTPAREN){
            if(!op_stack.empty()){          //check for empty
                while(op_stack.top() -> type() != LEFTPAREN){     //loop until the top of the stack found leftparen
                    if(!op_stack.empty()){  //check for empty again
                        result_queue.push(op_stack.top());    //push the top of the stack value into queue
                        op_stack.pop();     //then pop the pushed value
                    }
                }
            }

            if(!op_stack.empty() && op_stack.top() -> type() == LEFTPAREN){   //check for empty and the type
                op_stack.pop();     //pop the leftparen operator after the process is done
            }
            _infix.pop();
        }else{
            cout << "ERROR: unknown opeartor type: " << *current << type << endl;
            exit(0);
        }
    }

    while(!op_stack.empty()){
        result_queue.push(op_stack.top());    //push the rest of the value into the postfix queue
        op_stack.pop();
    }
    return result_queue;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> &infix){
    _infix = infix;
    return postfix();
}

void ShuntingYard::set_infix(Queue<Token*> infix){
    _infix = infix;
}

Queue<Token*> ShuntingYard::tk_vector(vector<string> v){
    Queue<Token*> result;
    for(int i = 0; i < v.size(); i++){
        string input = v[i];
        if(input == "and" || input == "or"){
            result.push(new Logical(input));
        }else if(input == "=" || input == "<=" || input == ">=" || input == "<" || input == ">"){
            result.push(new Relational(input));
        }else if(input == "("){
            result.push(new LParen());
        }else if(input == ")"){
            result.push(new RParen());
        }else{
            result.push(new TokenStr(input));
        }
    }
    return result;
}
