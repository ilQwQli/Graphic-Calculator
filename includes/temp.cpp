// const char* menu_1 = "=====Option Menu====="
//                      "\n[1]Read sample file and display."
//                      "\n[2]Read from a file name and display."
//                      "\n[3]Manual input."
//                      "\n[4]Exit";

// const char* menu_2 = "<CREATE | MAKE> : {  <create | make> table <TABLE_NAME> fields <FIELD_NAME> [, <FIELD_NAME>...]  }"
//                         "\n<INSERT> : { insert <INTO> <TABLE_NAME> values <VALUE> [, <VALUE>...]      }"
//                         "\n<SELECT> : {  select <* | FIELD_NAME> [, ,FIELD_NAME>...]"
//                         "\n					from <TABLE_NAME>"
//                         "\n					where <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>"
//                         "\n						[<LOGICAL_OPERATOR>"
//                         "\n							<FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>...]"
//                         "\n			}"

//                         "\n<VALUE>  : A string of alphanumeric characters, or a string of alphanumeric"
//                         "\n            characters and spaces enclosed by double quotation marks:"
//                         "\n            \"Jean Luise\", Finch, 1923"
//                         "\n<RELATIONAL OPERATOR> : [ = | > | < | >= | <= ]"
//                         "\n<LOGICAL OPERATOR>    : [and | or]";

// void file_command(string fileName){
//     //freopen("OutputFile.txt","w",stdout);

//     int command_counter = 0;
//     string line;
//     fstream batch_file;
//     open_fileRW(batch_file, fileName.c_str());
//     if(batch_file.is_open()){
//         SQL sql;
//         long file_length = batch_file.tellg();
//         while(!batch_file.eof()){
//             getline(batch_file, line);
//             if(line[0] != '/' && line.size() > 1){
//                 cout << "[" << command_counter << "] " << line << endl;
//                 sql.command(line);
//                 command_counter++;
//             }else{
//                 cout << line << endl;
//             }
//         }
//     }else{
//         cout << "WTF" << endl;
//     }
//     //fclose(stdout);
//     batch_file.close();

//     // fstream outputFile;
//     // open_fileRW(outputFile, fileName.c_str());
//     // if(outputFile.is_open()){
//     //     string output_line;
//     //     long file_length = outputFile.tellg();
//     //     while(!outputFile.eof()){
//     //         getline(outputFile, line);
//     //         cout << output_line << endl;
//     //     }
//     // }
//     // outputFile.close();
// }

// void menu_input(){
//     int userInput = 0;
//     string str;
//     cout << menu_1 << endl;
//     cin >> userInput;
//     switch(userInput){
//         case 1:{
//             file_command("_!select.txt");
//             break;
//         }

//         case 2:{
//             cout << "Enter the file name: " << endl;
//             getline(cin, str);
//             file_command(str);
//             break;
//         }

//         case 3:{
//             cout << menu_2 << endl << endl;
//             cout << "Enter your input: ";
//             cin >> str;
//             SQL sql;
//             cout << sql.command(str) << endl;
//             break;
//         }

//         case 4:{
//             cout << "Exiting Program....." << endl;
//             exit(0);
//             break;
//         }

//         default:{
//             cout << "ERROR! UNKNOWN INPUT!!!" << endl;
//             break;
//         }
//     }
// }

// int main(int argv, char** argc) {
//     cout << "\n\n"
//          << endl;
//     bool run = true;
//     // menu_input();
//     file_command("_!select.txt");

//     cout << "\n\n\n=====================" << endl;
//     return 0;
// }
