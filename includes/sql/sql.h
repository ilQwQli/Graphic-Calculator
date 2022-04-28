#ifndef SQL_H
#define SQL_H

#include "../parser/parser.h"
#include "../table/table.h"

class SQL{
public:
    SQL();
    Table command(string command_list);
    vector<long> select_recnos();

private:
    Parser _parser;
    vector<long> _recnos;
};

#endif //SQL_H
