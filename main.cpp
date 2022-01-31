#include <iostream>
#include <string>
#include <map>
#include "graph.h"
#include "AuxFunctions.h"
#include "ReadFiles.h"
#include "Application1.h"
using namespace std;

int main() {

    Graph busLine(2487,true);
    map<string,int> mapStops;
    fillmapStops(mapStops,busLine);
    readEdge(busLine,mapStops);
    busLine.stopNextStop(mapStops);

    Application1 app1(&busLine,mapStops);
    app1.originPositionMenu();
}








