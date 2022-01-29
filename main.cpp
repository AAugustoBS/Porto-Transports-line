#include <iostream>
#include <string>
#include <map>
#include "graph.h"
#include "AuxFunctions.h"
#include "ReadFiles.h"
#include "Application1.h"
#include "Application.h"
using namespace std;


int main() {

    //Lembrar da direção
    Graph busLine(2487,true);
    map<string,int> mapStops;
    fillmapStops(mapStops,busLine);
    readEdge(busLine,mapStops);
    busLine.stopNextStop(mapStops);


    //cout<<busLine.distance(235,626)<<endl;

    Application1 app1(&busLine,mapStops);
    app1.originPositionMenu();

    //Application app1(&busLine,mapStops);
    //app1.mainMenu();
    //cout<<busLine.distance(235,626)<<endl;

}

// busLine.showNodes();
//readEdge(busLine,mapStops);
//cout.precision(3);
//busLine.getEdge(mapStops.find("ASP4")->second);
//busLine.setStoplines(mapStops.find("ASP4")->second);
//for (auto i : busLine.getStoplines()){
//  cout<<i.line<<endl;
//}

//Application1 app1(&busLine,mapStops);
//cout<<busLine.distance(mapStops.find("BCM1")->second,mapStops.find("MAV1")->second)<<endl;//menos paragem possiveis
//cout<<busLine.dijkstra_distance(mapStops.find("BCM1")->second,mapStops.find("MAV1")->second)<<endl;
//app1.mainMenu();
//busLine.distancePersonStop(41.174505,-8.599566








