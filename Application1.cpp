//
// Created by Luís  Paiva on 28/01/2022.
//

#include "Application1.h"

Application1::Application1(Graph *busLine,map<string,int> &mapStops){
this->stateApplication = false;
this->busLine = busLine;
this->mapStops = mapStops;
}



void Application1::printOriginMenuOptions() {
    cout<<"Welcome to Porto public transport System!\n\n";
    cout<<"Origin Position: \n";
    cout<<"1. Coordenates\n";
    cout<<"2. Stop\n";
    cout<<"0. Exit\n";
    originPositionMenu();
}

void Application1::originPositionMenu(){
        int choose;
        cin>>choose;
        bool stateApplication = true;
        while(stateApplication) {
            switch (choose) {
                case 0:
                    stateApplication=false;
                    break;

                case 1:
                    originType=true;
                    setOriginCoordenates();
                    break;

                case 2:
                    originType=false;
                    setOriginStop();
                    break;

            }
            printDestMenuOptions();
        }
    }

void Application1::setOriginCoordenates(){
    originLatitude = 41.180548;  //UHUB COORDENATES
    originLongitude = -8.594938;
    /*
    cout<<"Latitude: ";
    cin>>this->originLatitude;
    cout<<endl;
    cout<<"Longitude: ";
    cin>>this->originLongitude;
    cout<<endl;*/
}

void Application1::setOriginStop(){
    originStop="ASP4";
    /*
    cout<<"Origin Stop: ";
    cin>>this->originStop;
    cout<<endl;*/
}

void Application1::printDestMenuOptions() {
    cout<<"Welcome to Porto public transport System!\n\n";
    cout<<"Destination Position: \n";
    cout<<"1. Coordenates\n";
    cout<<"2. Stop\n";
    cout<<"0. Exit\n";
    destPositionMenu();
}

void Application1::destPositionMenu(){
    int choose;
    cin>>choose;
    bool stateApplication = true;
    while(stateApplication) {
        switch (choose) {
            case 0:
                stateApplication=false;
                break;

            case 1:
                destType=true;
                setDestCoordenates();
                break;

            case 2:
                destType=false;
                setDestStop();
                break;
        }
        printTypeOfTrip();
    }
}

void Application1::setDestCoordenates() {
    destLatitude = 41.172245;  //Açoreano COORDENATES
    destLongitude = -8.597604;
    /*cout<<"Latitude: ";
    cin>>this->destLatitude;
    cout<<endl;
    cout<<"Longitude: ";
    cin>>this->destLongitude;
    cout<<endl;*/
}

void Application1::setDestStop(){
    destStop="CQ8";
    /*cout<<"Dest Stop: ";
    cin>>this->destStop;
    cout<<endl;*/
}

void Application1::printTypeOfTrip() {
    cout<<"Welcome to Porto public transport System!\n\n";
    cout<<"Type of your trip: \n";
    cout<<"1. Fewer stops\n";
    cout<<"2. Shorter Distance\n";
    cout<<"3. Less bus changes\n";
    cout<<"0. Exit\n";
    typeOfTrip();
}

void Application1::typeOfTrip(){
    int choose;
    cin>>choose;
    bool stateApplication = true;
    while(stateApplication) {
        switch (choose) {
            case 0:
                stateApplication=false;
                break;

            case 1:
                cin.ignore();
                fewerStops();
                //cin.ignore();
                break;

            case 2:
                //shorterDistance();
                break;

            case 3:
                //lessBusChanges();
                break;
        }
    }
}

void Application1::fewerStops(){
    pair<string,double> bestroute;
    if(originType)
        originPossivelStops = possivelStops(originLatitude,originLongitude);
    if(destType)
        destPossivelStops = possivelStops(destLatitude,destLongitude);

    bestroute.second = busLine->distance(mapStops.find("ASP4")->second,mapStops.find("CQ8")->second);
    cout<<mapStops.find("ASP4")->second<<endl;
    cout<<mapStops.find("CQ8")->second<<endl;

    for(auto i :originPossivelStops){
        int distance = busLine->distance(mapStops.find(i.first)->second,mapStops.find(destStop)->second);
    }


    stateApplication=false;

}

vector<pair <string ,double>> Application1::possivelStops(double latitude,double longitude){
    return busLine->distancePersonStop(latitude,longitude);
}

pair<string,double> Application1::bestRouteByFewerStops(){

}
