#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <assert.h>
#include "btree_array_funcs.h"

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){}

        T operator *(){
            return it -> data[key_ptr];
        }

        Iterator operator++(int un_used){
            if(it){
                Iterator it_ptr = Iterator(it, key_ptr);
                if(key_ptr < it -> data_count - 1){
                    key_ptr++;
                }else{
                    it = it -> next;
                    key_ptr = 0;
                }
                return it_ptr;
            }
        }
        Iterator operator++(){
            if(it){
                if(key_ptr < it -> data_count - 1){
                    key_ptr++;
                }else{
                    it = it -> next;
                    key_ptr = 0;
                }
                return *this;
            }
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            if(lhs.it == nullptr && rhs.it == nullptr){
                return true;
            }

            if(lhs.it != nullptr && rhs.it != nullptr){
                Iterator lhs_cpy(lhs.it, lhs.key_ptr);
                Iterator rhs_cpy(rhs.it, rhs.key_ptr);
                return *lhs_cpy == *rhs_cpy;
            }
            return false;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return !(lhs == rhs);
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const;       //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    const T& get_existing(const T& entry)const;
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template <typename T>
BPlusTree<T>::BPlusTree(bool dups):dups_ok(dups), data_count(0),
                                   child_count(0), next(NULL){
    for(int i = 0; i < MAXIMUM + 1; i++){
        data[i] = T();
    }

    for(int i = 0; i < MAXIMUM + 2; i++){
        subset[i] = nullptr;
    }
}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups){
    dups_ok = dups;
    child_count = 0;
    data_count = 0;
    next = NULL;
    for(int i = 0; i < MAXIMUM + 1; i++){
        data[i] = T();
    }

    for(int i = 0; i < MAXIMUM + 2; i++){
        subset[i] = nullptr;
    }

    for(int i = 0; i < size; i++){
        insert(a[i]);
    }
}

//big three:
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){
    copy_tree(other);
}

template <class T>
BPlusTree<T>::~BPlusTree(){
    //cout << "Entered ~BTree: "<< endl;
    const bool debug = false;
    if(debug){
        cout <<"=w="<<endl;
    }
    clear_tree();
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){
    if(this == &RHS){
        return *this;
    }
    //clear_tree();
    copy_tree(RHS);
    return *this;
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
    if(other.data_count < 0 || other.data_count > MAXIMUM + 1){
        return;
    }
    //clear_tree();
    BPlusTree<T>* newNode = nullptr;
    copy_tree(other, newNode);
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node){
    //cout << "Entered copy: "<< endl;
    dups_ok = other.dups_ok;
    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;

    if(other.child_count < 0 || other.child_count > MAXIMUM + 2){
        return;
    }
    next = nullptr;
    if(!other.is_leaf()){
        for(int i = 0; i < child_count; i++){
            BPlusTree* copy = new BPlusTree<T>;
            subset[i] = copy;
            subset[i] -> copy_tree(*other.subset[i], last_node);
        }
    }
    if(other.is_leaf()){
        if(last_node != nullptr){
            last_node -> next = this;
        }
        last_node = this;
    }
}

template <class T>
void BPlusTree<T>::insert(const T& entry){
    //cout << "INSERTING: " << entry << endl;
    loose_insert(entry);
    if(data_count > MAXIMUM){
        BPlusTree* newNode = new BPlusTree<T>();
        copy_array(newNode -> data, data, newNode -> data_count, data_count);
        copy_array(newNode -> subset, subset, newNode -> child_count, child_count);
        data_count = 0;
        child_count = 1;
        subset[0] = newNode;
        fix_excess(0);
    }
}

template <class T>
void BPlusTree<T>::remove(const T& entry){
    loose_remove(entry);
    if(data_count == 0 && child_count == 1){
        BPlusTree* shrink_ptr = subset[0];
        copy_array(data, shrink_ptr -> data, data_count, shrink_ptr -> data_count);
        copy_array(subset, shrink_ptr -> subset, child_count, shrink_ptr -> child_count);
        for(int i = 0; i < shrink_ptr -> child_count; i++){
            shrink_ptr -> subset[i] = nullptr;
        }
        shrink_ptr -> data_count = 0;
        shrink_ptr -> child_count = 0;
        shrink_ptr = nullptr;
        delete shrink_ptr;
    }
}

template <class T>
void BPlusTree<T>::clear_tree(){
    data_count = 0;
    if(!is_leaf()){
        for(int i = 0; i < child_count; i++){
            subset[i] -> clear_tree();
            delete subset[i];
        }
    }
    next = nullptr;
    child_count = 0;
}

template <class T>
bool BPlusTree<T>::contains(const T& entry) const{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(found){
        return true;
    }
    if(is_leaf()){
        return false;
    }
    return subset[i] -> contains(entry);
}

