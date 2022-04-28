#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!+-*%&|";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char PUNC[] = "?.,:;'`~!";
const char APOSTROPHE[] = "\"";
const char PARENTHESIS[] = "()";
const int START_DOUBLE = 0;
const int START_SPACES = 4;
const int START_ALPHA = 6;
const int START_OPERATOR = 20;
const int START_PUNC = 10;
const int START_APOSTROPHE = 30;
const int START_PARENTHESIS = 40;

//token types:
const int TOKEN_NUMBER = 1;
const int TOKEN_ALPHA = 2;
const int TOKEN_SPACE = 3;
const int TOKEN_OPERATOR = 4;
const int TOKEN_PUNC = 5;
const int TOKEN_APOSTROPHE = 6;
const int TOKEN_PARENTHESIS = 7;

const int TOKEN_UNKNOWN = -1;
const int TOKEN_END = -2;

const int TOKEN_STRING = 100;
const int LOGICAL = 101;
const int RELATIONAL = 102;

const int LEFTPAREN = 110;
const int RIGHTPAREN = 111;


#endif //CONSTANTS_H
