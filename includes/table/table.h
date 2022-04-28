#ifndef TABLE_H
#define TABLE_H

#include "typedefs.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"

class Table{
public:
    Table();
    Table(const string& name, const vectorstr field);
    Table(const string& name);

    void insert_into(vectorstr vs);
    Table select(vectorstr types, string type_input, string op, string input);
    Table select(vectorstr types, Queue<Token *> post);
    Table select(vectorstr types, vector<string> infix);
    Table select_all();
    vector<long> select_recnos();

    friend ostream& operator<<(ostream& outs, const Table& t);
private:
    string table_name;              //table name or file name
    string bin_table_name;
    vectorstr v_field_names;        //header name
    vector<mmap_sl*> v_mmap;         //input map???
    map_sl field_map;              //field_name, 
    bool empty;                     //file status
    static long serial_number;      //file number?
    long last_record_number;        //current recording number
    vector<long> records_selected;
};

#endif // TABLE_H
