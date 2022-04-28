#ifndef QUEUE_H
#define QUEUE_H

#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                              //give access to list to access _ptr
        Iterator(){
            _ptr = nullptr;
        }                                     //default ctor
        Iterator(node<T>* p){
            _ptr = p;
        }                   //Point Iterator to where p is pointing to
        operator bool(){
            if(_ptr != nullptr){
                return true;
            }
            return false;
        }                                //casting operator: true if _ptr not NULL
                                                        //      this turned out to be a pain!


        T& operator *(){
            return _ptr -> _item;
        }                        //dereference operator
        T* operator ->(){
            return &_ptr -> _item;
        }                       //member access operator

        bool is_null(){
            if(_ptr == nullptr){
                return true;
            }
            return false;
        }                                 //true if _ptr is NULL

        friend bool operator !=(const Iterator& left,
                                const Iterator& right){
                                    if(left._ptr != right._ptr){
                                        return true;
                                    }
                                    return false;
                                } //true if left != right

        friend bool operator ==(const Iterator& left,
                                const Iterator& right){
                                    if(left._ptr == right._ptr){
                                        return true;
                                    }
                                    return false;
                                } //true if left == right

        Iterator& operator++(){
            _ptr = _ptr -> _next;
            return *this;
        }                         //member operator: ++it; or ++it = new_value

        friend Iterator operator++(Iterator& it,
                                   int unused){
                                       Iterator it_ptr = Iterator(it._ptr);
                                       it._ptr = it._ptr -> _next;
                                       return it_ptr;
                                   }         //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <typename T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = nullptr;
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template <typename T>
Queue<T>::~Queue(){
    const bool debug = false;
    if(debug){
        cout <<"QwQ"<<endl;
    }
    _clear_list(_front);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if(this == &RHS){
        return *this;
    }
    _clear_list(_front);
    
    _size = RHS._size;
    
    _rear = _copy_list(_front, RHS._front);
    return *this;
}

template <typename T>
bool Queue<T>::empty(){
    if(_front == nullptr){
        return true;
    }
    return false;
}

template <typename T>
T Queue<T>::front(){
    return _front -> _item;
}

template <typename T>
T Queue<T>::back(){
    return _rear -> _item;
}

template <typename T>
void Queue<T>::push(T item){
    if(_front == nullptr){
        _insert_head(_front, item);
        _rear = _front;
    }else{
        _insert_after(_front, _rear, item);
        _rear = _rear -> _next;
    }
    _size++;
}

template <typename T>
T Queue<T>::pop(){
    _size--;
    return _delete_node(_front, _front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    return Iterator();
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){
    node<TT>* walker = printMe._front;
    outs <<"Queue::Head->";
    while(walker != nullptr){
        outs << *walker;
        walker = walker -> _next;
    }
    outs << "|||" << endl;
    return outs;
}


#endif //QUEUE_H
