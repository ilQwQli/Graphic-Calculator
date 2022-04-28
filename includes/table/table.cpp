#include "table.h"

long Table::serial_number = 0;

Table::Table(){
    table_name = "";
    empty = true;
    last_record_number = -1;
    bin_table_name = ".tbl";
}

Table::Table(const string& name, const vectorstr field){
    serial_number++;
    v_field_names = field;
    table_name = name;
    bin_table_name = name + ".tbl";
    last_record_number = -1;

    string txt_file_name = name + ".txt";
    ofstream f_txt(txt_file_name);
    for(long i = 0; i < field.size(); i++){
        f_txt << field[i] << endl;
        field_map[field[i]] += i;
        v_mmap.push_back(new mmap_sl());
    }

    fstream f;
    open_fileW(f, bin_table_name.c_str());
    f.close();
}

Table::Table(const string& name){
    table_name = name;
    bin_table_name = name + ".tbl";
    last_record_number = -1;

    string txt_file_name = name + ".txt";
    fstream f_txt(txt_file_name);
    if(f_txt.is_open()){
        string field = "";
        long i = 0;
        while(getline(f_txt, field)){
            v_field_names.push_back(field);
            field_map[field] += i;
            i++;
        }
    }
    f_txt.close();

    fstream f;
    FileRecord r;
    open_fileRW(f, bin_table_name.c_str());
    vectorstr vs;
    f.seekg(0, f.end);
    long file_length = f.tellg();
    long total_record_num = file_length / sizeof(r._record) - 1;
    for(int i = 0; i <= total_record_num; i++){
        r.read(f, i);
        last_record_number++;
        records_selected.push_back(last_record_number);
        for(int j = 0; j < v_field_names.size(); j++){
            v_mmap.push_back(new mmap_sl());
            (*v_mmap[j])[r._record[j]].push_back(last_record_number);
        }
        vs.clear();
    }
    f.close();
}

void Table::insert_into(vectorstr vs){
    if(file_exists(bin_table_name.c_str())){
        for(int j = 0; j < v_field_names.size(); j++){
            v_mmap.push_back(new mmap_sl());
        }
        fstream f;
        open_fileRW(f, bin_table_name.c_str());
        FileRecord r(vs);
        r.write(f);
        last_record_number++;
        records_selected.push_back(last_record_number);
        for(int i = 0; i < vs.size(); i++){
            (*v_mmap[i])[vs[i]].push_back(last_record_number);
        }
        f.close();
    }
}

Table Table::select(vectorstr types, string type_input, string op, string input){
    records_selected.clear();
    if(op == "="){
        records_selected = (v_mmap[field_map[type_input]]) -> at(input);
    }else if(op == ">="){
        mmap_sl::Iterator begin = v_mmap[field_map[type_input]] -> lower_bound(input);
        mmap_sl::Iterator end = v_mmap[field_map[type_input]] -> end();
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }else if(op == ">"){
        mmap_sl::Iterator begin = v_mmap[field_map[type_input]] -> upper_bound(input);
        mmap_sl::Iterator end = v_mmap[field_map[type_input]] -> end();
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }else if(op == "<="){
        mmap_sl::Iterator begin = v_mmap[field_map[type_input]] -> begin();
        mmap_sl::Iterator end = v_mmap[field_map[type_input]] -> upper_bound(input);
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }else if(op == "<"){
        mmap_sl::Iterator begin = v_mmap[field_map[type_input]] -> begin();
        mmap_sl::Iterator end = v_mmap[field_map[type_input]] -> lower_bound(input);
        for(; begin != end; begin++){
            for(int i = 0; i < (*begin).value_list.size(); i++){
                records_selected.push_back((*begin).value_list[i]);
            }
        }
    }
    
    Table t("selected_" + table_name + to_string(serial_number), types);
    fstream f;
    FileRecord r;
    open_fileRW(f, bin_table_name.c_str());
    vectorstr vs;

    for(int i = 0; i < records_selected.size(); i++){
        r.read(f, records_selected[i]);
        for(int j = 0; j < v_field_names.size(); j++){
            vs.push_back(r._record[field_map[types[j]]]);
        }
        t.insert_into(vs);
        vs.clear();
    }
    f.close();
    return t;
}

Table Table::select(vectorstr types, Queue<Token *> post){
    if(!post.empty()){
        RPN rpn(post);
        records_selected = rpn.eval(field_map, v_mmap);
    }
    
    Table t("selected_" + table_name + to_string(serial_number), types);
    fstream f;
    FileRecord r;
    open_fileRW(f, bin_table_name.c_str());
    vectorstr vs;
    
    for(int i = 0; i < records_selected.size(); i++){
        r.read(f, records_selected[i]);
        for(int j = 0; j < types.size(); j++){
            vs.push_back(r._record[field_map[types[j]]]);
        }
        t.insert_into(vs);
        vs.clear();
    }
    f.close();
    return t;
}

Table Table::select(vectorstr types, vector<string> infix){
    if(types[0] == "*"){
        types.clear();
        for(int i = 0; i < v_field_names.size(); i++){
            types.push_back(v_field_names[i]);
        }
    }
    if(infix.size() == 0){
        Queue<Token*> empty_q;
        return select(types, empty_q);
    }

    Queue<Token*> infix_q;
    ShuntingYard sy;
    infix_q = sy.tk_vector(infix);
    sy.set_infix(infix_q);
    Queue<Token*> postfix_q = sy.postfix();
    return select(types, postfix_q);
}

Table Table::select_all(){
    records_selected.clear();
    for(int i = 0; i <= last_record_number; i++){
        records_selected.push_back(i);
    }

    Table t(table_name + to_string(serial_number), v_field_names);
    fstream f;
    FileRecord r;
    open_fileRW(f, bin_table_name.c_str());
    vectorstr vs;
    for(int i = 0; i <= last_record_number; i++){
        r.read(f, i);
        for(int j = 0; j < v_field_names.size(); j++){
            vs.push_back(r._record[j]);
        }
        t.insert_into(vs);
        vs.clear();
    }
    f.close();
    return t;
}

vector<long> Table::select_recnos(){
    return records_selected;
}

ostream& operator<<(ostream& outs, const Table& t){
    outs << "Table name: " << t.bin_table_name << ", records: " << t.last_record_number + 1 << endl;
    outs << setw(25) << "record";
    for(int i = 0; i < t.v_field_names.size(); i++){
        outs << setw(25) << t.v_field_names[i];
    }
    outs << endl;

    fstream f;
    FileRecord r;
    r._size = t.v_field_names.size();
    open_fileRW(f, t.bin_table_name.c_str());
    for(int i = 0; i < t.records_selected.size(); i++){    
        r.read(f, t.records_selected[i]);
        outs << setw(25) << i << r << endl;
    }
    f.close();
    return outs;
}
