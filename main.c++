#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
fstream db_file;
vector<string> commands={"create","select","delete","insert","update"};
vector<int> argu={3,2,3,3,3};
vector<string> types={"INT","TEXT","FLOAT"};
class value{
    private:
        int type;
        string data;
        union converted_data
        {
            int int_data;
            float float_data;
        };
        converted_data c;
    public:
        void convert_data_type(int type,string data,converted_data &c){
            if(type==1){
                c.int_data=stoi(data);
            }else if(type==2){
                this->data=data;
            }else if (type==3)
            {
                c.float_data=stof(data);
            }
        }
        value(int type,string data){
            this->type=type;
            this->data=data;
            convert_data_type(type,data,this->c);
        }
        int getter(){
            return c.int_data;
        }
        int gettype(){
            return type;
        }
        string getdata(){
            return data;
        }
        void display(){
            if(type==1){
                cout<<c.int_data;
            }else if(type==2){
                cout<<data;
            }else if(type==3){
                cout<<c.float_data;
            }
        }
};
class column{
    public:
        string column_name;
        int data_type;
        column(string column_name,int data_type){
            this->column_name=column_name;
            this->data_type=data_type;
        }
        column(){}
};
class rows{
    private:
        vector<value> data;
    public:
        static int count;
        rows(vector<column> columns,vector<string> data){
            for(int i=0;i<data.size();i++){
                value v(columns[i].data_type,data[i]);
                this->data.push_back(v);
            }
        }
        void display(){
            for(int i=0;i<data.size();i++){
                data[i].display();
                cout<<" ";
            }
            cout<<endl;
        }
        int getid(int c){
            return data[c].getter();
        }
        void setdata(vector<string> newdata,int idindex){
            int k=0;
            for(int i=0;i<data.size();i++){
                if(i==idindex){
                    continue;
                }
                data[i]=value(data[i].gettype(),newdata[k]);
                k++;
            }
        }
        vector<string> getdata(){
            vector<string> get_data;
            for(int i=0;i<data.size();i++){
                get_data.push_back(data[i].getdata());
            }
            return get_data;
        }
};
int rows::count=0;
class table{
    public:
        string table_name;
        vector<column> columns;
        vector<rows> data;

