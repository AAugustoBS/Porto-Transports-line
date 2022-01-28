//
// Created by Antonio Augusto on 27/01/2022.
//

#include "Application.h"

Application::Application(Graph *busLine,map<string,int> &mapStops){
    this->stateApplication = false;
    this->busLine = busLine;
    this->mapStops = mapStops;
}

void Application::mainMenu() {
    int nodes;
    int choose;
    stateApplication = true;
    while(stateApplication){
        printMenuOptions();
        cin>>choose;
         switch(choose){
             case 1:
                 menu1();
                break;

             case 2:
                 menuSetDistance();
                break;

             case 3:
                 menuTypeDestinationStop();
                 break;
             case 0:
                 stateApplication = false;
                 break;
         }
    }
}


void Application::printMenuOptions() {

    cout<<"Welcome to Porto public transport System!\n\n";
    cout<<"Select an option below: \n";
    cout<<"1. Search stops more cl\n";
    cout<<"2. Set distance\n ";
    cout<<"3. Minimum stops";
    cout<<"0. Exit\n";


}

void Application::menu1(){
    double latitude = 41.175405; // coordenadas Açoreano HOUSE
    double longitude = -8.599566;

    //cout<<"Inserir latitude:"<<endl;
    //cin>>latitude;
    //cout<<"Inserir latitude:"<<endl;
    //cin>>longitude;
    possivelStops = busLine->distancePersonStop(latitude,longitude);
    //cout<<possivelStops.size()<<endl;
}



void Application::menuSetDistance() {
    float distance;
    cout << "Set your distance: ";
    cin >> distance;
    busLine->setDistanceMax(distance);
}
 void Application::menuTypeDestinationStop(){
    cout<<"Select your destination"<<endl;
    cout<<"1. Paragem de destino"<<endl;
    cout<<"2. Coordenadas"<<endl;

    int choose;
    cin>>choose;

    switch(choose){
        case 1:
            MinimumbyStop();
            break;
        case 2:
            MinimumbyCoordenates();
            break;
    }
}

void Application::MinimumbyStop(){

    string codeDest= "ASP4";
    string codeOrig ;
    pair <string, int> minimum ;
    minimum.second = busLine->distance(mapStops.find(possivelStops[0].first)->second,mapStops.find(codeDest)->second);
    for(auto i : possivelStops){
        minimum.first=i.first;
        codeOrig=i.first;
        int aux =busLine->distance(mapStops.find(codeOrig)->second,mapStops.find(codeDest)->second);
        if(minimum.second >aux){
            minimum.second = aux;
        }
    }
    cout<<minimum.first<<": "<<minimum.second<<endl;
}

void Application::MinimumbyCoordenates(){
}