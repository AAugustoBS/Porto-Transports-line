//
// Created by Antonio Augusto on 25/01/2022.
//
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#ifndef AED_PROJECT_READFILES_H
#define AED_PROJECT_READFILES_H
using namespace std;


/*
 * Necessary to read cvs files
 */


void splitWord(vector<string> &line, string stops){
    string del = ",";
    int start = 0;
    int end = stops.find(del);
    while (end != -1) {
        line.push_back(stops.substr(start, end - start));
        start = end + del.size();
        end = stops.find(del, start);
    }
    line.push_back(stops.substr(start, end - start));
}

/*
 * This function will read stops.csv file and fill our mapStops with Oporto's bus stops information.
 */
void fillmapStops(map<string,int> &mapStops,Graph &busline){

    fstream line("dataset/stops.csv");
    string stops;
    int idStop = 1; //first id is initialize

    if(!line.is_open()){
        cout<<"failed";
        return;
    }

    getline(line,stops);
    while(getline(line,stops)){
        vector<string> infos;
        splitWord(infos,stops);
        mapStops.insert({infos[0],idStop});
        busline.setInfoNode(idStop,infos);
        idStop++;
    }
}

void readLine(string fileName,string lineName,Graph &busline,map<string,int> mapStops){
    fstream file(fileName);
    string line;

    if(!file.is_open()){
        //cout<<"failed";
        return;
    }
    getline(file,line);
    getline(file,line);
    int firsIdStop = mapStops.find(line)->second;
    while(getline(file,line)){
        int secIdStop = mapStops.find(line)->second;
        busline.setInfoLine(firsIdStop,secIdStop,lineName);
        firsIdStop = secIdStop;
    }

}

void readEdge(Graph &busline,map<string,int> mapStops){

    fstream file("dataset/lines.csv");
    string line;

    while(getline(file,line,',')){
        string fileToOpen = "dataset/line_" + line +"_0.csv";
        //cout<<fileToOpen<<endl;
        getline(file,line);
        readLine(fileToOpen,line,busline,mapStops);
    }

}



#endif //AED_PROJECT_READFILES_H
