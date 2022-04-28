#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>
#include "typedefs.h"
#include "../tokenizer/stokenize.h"

using namespace std;

class Parser{
public:
    Parser();
    Parser(char* s);
    void set_string(char* s);
    void keyword_map();
    bool get_parse_tree();
    mmap_ss parse_tree();
    bool fail();
private:
    void make_table();
    Queue<string> _input_q;
    map_sl _map;
    mmap_ss _ptree;
    char _buffer[MAX_BUFFER];
    static int _table[MAX_ROWS][MAX_COLUMNS];
    bool _fail;
};

#endif //PARSER_H
