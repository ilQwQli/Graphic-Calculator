#ifndef LINK_LISTED_H
#define LINK_LISTED_H

#include "../node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                                T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                                T insert_this);

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                 node<T> *after_this,
                                 T insert_this);

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                  node<T>* before_this,
                                  T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head,
                                  node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*&head,
                         node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T>* _insert_sorted(node<T>* &head,       //insert
                              T item,
                              bool ascending=true);

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head,
                                      T item,
                                      bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head,
                               T item,
                               bool ascending=true);
//Last Node in the list
template <typename T>
node<T>* _last_node(node<T>* head);            //

  //--------------------------------------------------------//
 //-----------------------definition-----------------------//
//--------------------------------------------------------//



template <typename T>
void _print_list(node<T>* head){
    //have walker point to head
    node<T> *walker = head;
    cout << "H->";
    //loop to print out each node in the head
    while(walker != nullptr){
        cout <<*walker;
        //move to the next node
        walker = walker -> _next;
    }
    cout << "|||" <<endl;
}

//recursive function
template <typename T>
void _print_list_backwards(node<T> *head){
    node<T> *walker = head;
    //output null when recursive reached the end of the linked list
    //which will also break out of the recursive function loop
    if(walker == nullptr){
        cout << "|||->";
        //break out of the last recursive function loop, move into the one before
        return;
    }
    //recursive function call, which will save the head value and move on until null
    _print_list_backwards(walker -> _next);
    //this will be unused until breaked out of the loop
    cout << *walker;
}

template <typename T>
node<T>* _search_list(node<T>* head, T key){
    node<T> *walker = head;
    //loop to search through the linked list
    while(walker != nullptr){
        //conditional statement to check if current item in the node match the key
        if(walker -> _item == key){
            return walker;
        }
        //move on if didn't match
        walker = walker -> _next;
    }
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    //create a new node
    node<T> *temp = new node<T>(insert_this, head);
    if(head != nullptr){
        head -> _prev = temp;
    }
    //link temp to head
    head = temp;
    return head;
}

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    if(head == nullptr){
        head = _insert_head(head, insert_this);
        return head;
    }
    //create a new node
    node<T> *temp = new node<T>(insert_this);
    //link the temp node's next node address, so the right side of temp is linked
    temp -> _next = after_this -> _next;
    //then link after_this's next node address to the temp, so the link is connected
    after_this -> _next = temp;
    return temp;
}

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){ 
    //if the before_this is the head of the linked list, then insert a head instead
    if(before_this == head){
        head = _insert_head(head, insert_this);
        return head;
    }
    //create a new node that points to the info of the previous node
    node<T> *prev = before_this -> _prev;
    //if before_this is not the header, then insert it after prev
    node<T> *temp = _insert_after(head, prev, insert_this);
    return temp;
}

template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this){
    node<T> *walker = head;
    //check if the prev_to_this is the header, return nullptr if true
    if(walker == prev_to_this){
        return nullptr;
    }
    //loop to go through the linked list
    while(walker != nullptr){
        //find the previous node and return it
        if(walker -> _next == prev_to_this){
            return walker;
        }
        //move to next node in the list
        walker = walker -> _next;
    }
    return nullptr;
}

template <typename T>
T _delete_node(node<T>*&head, node<T>* delete_this){
    assert(delete_this != nullptr && "cannot delete null");
    node<T> *temp = delete_this;
    T save = delete_this -> _item;
    node<T> *prev = _previous_node(head, delete_this);
    //check if the delete_this is the header, if yes, then change the head to the next node
    if(prev == nullptr){
        head = temp -> _next;
    }else{
        //otherwise, link the prev node to the node after delete_this
        prev -> _next = temp -> _next;
    }
    //delete and return the deleted value
    delete delete_this;
    return save;
}

template <typename T>
node<T>* _copy_list(node<T>* head){
    if(head != nullptr){
        //make a new node with a head item
        node<T> *list = new node<T>(head -> _item);
        node<T> *walker = list;
        node<T> *walkerh = head;
        //move the head to the next value since head already exist
        walkerh = walkerh -> _next;
        //loop to go through the linked list
        while(walkerh != nullptr){
            //insert node until all node has been inserted
            _insert_after(list, walker, walkerh -> _item);
            walkerh = walkerh -> _next;
            walker = walker -> _next;
        }
        return list;
    }
    return nullptr;
}

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    node<T> *walker = src;
    if(src != nullptr){
        _insert_head(dest, walker -> _item);
        node<T> *walkerd = dest;
        walker = walker -> _next;
        //loop to go through the linked list
        while(walker != nullptr){
            //insert node until all node has been inserted
            _insert_after(dest, walkerd, walker -> _item);
            if(walkerd -> _next == nullptr){
                return walkerd;
            }
            walkerd = walkerd -> _next;
            walker = walker -> _next;
        }
        return walkerd;
    }
    return nullptr;
}

template <typename T>
void _clear_list(node<T>*& head){
    node<T> *walker = head;
    //loop to go through the linked list
    while(walker != nullptr){
        //make walker one node before the head
        //so we can delete node one by one from left to right
        walker = walker -> _next;
        delete head;
        head = walker;
    }  
}

template <typename T>
T& _at(node<T>* head, int pos){
    node<T>* walker = head;
    //loop to go through by the number of pos
    while(pos != 0){
        //move head to the next one each loop and decrement pos
        walker = walker -> _next;
        pos--;
    }
    assert(walker != nullptr && "cannot return null");
    //return the item at that position
    return walker -> _item;
}

template <typename T>
node<T>* _last_node(node<T>* head){
    node<T>* walker = head;
    //loop to go through the linked list
    while(walker != nullptr){
        if(walker -> _next == nullptr){
            return walker;
        }
        //move into the next node
        walker = walker -> _next;
    }
    //return the last node which should be null
    return walker;
}

template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending){
    //create a pos node to save the position
    node<T>* pos = _where_this_goes(head, item, ascending);
    //insert the item by the position
    head = _insert_after(head, pos, item);
    
    return head;
}

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head, T item, bool ascending){

    return nullptr;
}

//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending){
    //pointer to head and temp to save address of walker
    node<T>* walker = head;
    node<T>* temp = nullptr;
    //loop through the whole list
    while(walker != nullptr){
        if(ascending == true && walker -> _item <= item){               //check the position for ascending
            //save the walker's address before the function exit increment
            temp = walker;
        }else if(ascending == false && walker -> _item >= item){        //check the position for descending
            //save the walker's address before the function exit increment
            temp = walker;
        }
        //increment to the next node
        walker = walker -> _next;
    }
    return temp;
}

#endif //LINK_LISTED_H
