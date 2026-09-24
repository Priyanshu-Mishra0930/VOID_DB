#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> commands={"create","select","delete","insert","update"};
vector<int> argu={3,2,3,3,3};
class rows{
    private:
        vector<string> data;

    public:
        static int count;

        rows(vector<string> data){
            count++;
            this->data=data;
        }
        void display(){
            for(int i=0;i<data.size();i++){
                cout<<data[i]<<" ";
            }
            cout<<endl;
        }

        int getid(int c){
            return stoi(data[c]);
        }

        void setdata(vector<string> newdata,int idindex){
            int k=0;

            for(int i=0;i<data.size();i++){
                if(i==idindex){
                    continue;
                }

                data[i]=newdata[k];
                k++;
            }
        }
};

int rows::count=0;

class table{
    public:
        string table_name;
        vector<string> columns;
        vector<rows> data;

        table(string table_name,vector<string> columns){
            this->table_name=table_name;
            this->columns=columns;
        }
};

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

void create(string name,vector<string> colmuns,vector<table> &tables){
    table t1(name,colmuns);
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

    if(i<tables.size()){
        if(prase.size()-2==tables[i].columns.size()){
            prase.erase(prase.begin(),prase.begin()+2);

            rows r1(prase);

            tables[i].data.push_back(r1);

            return true;
        }else{
            cout<<"void_db> column count mismatch"<<endl;
            return false;
        }
    }

    cout<<"void_db> table not found"<<endl;
    return false;
}

void select(vector<string> prase,vector<table> &tables){
    int i=0;

    while(i<tables.size()){
        if(tables[i].table_name==prase[1]){
            break;
        }
        i++;
    }

    if(i<tables.size()){
        for(int j=0;j<tables[i].data.size();j++){
            tables[i].data[j].display();
        }
    }else{
        cout<<"void_db> table not found"<<endl;
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
            if(tables[i].columns[j]=="id"){
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
        if(prase.size()-3!=tables[i].columns.size()-1){
            cout<<"void_db> column count mismatch"<<endl;
            return false;
        }

        int c=0;

        for(int j=0;j<tables[i].columns.size();j++){
            if(tables[i].columns[j]=="id"){
                c=j;
                break;
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
        bool idfound=false;
        for(int i=2;i<prase.size();i++){
            if(prase[i]=="id"){
                idfound=true;
                break;
            }
        }
        if(!idfound){
            cout<<"void_db> please include \"id\" column"<<endl;
            return false;
        }
        for(int i=2;i<prase.size();i++){
            for(int j=i+1;j<prase.size();j++){
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
    }else{
        if(prase.size()<argu[c]){
            cout<<"void_db> argument mismatch"<<endl;
            return false;
        }
    }
    bool found=false;
    for(int i=0;i<tables.size();i++){
        if(prase[1]==tables[i].table_name){
            found=true;
            break;
        }
    }
    if(!found){
        cout<<"void_db> Table not found"<<endl;
        return false;
    }
    return true;
}

int main(){
    string command;
    vector<table> tables;

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

            cout<<"void_db> created"<<endl;

        }else if(p[0]=="insert"){

            if(insert(p,tables)){
                cout<<"void_db> inserted"<<endl;
            }

        }else if(p[0]=="select"){

            select(p,tables);

        }else if(p[0]=="delete"){

            if(del(p,tables)){
                cout<<"void_db> deleted"<<endl;
            }

        }else if(p[0]=="update"){

            if(update(p,tables)){
                cout<<"void_db> updated"<<endl;
            }
        }
    }
}