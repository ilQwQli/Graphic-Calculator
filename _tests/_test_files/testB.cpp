#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/sql/sql.h"


//------------------------------------------------------------------------------------------

using namespace std;

const vector<string> command_list = {

  "make table employee fields  last, first, dep",
  "insert into employee values Blow, Joe, CS",
  "insert into employee values Johnson, \"Jimmy\", Chemistry",
  "insert into employee values Yang, Bo, CS",
  "insert into employee values \"Jackson\", Billy, Math",
  "insert into employee values Johnson, Billy, \"Phys Ed\"",
  "insert into employee values \"Van Gogh\", \"Jim Bob\", \"Phys Ed\"",
  //----- student table ----------
  "make table student fields fname, lname, major, age",
  "insert into student values Flo, Yao, CS, 20",
  "insert into student values \"Flo\", \"Jackson\",  Math,  21",
  "insert into student values Calvin, Woo, Physics,22",
  "insert into student values \"Anna Grace\", \"Del Rio\",  CS,  22",
  
  "select * from employee",
  "select * from student",
  
  //.................
  //:AND            :
  //.................
//   "select * from student where fname = \"Flo\" and lname = \"Yao\"",
  //.................
  //:OR            :
  //.................
//   "select * from student where fname = Flo or lname = Jackson",
  //.................
  //:OR AND         :
  //.................
//   "select * from student where fname = Flo or major = CS and age <= 23",
  //.................
  //:AND OR AND     :
  //.................
//  "select * from student where (age <30 and major=CS) or (major = Physics and lname = Jackson)",
  //.................
  //:OR AND OR      :
  //.................
//  "select * from student where lname = Yang and major = CS or age < 23 and lname = Jackson",

     "select * from student where ((lname = Jackson) or age > 20)",

     //"fname = Yao and lname = Joe and age < 30 or age > 45 and salary < 200000",
};

const int MAKE_TABLE_COMMANDS = 11;
const int SELECT_COMMANDS = 7;

bool sql_basic(bool debug = false)
{
     SQL sql;
     Table t;
     cout << ">" << command_list[0] << endl;
     sql.command(command_list[0]);
     cout << "basic_test: table created." << endl<<endl;

     for (int i = 0; i < MAKE_TABLE_COMMANDS; i++)
     {
          cout << ">" << command_list[i] << endl;
          sql.command(command_list[i]);
     }

     cout << endl
          << endl;
     for (int i = MAKE_TABLE_COMMANDS; i < command_list.size(); i++)
     {
          cout << "\n>" << command_list[i] << endl;
          if (debug)
               cout<< sql.command(command_list[i])<<endl;
          else
               t = sql.command(command_list[i]);
          cout << t << endl;
          cout << "basic_test: records selected: "<<sql.select_recnos() << endl;
     }

     cout << "----- END TEST --------" << endl;
     return true;
}

// ==============================
// global BAD!
bool debug = false;
// ==============================

TEST(SQL_BASIC, SQLBasic) {
  bool success = sql_basic(debug);
  EXPECT_EQ(success, true);
}

int main(int argc, char **argv) {
  if (argc > 1)
  {
    debug = !strcmp(argv[1], "debug");
  }

  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
