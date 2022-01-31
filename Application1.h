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
    /**
     * application that manage all menus
     * @param busLine graph with all stops and all lines
     * @param mapStops map that connects the stop with a number of the corresponding node
     */
    Application1(Graph *busLine,map<string,int> &mapStops);
    /**
     * show the origin menu options
     */
    void printOriginMenuOptions();
    /**
     * show the origin position menu
     */
    void originPositionMenu();
    /**
     * show the set coordinates menu
     */
    void setOriginCoordenates();
    /**
     * set origin stop
     */
    void setOriginStop();
    /**
     * show destination menu options
     */
    void printDestMenuOptions();
    /**
     * show destination position options
     */
    void destPositionMenu();
    /**
     * set destination coordinates
     */
    void setDestCoordenates();
    /**
     * set destination stop
     */
    void setDestStop();
    /**
     * options for type if trip
     */
    void typeOfTrip();
    /**
     * show the options for the type of trip
     */
    void printTypeOfTrip();
    /**
     * show the path that have the lowest number of stops between two stops
     */
    void fewerStops();
    /**
     * show the path that have the shorter distance of stops between two stops
     */
    void shorterDistance();
    /**
     * possible stops
     * @param latitude latitude of coordinate
     * @param longitude longitude of coordinate
     * @return vector with information about the stops
     */
    vector<pair <string ,double>> possivelStops(double latitude,double longitude);
    /**
     * show the path
     * @param bestroute best path for the indicated situation
     * @param lines list with lines
     * @param path list with stops that belog to the best path
     */
    void printResultwithLine(pair<pair<string,string>,double> bestroute,list<string> lines,list<int> path);
    /**
     * set the best bath
     * @param origem origin stop
     * @param destino destination stop
     * @param nStops number of stops
     */
    void setBestRoute(string origem,string destino,double nStops);
    /**
     *Ask if the user want to back for initial main menu
     */
    void callInitialMenu();

private:
    /**
     * indicates if application is active
     */
    bool stateApplication;
    /**
     * graph with all stops and all lines
     */
    Graph *busLine;
    /**
     * maps de information of stops with a number of a node
     */
    map<string,int> mapStops;
    /**
     * vector with origin possible stops
     */
    vector<pair <string ,double>> originPossivelStops = {};
    /**
     * vector with destination possible stops
     */
    vector<pair <string ,double>> destPossivelStops = {} ;
    /**
     * latitude of origin
     */
    double originLatitude;
    /**
     * longitude of origin
     */
    double originLongitude;
    /**
     * origin stop
     */
    string originStop;
    /**
     * true if the user choose coordinates type, false if the user choose code of stop type
     */
    bool originType;
    /**
     * latitude of destination
     */
    double destLatitude;
    /**
     * longitude of destination
     */
    double destLongitude;
    /**
     * destination stop
     */
    string destStop;
    /**
     * true if the user choose coordinates, false if the user choose code of stop type
     */
    bool destType;
    /**
     * origin, destination, number of stops
     */
    pair<pair<string,string>,double> bestroute;
    /**
     * show the best path associated to the situation chosen
     * @param bestroute path associated to the situation chosen
     */
    void printResult(pair<pair<string,string>,double> bestroute);
    /**
     * number that represent the choice in each menu
     */
    int selectOption;

};

#endif //AED_PROJECT_APPLICATION1_H
