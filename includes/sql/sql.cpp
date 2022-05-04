#include "sql.h"

SQL::SQL(){
    _parser = Parser();
}

Table SQL::command(string command_list){
    char s[300] = {};
    ofstream outputFile;
    outputFile.open("outputFile.txt", ios_base::app);
    strcpy(s, command_list.c_str());
    _parser.set_string(s);
    mmap_ss ptree = _parser.parse_tree();
    // ptree.print_lookup();
    string command_input = ptree["command"][0];
    if(command_input == "make" || command_input == "create"){
        Table t(ptree["table_name"][0], ptree["fields"]);
        outputFile << "SQL::run_command: " << command_input << "table: " << ptree["table_name"] << ptree["fields"] << endl;
        outputFile << "SQL::create_table(" << ptree["table_name"] << ptree["fields"]  << ")" << endl;
        outputFile << "Table " << ptree["table_name"] << " created. cols: " << ptree["fields"] << endl;
        outputFile << "\n\n\nSQL: DONE." << endl;
    }
    else if(command_input == "insert"){
        Table t(ptree["table_name"][0]);
        t.insert_into(ptree["values"]);
        outputFile << "\n\n\nSQL: DONE." << endl;
    }
    else if(command_input == "select"){
        Table t(ptree["table_name"][0]);
        vectorstr field = ptree["fields"];
        Table selected = t.select(field, ptree["condition"]);
        _recnos = t.select_recnos();
        outputFile << selected << endl;
        outputFile << "\n\n\nSQL: DONE." << endl;
        outputFile.close();
        return selected;
    }
    outputFile.close();
    return Table();
}

vector<long> SQL::select_recnos(){
    return _recnos;
}


