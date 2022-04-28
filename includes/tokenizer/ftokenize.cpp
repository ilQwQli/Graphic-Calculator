#include "ftokenize.h"

FTokenizer::FTokenizer(char* fname){
    _f.open(fname);
    _stk = STokenizer();
    if(_f.fail()){
        cout << "cannot open file: " << fname << endl;
        exit(1);
    }
    _pos = 0;
    _blockPos = 0;
    _more = true;
}

Token FTokenizer::next_token(){
    if(!_stk.more() && _more){
        bool state = get_new_block();
        cout << "debug out of get_new_block" << endl;
    }
    
    Token t;
    if(_more){
        cout << "debug before stk >> t" << endl;
        _stk >> t;
    }
    return t;
}

bool FTokenizer::more(){
    return _more;
}

int FTokenizer::pos(){
    return _pos;
}

int FTokenizer::block_pos(){
    return _blockPos;
}

FTokenizer& operator >> (FTokenizer& f, Token& t){
    if(f._more){
        t = f.next_token();
        f._pos++;
    }
    return f;
}

bool FTokenizer::get_new_block(){
    if(_f.eof()){
        _more = false;
        _f.close();
        cout << "*** END OF FILE ***" << endl; 
        return false;
    }
    if(_more){
        _blockPos++;
        cout << "----- New Block ---------------------[ " << MAX_BLOCK - 1 << "] bytes" << endl;
        char block[MAX_BUFFER];
        cout << "debug1" << endl;
        _f.read(block, MAX_BLOCK);
        cout << "debug2" << endl;
        block[_f.gcount()] = '\0';
        cout << "debug3" << endl;
        _stk.set_string(block);
        cout << "debug4" << endl;
        return true;
    }
    return false;
}
