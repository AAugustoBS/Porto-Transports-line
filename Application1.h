//
// Created by Luís  Paiva on 28/01/2022.
//

#ifndef AED_PROJECT_APPLICATION1_H
#define AED_PROJECT_APPLICATION1_H

#include "graph.h"
#include <iostream>
#include <string>
#include <map>
#include "AuxFunctions.h"

class Application1 {

public:
    Application1(Graph *busLine,map<string,int> &mapStops);
    void printOriginMenuOptions();
    void originPositionMenu();
    void setOriginCoordenates();
    void setOriginStop();
    void printDestMenuOptions();
    void destPositionMenu();
    void setDestCoordenates();
    void setDestStop();
    void typeOfTrip();
    void printTypeOfTrip();
    void fewerStops();
    void shorterDistance();
    void lessBusChanges();
    vector<pair <string ,double>> possivelStops(double latitude,double longitude);
    pair<string,double> bestRouteByFewerStops();
    void setBestRoute(string origem,string destino,double nStops);
    void callInitialMenu();






private:
    bool stateApplication;
    Graph *busLine;
    map<string,int> mapStops;
    vector<pair <string ,double>> originPossivelStops = {};
    vector<pair <string ,double>> destPossivelStops = {} ;
    double originLatitude;
    double originLongitude;
    string originStop;
    bool originType; // true if the user choose Coordenates, false if the user choose Stop
    double destLatitude;
    double destLongitude;
    string destStop;
    bool destType; // true if the user choose Coordenates, false if the user choose Stop
    pair<pair<string,string>,double> bestroute; // origem,destino,numero de paragens
    void printResult(pair<pair<string,string>,double> bestroute);
    int selectOption;


};



#endif //AED_PROJECT_APPLICATION1_H
