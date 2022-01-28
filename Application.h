//
// Created by Antonio Augusto on 27/01/2022.
//

#ifndef AED_PROJECT_APPLICATION_H
#define AED_PROJECT_APPLICATION_H

#include "graph.h"
#include <iostream>
#include <string>
#include <map>
#include "AuxFunctions.h"


class Application {

public:
    Application(Graph *busLine,map<string,int> &mapStops);

    void mainMenu();

    void printMenuOptions();

    void menuSetDistance();

    void menu1();

    void menuTypeDestinationStop();

    void MinimumbyStop();

    void MinimumbyCoordenates();

    void menuSearchRoute();

    void lessStopMenu(int origChoose,int destChoose);

    void filterBestWayByBFS(string codeStop,vector<pair <string ,double>> possivelStops,int choose);

    void filterBestRouteByDij(vector<pair <string ,double>> possivelStopsOrig,vector<pair <string ,double>> possivelStopsDest);

    void filterBesRoutesByBFS(vector<pair <string ,double>> possivelStopsOrig,vector<pair <string ,double>> possivelStopsDest);

    void bestWayByDij(string codeStop,vector<pair <string ,double>> possivelStops,int choose);

    void askCoordinates(double &lat,double &log);

    void askStop(string &codeStop);

private:
    bool stateApplication;
    Graph *busLine;
    map<string,int> mapStops;
    vector<pair <string ,double>> possivelStops;

};


#endif //AED_PROJECT_APPLICATION_H
