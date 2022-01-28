//
// Created by Antonio Augusto on 27/01/2022.
//

#ifndef AED_PROJECT_APPLICATION_H
#define AED_PROJECT_APPLICATION_H

#include "graph.h"
#include <iostream>
#include <string>
#include <map>


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
private:
    bool stateApplication;
    Graph *busLine;
    map<string,int> mapStops;
    vector<pair <string ,double>> possivelStops;

};


#endif //AED_PROJECT_APPLICATION_H