        table(string table_name,vector<column> columns){
            this->table_name=table_name;
            this->columns=columns;
        }
        table(){}
};
int data_type(string type){
    if(type=="int"||type=="INT"){
        return 1;
    }else if(type=="text"||type=="TEXT"){
        return 2;
    }else if(type=="float"||type=="FLOAT"){
        return 3;
    }else{
        return 0;
    }
}
bool check_type(string s,int type){
    if(type==1){
        try{
            size_t p;
            stoi(s,&p);
            return p==s.size();
        }catch(...){
            return false;
        }
    }
    if(type==2){
        return true;
    }
    if(type==3){
        try{
            size_t p;
            stof(s,&p);
            return p==s.size();
        }catch(...){
            return false;
        }
    }
    return false;
}
void load_database(vector<table> &tables){
    db_file.open("voiddb.vdb",ios::in);
    if(db_file.is_open()){
        bool table_valid=true;
        bool table_started=false;
        bool column_started=false;
        string line;
        string current_table;
        vector<column> current_column;
        vector<rows> current_row;
        while(getline(db_file,line)){
            if(line.empty()) continue;
            string check="";
            int i=0;
            while(i<line.size()&&line[i]!='|'){
                check+=line[i];
                i++;
            }
            if(check=="TABLE"){
                table_valid=true;
                table_started=true;
                line.erase(0,6);
                current_column.clear();
                current_row.clear();
                current_table=line;
            }else if(check=="COLUMN"){
                if(!table_started){
                    cout<<"void_db> database file corrupted: unexpected COLUMN\n";
                    continue;
                }
                line.erase(0,7);
                string name="";
                int i=0;
                while(i<line.size()&&line[i]!='|'){
                    name+=line[i];
                    i++;
                }
                line.erase(0,i+1);
                string d_t="";
                int j=0;
                while(j<line.size()&&line[j]!='|'){
                    d_t+=line[j];
                    j++;
                }
                int d=data_type(d_t);
                if((name.empty()||d==0)||(line.find('|')!=string::npos)){
                    table_valid=false;
                }else{
                    bool can_push=true;
                    for(int i=0;i<current_column.size();i++){
                        if(name==current_column[i].column_name){
                            can_push=false;
                            break;
                        }
                    }
                    if(can_push){
                        column c;
                        c.column_name=name;
                        c.data_type=d;
                        current_column.push_back(c);
                        column_started=true;
                    }else{
                        cout<<"void_db> database file corrupted: duplicate column\n";
                        table_valid=false;
                    }
                }
            }else if(check=="ROW"){
                if(!table_started){
                    cout<<"void_db> database file corrupted: unexpected ROW\n";
                    continue;
                }
                if(!column_started){
                    cout<<"void_db> database file corrupted: ROW before COLUMN\n";
                    table_valid=false;
                    continue;
                }
                line.erase(0,4);
                if(line.empty()||line[line.size()-1]!='|'){
                    cout<<"void_db> database file corrupted: invalid row\n";
                    continue;
                }
                vector<string> row_data;
                for(int i=0;i<line.size();){
                    string val="";
                    while(i<line.size()&&line[i]!='|'){
                        val+=line[i];
                            i++;
                    }
                    if(!val.empty()){
                        row_data.push_back(val);
                    }
                    if(i<line.size()){
                        i++;
                    }
                }
                bool valid=true;
                if(row_data.size()!=current_column.size()){
                    valid=false;
                }else{
                    for(int i=0;i<row_data.size();i++){
                        if(!check_type(row_data[i],current_column[i].data_type)){
                            valid=false;
                            break;
                        }
                    }
                }
                if(valid){
                    bool duplicate=false;
                    for(int i=0;i<current_row.size();i++){
                        if(current_row[i].getid(0)==stoi(row_data[0])){
                            duplicate=true;
                            break;
                        }
                    }
                    if(duplicate){
                        cout<<"void_db> database file corrupted: duplicate id\n";
                    }else{
                        rows row(current_column,row_data);
                        current_row.push_back(row);
                    }
                }else{
                    cout<<"void_db> database file corrupted: invalid row\n";
                    table_valid=false;
                }
            }else if(line=="END"){
                if(!table_started){
                    cout<<"void_db> database file corrupted: unexpected END\n";
                    continue;
                }
                if(current_column.empty()||current_column[0].column_name!="id"||current_column[0].data_type!=1){
                    table_valid=false;
                }
                if(table_valid){
                    bool can_push=true;
                    for(int i=0;i<tables.size();i++){
                        if(current_table==tables[i].table_name){
                            can_push=false;
                            break;
                        }
                    }
                    if(can_push){
                        table t;
                        t.table_name=current_table;
                        t.columns=current_column;
                        t.data=current_row;
                        tables.push_back(t);
                    }else{
                        cout<<"void_db> database file corrupted: duplicate table\n";
                    }
                }else{
                    cout<<"void_db> database file corrupted: invalid table\n";
                }
                table_started=false;
            }else{
                cout<<"void_db> database file corrupted: unknown statement\n";
                if(table_started){
                    table_valid=false;
                }
            }
        }
        if(table_started){
            cout<<"void_db> database file corrupted: missing END\n";
        }
        db_file.close();
    }else{
        db_file.open("voiddb.vdb",ios::out);
        db_file.close();
    }
}
void save_database(vector<table> tables){
    db_file.open("voiddb.vdb",ios::out|ios::trunc);
    for(int i=0;i<tables.size();i++){
        db_file<<"TABLE|"<<tables[i].table_name<<"\n";
        for(int j=0;j<tables[i].columns.size();j++){
            db_file<<"COLUMN|"<<tables[i].columns[j].column_name<<"|"<<types[(tables[i].columns[j].data_type)-1]<<"\n";
        }
        for(int k=0;k<tables[i].data.size();k++){
            db_file<<"ROW|";
            for(int l=0;l<tables[i].data[k].getdata().size();l++){
                db_file<<tables[i].data[k].getdata()[l]<<"|";
            }
            db_file<<"\n";
        }
        db_file<<"END\n";
    }
    db_file.close();
}
vector<string> praseing(string input){
    vector<string> prase;
    int size=input.length();
    int i=0;
    while(i<size){
        string s="";
        while(i<size && input[i]!=' '){
            s+=input[i];
            i++;
        }
        if(i<size){
            i++;
        }
        prase.push_back(s);
    }
    return prase;
}
vector<column> create_column(vector<string> prase){
    vector<column>columns;
    for(int i=0;i<prase.size();i+=2){
        column c1(prase[i],data_type(prase[i+1]));
        columns.push_back(c1);
    }
    return columns;
}
void create(string name,vector<string> prase,vector<table> &tables){
    vector<column>columns=create_column(prase);
    table t1(name,columns);
    tables.push_back(t1);
}
bool insert(vector<string> prase,vector<table> &tables){
    int i=0;
    while(i<tables.size()){
        if(tables[i].table_name==prase[1]){
            break;
        }
        i++;
    }
    int id_column=0;
    for(int j=0;j<tables[i].columns.size();j++){
        if(tables[i].columns[j].column_name=="id"){
            id_column=j;
            break;
        }
    }
    for(int j=0;j<tables[i].columns.size();j++){
        int type=tables[i].columns[j].data_type;
        if(!check_type(prase[j+2],type)){
            cout<<"void_db> invalid data type for \""<<tables[i].columns[j].column_name<<"\""<<endl;
            return false;
        }
    }
    for(int j=0;j<tables[i].data.size();j++){
        if(tables[i].data[j].getid(id_column)==stoi(prase[id_column+2])){
            cout<<"void_db> dublicate id found"<<endl;
            return false;
        }
    }
    prase.erase(prase.begin(),prase.begin()+2);
    rows r1(tables[i].columns,prase);
    tables[i].data.push_back(r1);
    return true;
}
void select(vector<string> prase,vector<table> &tables){
    int i=0;
    while(i<tables.size()){
        if(tables[i].table_name==prase[1]){
            break;
        }
        i++;
    }
    for(int j=0;j<tables[i].columns.size();j++){
        cout<<"| "<<tables[i].columns[j].column_name<<" ";
    }
    cout<<"|"<<endl;
    for(int j=0;j<tables[i].data.size();j++){
        tables[i].data[j].display();
    }
}
bool del(vector<string> prase,vector<table> &tables){
    int i=0;
    while(i<tables.size()){
        if(tables[i].table_name==prase[1]){
            break;
        }
        i++;
    }
    if(i<tables.size()){
        int c=0;
        for(int j=0;j<tables[i].columns.size();j++){
            if(tables[i].columns[j].column_name=="id"){
                c=j;
                break;
            }
        }
        for(int j=0;j<tables[i].data.size();j++){
            if(tables[i].data[j].getid(c)==stoi(prase[2])){
                tables[i].data.erase(tables[i].data.begin()+j);
                return true;
            }
        }
        cout<<"void_db> row not found"<<endl;
        return false;
    }
    cout<<"void_db> table not found"<<endl;
    return false;
}
bool update(vector<string> prase,vector<table> &tables){
    int i=0;
    while(i<tables.size()){
        if(tables[i].table_name==prase[1]){
            break;
        }
        i++;
    }
    if(i<tables.size()){
        int c=0;
        for(int j=0;j<tables[i].columns.size();j++){
            if(tables[i].columns[j].column_name=="id"){
                c=j;
                break;
            }
        }
        for(int j=0;j<tables[i].columns.size();j++){
            int type=tables[i].columns[j].data_type;

            if(!check_type(prase[j+2],type)){
                cout<<"void_db> invalid data type for \""<<tables[i].columns[j].column_name<<"\""<<endl;
                return false;
            }
        }
        for(int j=0;j<tables[i].data.size();j++){
            if(tables[i].data[j].getid(c)==stoi(prase[2])){
                prase.erase(prase.begin(),prase.begin()+3);

                tables[i].data[j].setdata(prase,c);

                return true;
            }
        }
        cout<<"void_db> row not found"<<endl;
        return false;
    }
    cout<<"void_db> table not found"<<endl;
    return false;
}
bool validate(vector<string> prase,vector<table> tables){
    int c=-1;
    for(int i=0;i<commands.size();i++){
        if(prase[0]==commands[i]){
            c=i;
            break;
        }
    }
    if(c==-1){
        cout<<"void_db> Invalid command"<<endl;
        return false;
    }
    if(c==0){
        if(prase.size()<argu[c]){
            cout<<"void_db> argument mismatch"<<endl;
            return false;
        }
        for(int i=0;i<tables.size();i++){
            if(prase[1]==tables[i].table_name){
                cout<<"void_db> table already exists"<<endl;
                return false;
            }
        }
        if(prase.size()%2!=0){
            cout<<"void_db> invalid column definition"<<endl;
            return false;
        }
        for(int i=3;i<prase.size();i+=2){
            if(!data_type(prase[i])){
                cout<<"void_db> invalid data type"<<endl;
                return false;
            }
        }
        bool idfound=false;
        int id_index=0;
        for(int i=2;i<prase.size();i++){
            if(prase[i]=="id"){
                idfound=true;
                id_index=i;
                break;
            }
        }
        if(!idfound){
            cout<<"void_db> please include \"id\" column"<<endl;
            return false;
        }
        if(prase[id_index+1]!="int"){
            cout<<"void_db> invalid data type for \"id\""<<endl;
            return false;
        }
        for(int i=2;i<prase.size();i+=2){
            for(int j=i+2;j<prase.size();j+=2){
                if(prase[i]==prase[j]){
                    cout<<"void_db> duplicate column"<<endl;
                    return false;
                }
            }
        }
        return true;
    }
    if(c==1||c==2){
        if(prase.size()!=argu[c]){
            cout<<"void_db> argument mismatch"<<endl;
            return false;
        }
    }
    if(c==3){
        if(prase.size()<argu[c]){
            cout<<"void_db> argument mismatch"<<endl;
            return false;
        }
    }
    if(c==4){
        if(prase.size()<argu[c]){
            cout<<"void_db> argument mismatch"<<endl;
            return false;
        }
    }
    if(c==1||c==2||c==3||c==4){
        int i=0;
        while(i<tables.size()){
            if(tables[i].table_name==prase[1]){
                break;
            }
            i++;
        }
        if(i>=tables.size()){
            cout<<"void_db> Table not found"<<endl;
            return false;
        }
        if(c==3){
            if(prase.size()-2!=tables[i].columns.size()){
                cout<<"void_db> column count mismatch"<<endl;
                return false;
            }
        }
        if(c==4){
            if(prase.size()-3!=tables[i].columns.size()-1){
                cout<<"void_db> column count mismatch"<<endl;
                return false;
            }
        }
    }
    return true;
}
int main(){
    string command;
    vector<table> tables;
    load_database(tables);
    while(command!="exit"){
        cout<<"void_db> ";
        getline(cin,command);
        vector<string> p=praseing(command);
        if(p.empty()){
            continue;
        }
        if(p[0]!="exit"){
            bool valid=validate(p,tables);
            if(!valid){
                continue;
            }
        }
        if(p[0]=="create"){
            string name=p[1];
            p.erase(p.begin(),p.begin()+2);
            create(name,p,tables);
            save_database(tables);
            cout<<"void_db> created"<<endl;
        }else if(p[0]=="insert"){
            if(insert(p,tables)){
                save_database(tables);
                cout<<"void_db> inserted"<<endl;
            }else{
                cout<<"void_db> something went wrong"<<endl;
            }
        }else if(p[0]=="select"){
            select(p,tables);
        }else if(p[0]=="delete"){
            if(del(p,tables)){
                save_database(tables);
                cout<<"void_db> deleted"<<endl;
            }else{
                cout<<"void_db> something went wrong"<<endl;
            }
        }else if(p[0]=="update"){
            if(update(p,tables)){
                save_database(tables);
                cout<<"void_db> updated"<<endl;
            }else{
                cout<<"void_db> something went wrong"<<endl;
            }
        }
    }
}