template <class T>
T& BPlusTree<T>::get(const T& entry){
    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

template <class T>
const T& BPlusTree<T>::get(const T& entry)const{
    // assert(contains(entry));
    return get_existing(entry);
}

template <class T>
T& BPlusTree<T>::get_existing(const T& entry){
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);  
}

template <class T>
const T& BPlusTree<T>::get_existing(const T& entry)const{
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);  
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key){
    int i = first_ge(data, data_count, key);
    bool found = (i<data_count && data[i]==key);
    if(found && is_leaf()){
        return Iterator(this, i);
    }else if(!found && !is_leaf()){
        return subset[i] -> find(key);
    }else if(found && !is_leaf()){
        return subset[i + 1] -> find(key);
    }else{
        return Iterator();
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){
    for(Iterator it = begin(); it != end(); it++){
        if(*it >= key){
            return it;
        }
    }
    return Iterator();
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){
    for(Iterator it = begin(); it != end(); it++){
        if(*it > key){
            return it;
        }
    }
    return Iterator();
}

template <class T>
int BPlusTree<T>::size() const{
    int count = 0;
    if(data_count > 0){
        for(int i = 0; i < child_count; i++){
            count += subset[i] -> size();
        }
        count += data_count;
    }
    return count;
}

template <class T>
bool BPlusTree<T>::empty() const{
    return (data_count == 0);
}

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    if(!empty()){
        for(int i = child_count - 1; i >= 0; i--){
            if(i == data_count - 1){
                outs << setw(8 * level) << "---" << endl;
            }
            if(i < data_count){
                outs << setw(8 * level) << data[i] << endl;
            }
            if(i == 0){
                outs << setw(8 * level) << "---" << endl;
            }
            subset[i] -> print_tree(level + 1, outs);
        }
        //Printing all the leaf nodes at once
        if(is_leaf()){
            outs << setw(8 * level - 1) << "^" << endl;
            outs << setw(8 * level) << "---" << endl;
            for(int i = data_count - 1; i >= 0; i--){
                outs << setw(8 * level) << data[i] << endl;
            }
            outs << setw(8 * level) << "---" << endl;
        }
    }
}

template <class T>
bool BPlusTree<T>::is_valid(){
    return true;
}

template <class T>
string BPlusTree<T>::in_order(){
    string s = "";
    if(data_count > 0){
        for(int i = 0; i < child_count; i++){
            s += subset[i] -> in_order();
            if(i < data_count){
                s += to_string(data[i]) + "|";
            }
        }
        if(is_leaf()){
            for(int j = 0; j < data_count; j++){
                s += to_string(data[j]) + "|";
            }
        }
    }
    return s;
}

template <class T>
string BPlusTree<T>::pre_order(){
    string s = "";
    if(data_count > 0){
        for(int i = 0; i < child_count; i++){
            if(i < data_count){
                s += to_string(data[i]) + "|";
            }
            s += subset[i] -> pre_order();
        }
        if(is_leaf()){
            for(int j = 0; j < data_count; j++){
                s += to_string(data[j]) + "|";
            }
        }
    }
    return s;
}

template <class T>
string BPlusTree<T>::post_order(){
    string s = "";
    if(data_count > 0){
        if(!is_leaf()){
            s += subset[0] -> post_order();
        }
        for(int i = 0; i < data_count; i++){
            if(i < child_count - 1){
                s += subset[i + 1] -> post_order();
            }
            s += to_string(data[i]) + "|";
        }
    }
    return s;
}

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    return Iterator(get_smallest_node());
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
    return Iterator(NULL);
}

template <class T>
T* BPlusTree<T>::find_ptr(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(found){
        return &data[i];
    }
    if(is_leaf()){
        return nullptr;
    }
    return subset[i] -> find_ptr(entry);
}
                  
template <class T>
void BPlusTree<T>::loose_insert(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(found){
        if(is_leaf()){
            data[i] = entry;
        }else{
            subset[i+1]->loose_insert(entry);
            fix_excess(i+1);
        }
    }else{
        if(is_leaf()){
            insert_item(data, i, data_count, entry);
        }else{
            subset[i]->loose_insert(entry);
            fix_excess(i);
        }
    }
}

template <class T>
void BPlusTree<T>::fix_excess(int i){
    if(subset[i] != nullptr){
        if(subset[i] -> data_count > MAXIMUM){
            BPlusTree* sub_left = subset[i];
            BPlusTree<T>* sub_right = new BPlusTree<T>();
            T left_max = T();
            insert_item(subset, i + 1, child_count, sub_right);
            split(sub_left -> data, sub_left -> data_count, sub_right -> data, sub_right -> data_count);
            split(sub_left -> subset, sub_left -> child_count, sub_right -> subset, sub_right -> child_count);
            detach_item(sub_left -> data, sub_left -> data_count, left_max);
            insert_item(data, i, data_count, left_max);
            if(sub_right -> is_leaf()){
                insert_item(sub_right -> data, 0, sub_right -> data_count, left_max);
                sub_right -> next = sub_left -> next;
                sub_left -> next = sub_right;
            }
        }
    }
}

