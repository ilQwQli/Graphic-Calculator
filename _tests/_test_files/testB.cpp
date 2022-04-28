#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include "../../includes/table/typedefs.h"
#include "../../includes/stl_utils/vector_utilities.h"
#include "../../includes//bplustree/map.h"
#include "../../includes//bplustree/multimap.h"


//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/parser/parser.h"


//------------------------------------------------------------------------------------------
using namespace std;


bool parser_basic(bool debug = false){

  cout<<"\n\n\n------------------------\n\n"<<endl;
  string str;
  char s[300];
  str = "create table student fields last, first, age, major, class";
  strcpy(s, str.c_str());
  Parser parser(s);
  mmap_ss ptree;
  ptree= parser.parse_tree(); 
  cout<<"input: ["<<s<<"]"<<endl<<endl;
  ptree.print_lookup();   //multimap function to print mmap as a table
  cout << endl<<endl;

  str = "insert into student values Jones,\"Sue Ellen\", 20, CS, Fr ";
  strcpy(s, str.c_str());
  parser.set_string(s);
  ptree= parser.parse_tree(); 
  cout<<"input: ["<<s<<"]"<<endl<<endl;
  ptree.print_lookup();
  cout << endl<<endl;

  str = "select * from student where last = Malone and first = Deza or first = \"Mary Ann\"";
  strcpy(s, str.c_str());
  parser.set_string(s);
  ptree= parser.parse_tree(); 
  cout<<"input: ["<<s<<"]"<<endl<<endl;
  ptree.print_lookup();
  cout << endl<<endl;
  vector<string> expected_condition = {"last", "=", "Malone", "and", "first", "=", "Deza", "or", "first", "=", "Mary Ann"};

  if (ptree["condition"] != expected_condition){
      cout << "Test failed!" << endl;
      for(int i = 0; i < expected_condition.size(); i++){
         cout << " " <<expected_condition[i];
      }
      cout << endl << ptree["condition"] << endl;
  }else{
      cout << "Test Success!" << endl;
   }
 
  str = "select lname, fname from student where lname = \"Yao\" and fname = \"Flo\"";
  strcpy(s, str.c_str());
  parser.set_string(s);
  ptree= parser.parse_tree(); 
  cout<<"input: ["<<s<<"]"<<endl<<endl;
  ptree.print_lookup();
  cout << endl<<endl;

  str = "select age, lname, fname from student where fname = \"Mary Ann\" and lname = Yao";
  strcpy(s, str.c_str());
  parser.set_string(s);
  ptree= parser.parse_tree(); 
  cout<<"input: ["<<s<<"]"<<endl<<endl;
  ptree.print_lookup();
  cout << endl<<endl;

  str = "select * from student where (age>=25 or lname = Yao) and (fname = \"Teresa Mae\" or Major = CS)";
  strcpy(s, str.c_str());
  parser.set_string(s);
  ptree= parser.parse_tree(); 
  cout<<"input: ["<<s<<"]"<<endl<<endl;
  ptree.print_lookup();
  cout << endl<< endl;

  cout << "\n\n\n----- DONE -------------\n\n"
       << endl;
  return true;
}


TEST(TEST_TEMPLATE, TestTemplate) {
  bool success = parser_basic();
  EXPECT_EQ(success, true);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
