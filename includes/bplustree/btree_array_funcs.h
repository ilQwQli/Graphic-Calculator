#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

  //---------------------------------------------------------//
 //----------------------Declaration------------------------//
//---------------------------------------------------------//

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme



  //---------------------------------------------------------//
 //-----------------------Definition------------------------//
//---------------------------------------------------------//

template <class T>
T maximal(const T& a, const T& b){
    //cout << "Entered maximal" << endl;
    if(a > b){
        return a;
    }
    return b;
}

template <class T>
void swap(T& a, T& b){
    //cout << "Entered swap" << endl;
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n){
    //cout << "Entered index_of_maximal" << endl;
    int max = 0;
    for(int i = 0; i < n - 1; i++){
        if(data[i + 1] > data[i]){
            max = i + 1;
        }
    }
    return max;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    //cout << "Entered ordered_insert" << endl;
    int i = 0;
    for(i = n - 1; data[i] > entry && i >= 0; i--){
        data[i + 1] = data[i];
    }
    data[i + 1] = entry;
    n++;
}                         

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    //cout << "Entered first_ge" << endl;
    int i;
    for(i = 0; i < n; i++){
        if(data[i] >= entry){
            return i;               //might be data[i]
        }
    }
    return i;
}  

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    //cout << "Entered attach_item" << endl;
    data[n] = entry;
    n++;
}  

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
    //cout << "Entered insert_item" << endl;
    n++;
    for(int j = n - 1; j > i; j--){
        data[j] = data[j - 1];
    }
    data[i] = entry;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry){
    //cout << "Entered detach_item" << endl;
    entry = data[n - 1];
    n--;
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
    //cout << "Entered delete_item" << endl;
    entry = data[i];
    for(i; i < n; i++){
        data[i] = data[i + 1];
    }
    n--;
}
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    //cout << "Entered merge" << endl;
    for(int i = 0; i < n2; i++){
        data1[n1 + i] = data2[i];
    }
    n1 += n2;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    //cout << "Entered split" << endl;
    int size = n1/2;
    n1 -= size;
    for(int i = 0; i < size; i++){
        data2[i] = data1[n1 + i];
    }
    n2 = size;
}

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){
    //cout << "Entered copy_array" << endl;
    dest_size = src_size;
    for(int i = 0; i < src_size; i++){
        dest[i] = src[i];
    }
}

template <class T>
void print_array(const T data[], int n, int pos){
    //cout << "Entered print_array" << endl;
    if(pos < 0){
        pos = 0;
    }
    cout << "[";
    for(int i = pos; i < n - 1; i++){
        cout << data[i] << "|";
    }
    cout << data[n - 1] << "]" << endl;
}

template <class T>
bool is_gt(const T data[], int n, const T& item){
    //cout << "Entered is_gt" << endl;
    for(int i = 0; i < n; i++){
        if(item <= data[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){
    //cout << "Entered 15" << endl;
    for(int i = 0; i < n; i++){
        if(item > data[i]){
            return false;
        }
    }
    return true;
}

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    outs << "|";
    for(T i: list){
        outs << i << "|";
    }
    outs << endl;
    return outs;
}

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    list.push_back(addme);
    return list;
}
#endif //BTREE_ARRAY_FUNCS_H
