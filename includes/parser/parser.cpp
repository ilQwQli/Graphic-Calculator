#include "parser.h"

int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser(){
    keyword_map();
    make_table();
    for(int i = 0; i < MAX_BUFFER; i++){
        _buffer[i] = '\0';
    }
    _fail = true;
}

Parser::Parser(char* s){
    keyword_map();
    make_table();
    for(int i = 0; i < MAX_BUFFER; i++){
        _buffer[i] = '\0';
        if(i < strlen(s)){
            _buffer[i] = s[i];
        }
    }
    _fail = true;
    _input_q = Queue<string>();
    set_string(_buffer);
}

void Parser::set_string(char* s){
    _ptree.clear();
    STokenizer stk(s);
    Token t;
    stk >> t;
    while(stk.more()){
        if(t.type() < TOKEN_SPACE || t.type() == TOKEN_OPERATOR || t.type() == TOKEN_APOSTROPHE){
            _input_q.push(t.token_str());
        }
        stk >> t;
    }
    get_parse_tree();
}

void Parser::keyword_map(){
    vectorstr keywords = {"stub", "select", "from", "where", "make", "create", "insert", "into", "table", "fields", "values", "sym"};
    for(int i = 0; i < keywords.size(); i++){
        _map.insert(keywords[i], i);
    }
}

bool Parser::get_parse_tree(){
    int state = 0; 
    int col = 0;
    string popped = "";
    while(state != -1 && !_input_q.empty()){
        // cout << _input_q << endl;
        popped = _input_q.pop();
        // cout << "popped: " << popped << endl;
        if(_map.contains(popped)){
            col = _map[popped];
        }else{
            col = SYM;
        }
        // cout << col << endl;
        state = _table[state][col];
        switch(state){
            case START_SELECT:{
                _ptree["command"] += popped;
                break;
            }

            case START_SELECT+1:{
                _ptree["fields"] += popped;
                break;
            }

            case START_SELECT+3:{
                _ptree["table_name"] += popped;
                break;
            }

            case START_SELECT+4:{
                string yes = "yes";
                _ptree["where"] += yes;
                break;
            }

            case START_SELECT+5:{
                _ptree["condition"] += popped;
                break;
            }

            case START_CREATE:{
                _ptree["command"] += popped;
                break;
            }

            case START_CREATE+2:{
                _ptree["table_name"] += popped;
                break;
            }

            case START_CREATE+4:{
                _ptree["fields"] += popped;
                break;
            }

            case START_INSERT:{
                _ptree["command"] += popped;
                break;
            }

            case START_INSERT+2:{
                _ptree["table_name"] += popped;
                break;
            }

            case START_INSERT+4:{
                _ptree["values"] += popped;
                break;
            }

            case START_DROP:{
                _ptree["command"] += popped;
                break;
            }

            case START_DROP+2:{
                _ptree["table_name"] += popped;
                break;
            }

            default:{
                const bool debug = false;
                if(debug){
                    cout << "WTF??? default???" << endl;
                }
                break;
            }
        }
    }
    if(state == -1){
        _ptree.clear();
        _fail = true;
        return false;
    }
    _fail = false;
    return true;
}

mmap_ss Parser::parse_tree(){
    return _ptree;
}

bool Parser::fail(){
    return _fail;
}

void Parser::make_table(){
    init_table(_table);

    //SELECT (row, table, column, state)
    mark_cell(0, _table, SELECT, START_SELECT);
    mark_cell(START_SELECT, _table, SYM, START_SELECT+1);
    mark_cell(START_SELECT+1, _table, SYM, START_SELECT+1);
    mark_cell(START_SELECT+1, _table, FROM, START_SELECT+2);
    mark_cell(START_SELECT+2, _table, SYM, START_SELECT+3);
        //sucess states
    mark_success(_table, START_SELECT+3);

    //WHERE (row, table, column, state)
    mark_cell(START_SELECT+3, _table, WHERE, START_SELECT+4);
    mark_cell(START_SELECT+4, _table, SYM, START_SELECT+5);
    mark_cell(START_SELECT+5, _table, SYM, START_SELECT+5);
        // sucess states
    mark_success(_table, START_SELECT+5);


    //MAKE (row, table, column, state)
    mark_cell(0, _table, CREATE, START_CREATE);
    mark_cell(0, _table, MAKE, START_CREATE);
    mark_cell(START_CREATE, _table, TABLE, START_CREATE+1);
    mark_cell(START_CREATE+1, _table, SYM, START_CREATE+2);
    mark_cell(START_CREATE+2, _table, FIELDS, START_CREATE+3);
    mark_cell(START_CREATE+3, _table, SYM, START_CREATE+4);
    mark_cell(START_CREATE+4, _table, SYM, START_CREATE+4);
        //sucess states
    mark_success(_table, START_CREATE+4);


    //INSERT_INTO (row, table, column, state)
    mark_cell(0, _table, INSERT, START_INSERT);
    mark_cell(START_INSERT, _table, INTO, START_INSERT+1);
    mark_cell(START_INSERT+1, _table, SYM, START_INSERT+2);
    mark_cell(START_INSERT+2, _table, VALUES, START_INSERT+3);
    mark_cell(START_INSERT+3, _table, SYM, START_INSERT+4);
    mark_cell(START_INSERT+4, _table, SYM, START_INSERT+4);
        //sucess states
    mark_success(_table, START_INSERT+4);


    //DROP (row, table, column, state)
    mark_cell(0, _table, DROP, START_DROP);
    mark_cell(START_DROP, _table, TABLE, START_DROP+1);
    mark_cell(START_DROP+1, _table, SYM, START_DROP+2);
        //sucess states
    mark_success(_table, START_DROP+2);
}