template <class T>
void BPlusTree<T>::loose_remove(const T& entry){
    T deleted = T();
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(is_leaf() && !found){
        return;
    }

    if(is_leaf() && found){
        delete_item(data, i, data_count, deleted);
    }

    if(!is_leaf() && !found){
        subset[i]->loose_remove(entry);
        fix_shortage(i);
    }

    if(!is_leaf() && found){
        subset[i + 1] -> loose_remove(entry);
        BPlusTree<T>* temp = fix_shortage(i + 1);
        i = first_ge(data, data_count, entry);
        found = (i<data_count && data[i] == entry);
        if(found){
            T newData = T();
            subset[i + 1] -> get_smallest(newData);
            data[i] = newData;
        }else{
            i = first_ge(temp -> data, temp -> data_count, entry);
            found = (i< temp -> data_count && temp -> data[i] == entry);
            if(found){
                T newData = T();
                temp -> subset[i + 1] -> get_smallest(newData);
                temp -> data[i] = newData;
            }
        }
    }
}

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    if(subset[i] -> data_count < MINIMUM){
        if(subset[i] != nullptr){
            if(i > 0){
                if(subset[i - 1] -> data_count > MINIMUM){      //borrowing from left
                    transfer_right(i);
                    return subset[0];
                }else{                                          //merge with left
                    merge_with_next_subset(i - 1);
                    return subset[0];
                }
            }

            if(i < child_count - 1){
                if(subset[i + 1] -> data_count > MINIMUM){      //borrowing from right
                    transfer_left(i);
                    return subset[0];
                }else if(subset[i] -> data_count < MINIMUM){    //merge with right
                    merge_with_next_subset(i);
                    return subset[0];
                }
            }
        }
    }
}


template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
    if(is_leaf()){
        return this;
    }else{
        return subset[0] -> get_smallest_node();
    }
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry){
    if(!is_leaf()){
        subset[0] -> get_smallest(entry);
    }else{
        entry = data[0];
    }
}

template <class T>
void BPlusTree<T>::get_biggest(T& entry){
    if(!is_leaf()){
        subset[child_count - 1] -> get_smallest(entry);
    }else{
        entry = data[data_count - 1];
    }
}

template <class T>
void BPlusTree<T>::remove_biggest(T& entry){
    if(!is_leaf()){
        subset[child_count - 1] -> get_smallest(entry);
    }else{
        detach_item(data, data_count, entry);
    }
}

template <class T>
void BPlusTree<T>::transfer_left(int i){
    T right_detached = T();
    BPlusTree* child_detached = nullptr;
    attach_item(subset[i] -> data, subset[i] -> data_count, data[i]);
    delete_item(subset[i + 1] -> data, 0, subset[i + 1] -> data_count, right_detached);
    data[i] = right_detached;
    if(subset[i + 1] -> is_leaf() == false){
        delete_item(subset[i + 1] -> subset, 0, subset[i + 1] -> child_count, child_detached);
        attach_item(subset[i] -> subset, subset[i] -> child_count, child_detached);
    }
    if(subset[i + 1] -> is_leaf()){
        data[i] = subset[i + 1] -> data[0];
    }
}

template <class T>
void BPlusTree<T>::transfer_right(int i){
    T left_detached = T();
    BPlusTree* child_detached = nullptr;
    insert_item(subset[i] -> data, 0, subset[i] -> data_count, data[i - 1]);
    detach_item(subset[i - 1] -> data, subset[i - 1] -> data_count, left_detached);
    data[i - 1] = left_detached;
    if(subset[i] -> is_leaf() == false){
        detach_item(subset[i - 1] -> subset, subset[i - 1] -> child_count, child_detached);
        insert_item(subset[i] -> subset, 0, subset[i] -> child_count, child_detached);
    }
    if(subset[i] -> is_leaf()){
        subset[i] -> data[0] = left_detached;
    }
}

template <class T>
BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i){
    T data_detached = T();
    BPlusTree* deleted = nullptr;
    delete_item(data, i, data_count, data_detached);
    if(!subset[i] -> is_leaf()){
        attach_item(subset[i] -> data, subset[i] -> data_count, data_detached);
    }
    merge(subset[i] -> data, subset[i] -> data_count, subset[i + 1] -> data, subset[i + 1] -> data_count);
    merge(subset[i] -> subset, subset[i] -> child_count, subset[i + 1] -> subset, subset[i + 1] -> child_count);
    delete_item(subset, i + 1, child_count, deleted);
}

#endif //BPLUSTREE_H
