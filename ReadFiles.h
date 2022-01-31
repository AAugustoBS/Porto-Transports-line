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

/**
 * split a given string into substrings and save that information in a vector
 * @param line all information that belongs to one line
 * @param stops information that will be splited
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
/**
 * Read stops.csv file and fill the map that maps stops and numbers
 * @param mapStops map
 * @param busline graph with information about lines and stops
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
/**
 * Read all lines files and save that information in the graph
 * @param fileName name of the file
 * @param lineName name of the line
 * @param busline graph with information about the lines and stops
 * @param mapStops
 */
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
/**
 * read the lines file
 * @param busline graph with information about lines and stops
 * @param mapStops map with information about stops and corresponding node number
 */
void readEdge(Graph &busline,map<string,int> mapStops){

    fstream file("dataset/lines.csv");
    string line;

    while(getline(file,line,',')){
        string fileToOpen = "dataset/line_" + line +"_0.csv";
        string fileToOpen2 = "dataset/line_" + line +"_1.csv";
        //cout<<fileToOpen<<endl;
        getline(file,line);
        readLine(fileToOpen,line,busline,mapStops);

        readLine(fileToOpen2,line,busline,mapStops);
    }
}
#endif //AED_PROJECT_READFILES_H
