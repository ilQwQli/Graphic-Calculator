#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "bplustree.h"

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()){
        key = k;
    }
    MPair(const K& k, const V& v){
        key = k;
        value_list.push_back(v);
    }
    MPair(const K& k, const vector<V>& vlist){
        key = k;
        value_list = vlist;
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me){
        outs << print_me.key << ": [";
        for(int i = 0; i < print_me.value_list.size(); i++){
            outs << print_me.value_list[i] << " ";
        }
        outs << "]";
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key <= rhs.key;
    }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key >= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        if(lhs == rhs){
            MPair<K, V> sum(lhs.key, lhs.value_list);
            for(int i = 0; i < rhs.value_list.size(); i++){
                sum.value_list.push_back(rhs.value_list[i]);
            }
            return sum;
        }
        return lhs;
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = nullptr){
            _it = it;
        }
        Iterator operator ++(int unused){
            Iterator it_ptr = Iterator(_it);
            _it++;
            return it_ptr;
        }
        Iterator operator ++(){
            _it++;
            return *this;
        }
        MPair<K, V> operator *(){
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);
    vector<V> &at(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);

    bool is_valid();

    void print_lookup();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

template <typename K, typename V>
MMap<K, V>::MMap(){
    mmap = new BPlusTree<Pair<K, V>>;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin(){
    return MMap<K, V>::Iterator(mmap.begin());
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end(){
    return MMap<K, V>::Iterator(mmap.end());
}

template <typename K, typename V>
int MMap<K, V>::size() const{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K, V>::empty() const{
    return mmap.empty();
}

template <typename K, typename V>
const vector<V>& MMap<K, V>::operator[](const K& key) const{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K, V>::operator[](const K& key){
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v){
    mmap.insert(MPair<K, V>(k, v));
}

template <typename K, typename V>
void MMap<K, V>::erase(const K& key){
    mmap.remove(MPair<K, V>(key));
}

template <typename K, typename V>
void MMap<K, V>::clear(){
    mmap.clear_tree();
}

template <typename K, typename V>
bool MMap<K, V>::contains(const K& key) const{
    return mmap.contains(MPair<K, V>(key));
}

template <typename K, typename V>
vector<V> &MMap<K, V>::get(const K& key){
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
vector<V> &MMap<K, V>::at(const K& key){
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key){
    return MMap<K, V>::Iterator(mmap.find(MPair<K, V>(key)));
}

template <typename K, typename V>
int MMap<K, V>::count(const K& key){
    return 0;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key){
    return mmap.lower_bound(key);
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key){
    return mmap.upper_bound(key);
}

template <typename K, typename V>
bool MMap<K, V>::is_valid(){
    return true;
}

template <typename K, typename V>
void MMap<K, V>::print_lookup(){
    MMap<K, V>::Iterator _it;
    for (_it = mmap.begin(); _it != mmap.end(); _it++){
        cout << *_it << endl;
    }
}

#endif //MULTIMAP_H
