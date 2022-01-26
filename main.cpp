#include <iostream>
#include <string>
#include <map>
#include "graph.h"
#include "AuxFunctions.h"
#include "ReadFiles.h"

using namespace std;


int main() {

    Graph busLine(2487,true);
    map<string,int> mapStops;

    fillmapStops(mapStops,busLine);
  // busLine.showNodes();
    readEdge(busLine,mapStops);
    cout<<busLine.distance(914,1441);
}









