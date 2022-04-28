#include "sql.h"

SQL::SQL(){
    _parser = Parser();
}

Table SQL::command(string command_list){
    char s[300];
    strcpy(s, command_list.c_str());
    _parser.set_string(s);
    mmap_ss ptree = _parser.parse_tree();
    string command_input = ptree["command"][0];
    ptree.print_lookup();
    if(command_input == "make" || command_input == "create"){
        Table t(ptree["table_name"][0], ptree["fields"]);
    }
    else if(command_input == "insert"){
        Table t(ptree["table_name"][0]);
        t.insert_into(ptree["values"]);
    }
    else if(command_input == "select"){
        Table t(ptree["table_name"][0]);
        vectorstr field = ptree["fields"];
        Table selected = t.select(field, ptree["condition"]);
        _recnos = selected.select_recnos();
        return selected;
    }
    return Table();
}

vector<long> SQL::select_recnos(){
    return _recnos;
}


