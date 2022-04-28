#ifndef MAP_H
#define MAP_H

#include "bplustree.h"

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        outs << print_me.key << ":" << print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key == rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key < rhs.key;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key <= rhs.key;
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key >= rhs.key;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        if(lhs == rhs){
            Pair<K, V> sum(lhs.key, lhs.value + rhs.value);
            return sum;
        }
        return lhs;
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
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
        Pair<K, V> operator *(){
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

    Map();
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    V& operator[](const K& key);
    const V& operator[](const K& key) const;
    V& at(const K& key);
    const V& at(const K& key) const;


//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);

    bool is_valid(){return map.is_valid();}
    void print_lookup();

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

template <typename K, typename V>
Map<K, V>::Map(){
    key_count = 0;
    map = new BPlusTree<Pair<K, V>>;
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin(){
    return Map<K, V>::Iterator(map.begin());
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end(){
    return Map<K, V>::Iterator(map.end());
}

template <typename K, typename V>
int Map<K, V>::size() const{
    return map.size();
}

template <typename K, typename V>
bool Map<K, V>::empty() const{
    return map.empty();
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key){
    if(!contains(key)){
        key_count++;
    }
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
const V& Map<K, V>::operator[](const K& key) const{
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
V& Map<K, V>::at(const K& key){
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
const V& Map<K, V>::at(const K& key) const{
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
void Map<K, V>::insert(const K& k, const V& v){
    map.insert(Pair<K, V>(k, v));
    key_count++;
}

template <typename K, typename V>
void Map<K, V>::erase(const K& key){
    map.remove(Pair<K, V>(key));
    key_count--;
}

template <typename K, typename V>
void Map<K, V>::clear(){
    map.clear_tree();
    key_count = 0;
}

template <typename K, typename V>
V Map<K, V>::get(const K& key){
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K& key){
    return Map<K, V>::Iterator(map.find(Pair<K, V>(key)));
}

template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V>& target) const{
    return map.contains(target);
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K& key){
    return map.lower_bound(key);
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K& key){
    return map.upper_bound(key);
}

template <typename K, typename V>
void Map<K, V>::print_lookup(){
    Map<K, V>::Iterator _it;
    for (_it = map.begin(); _it != map.end(); _it++){
        cout << *_it << endl;
    }
}

#endif //MAP_H
