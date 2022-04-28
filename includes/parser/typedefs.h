#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <iostream>
#include <vector>
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../queue/MyQueue.h"
#include "../binary_files/file_record.h"

using namespace std;

enum KEY_MAP{
    STUB,
    SELECT,
    FROM,
    WHERE,
    MAKE,
    CREATE,
    INSERT,
    INTO,
    TABLE,
    FIELDS,
    VALUES,
    DROP,
    SYM
};

// parser types
const int START_SELECT = 1;
const int START_CREATE = 10;
const int START_INSERT = 20;
const int START_DROP = 30;

#endif //TYPEDEFS_H_
