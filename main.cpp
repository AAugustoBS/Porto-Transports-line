#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readFiles();
void readLines(string name);
int main() {

    readFiles();


}

void readFiles(){
    std::fstream file("dataset/lines.csv");
    string code;
    string sFile;
    if(!file.is_open()){
        cout<<"failed";
        return;
    }

    while(getline(file,code,',')){
        getline(file,sFile);
        string aux = "dataset/LINE_" + code + "_0.csv";
        readLines(aux);

    }
}


void readLines(string name){
    fstream file(name);

    string rFile;

    if(!file.is_open()){
        cout<<"failed\n";
        return;
    }
    while(getline(file,rFile)){
        cout<<rFile<<endl;
    }
}