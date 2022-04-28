#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(){
    _buffer[MAX_BUFFER] =  ' ';
    make_table(_table);
    _pos = 0;
}

STokenizer::STokenizer(char str[]){
    strcpy(_buffer, str);
    make_table(_table);
    _pos = 0;
}

bool STokenizer::done(){
    // if(_pos == strlen(_buffer)){
    //     _pos++;
    //     return true;
    // }
    // if(_pos > strlen(_buffer)){
    //     return true;
    // }
    if(_buffer[_pos - 1] == '\0'){
        return true;
    }
    return false;
}

bool STokenizer::more(){
    return !done();
}

STokenizer& operator >> (STokenizer& s, Token& t){
    string str = "";
    bool success = false;
    int start_state = 0;
    int type = -1;
    //cout << "debug before search" << endl;
    if(s.search(DIGITS, s._buffer[s._pos])){
        start_state = START_DOUBLE;
        type = TOKEN_NUMBER;
    }else if(s.search(SPACES, s._buffer[s._pos])){
        start_state = START_SPACES;
        type = TOKEN_SPACE;
    }else if(s.search(ALFA, s._buffer[s._pos])){
        start_state = START_ALPHA;
        type = TOKEN_ALPHA;
    }else if(s.search(PUNC, s._buffer[s._pos])){
        start_state = START_PUNC;
        type = TOKEN_PUNC;
    }else if(s.search(OPERATORS, s._buffer[s._pos])){
        start_state = START_OPERATOR;
        type = TOKEN_OPERATOR;
    }else if(s.search(APOSTROPHE, s._buffer[s._pos])){
        start_state = START_APOSTROPHE;
        type = TOKEN_APOSTROPHE;
    }else{
        start_state = -1;
        type = TOKEN_UNKNOWN;
    }
    //cout << "debug out of search" << endl;
    
    success = s.get_token(start_state, str);
    // cout << "str: " << str << endl;
    t = Token(str, type);
    //cout << "debug after create token" << endl;
    return s;
}

bool STokenizer::search(const char arr[], char key){
    int size = strlen(arr);
    for(int i = 0; i < size; i++){
        if(arr[i] == key){
            return true;
        }
    }
    return false;
}

void STokenizer::set_string(char str[]){
    strcpy(_buffer, str);
    _pos = 0;
}

void STokenizer::make_table(int table[][MAX_COLUMNS]){
    init_table(table);

    /*
    state machine(row, table, column, state)
    */

    //DOUBLE (row, table, column, state)
    mark_cells(0, table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    mark_cell(0, table, '.', 2);        //state [0] --- '.' ------> [2] 
    mark_cells(1, table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    mark_cell(1, table, '.', 2);        //state [1] --- '.' ------> [2] 
    mark_cells(2, table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    mark_cells(3, table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]

    //sucess states
    mark_cell(0, table, 0, 0);
    mark_cell(1, table, 0, 1);
    mark_cell(2, table, 0, 0);
    mark_cell(3, table, 0, 1);

    //SPACES (row, table, column, state)
    mark_cells(4, table, SPACES, 5); 
    mark_cells(5, table, SPACES, 5);

    //sucess states
    mark_cell(4, table, 0, 0);
    mark_cell(5, table, 0, 1);

    //ALPHA (row, table, column, state)
    mark_cells(6, table, ALFA, 7);
    mark_cells(7, table, ALFA, 7);

    //sucess states
    mark_cell(6, table, 0, 0);
    mark_cell(7, table, 0, 1);

    //PUNC (row, table, column, state)
    mark_cells(10, table, PUNC, 11);
    mark_cells(11, table, PUNC, 11);

    //sucess states
    mark_cell(10, table, 0, 0);
    mark_cell(11, table, 0, 1);

    //OPERATORS (row, table, column, state)
    mark_cells(20, table, OPERATORS, 21);
    mark_cells(21, table, OPERATORS, 21);

    //sucess states
    mark_cell(20, table, 0, 0);
    mark_cell(21, table, 0, 1);
    
    //APOSTROPHE (row, table, column, state)
    mark_cells(START_APOSTROPHE, table, APOSTROPHE, START_APOSTROPHE+1);
    mark_cells(START_APOSTROPHE+1, table, SPACES, START_APOSTROPHE+1);
    mark_cells(START_APOSTROPHE+1, table, ALFA, START_APOSTROPHE+1);
    mark_cells(START_APOSTROPHE+1, table, PUNC, START_APOSTROPHE+1);
    mark_cells(START_APOSTROPHE+1, table, OPERATORS, START_APOSTROPHE+1);
    mark_cells(START_APOSTROPHE+1, table, APOSTROPHE, START_APOSTROPHE+2);

    //sucess states
    mark_cell(START_APOSTROPHE, table, 0, 0);
    mark_cell(START_APOSTROPHE+1, table, 0, 0);
    mark_cell(START_APOSTROPHE+2, table, 0, 1);
}

bool STokenizer::get_token(int start_state, string& token){
    if(start_state == -1){
        _pos++;
        return false;
    }

    int current_state = start_state;
    int current_pos = _pos;
    int last_success_state = -1;
    bool success_state = 1;
    string result_token = "";

    for(int i = _pos; i < strlen(_buffer); i++){
        if(_buffer[current_pos] < 0){
            current_state = _table[current_state][_buffer[current_pos] + MAX_COLUMNS];
        }else{
            current_state = _table[current_state][_buffer[current_pos]];
        }
        success_state = _table[current_state][0];
        if(_buffer[current_pos] != '\"'){
            result_token += _buffer[current_pos];
        }
        // cout << "strlen_buffer: " << strlen(_buffer) << endl;
        // cout << "start_state: " << start_state << endl;
        // cout << "current_state: " << current_state << endl;
        // cout << "success_stat_pos : " << current_pos << endl;
        // cout << "_pos : " << _pos << endl;
        // cout << "success_state: " << success_state << endl;
        // cout << "_buffer at current pos: " << _buffer[current_pos] << endl;
        // cout << "result_token: " << result_token << endl << endl;

        if(current_state > 0){
            if(success_state){
                last_success_state = current_state;
                token = result_token;
                _pos = current_pos + 1;
            }
            current_pos++;
        }else if(current_state <= 0){
            if(token != ""){
                return true;
            }
            return false;
        }
    }
    return true;
}

void STokenizer::print(){
    print_table(_table);
}
