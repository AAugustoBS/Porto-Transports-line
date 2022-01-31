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
    cout<<"PORTO PUBLIC TRANSPORT SYSTEM\n";
    cout<<"-----------------------------------------\n";
    cout<<"Select the way you will insert your ORIGIN position:\n";
    cout<<"1. Coordinates\n";
    cout<<"2. Code of Stop\n";
    cout<<"0. Exit\n";
}

void Application1::originPositionMenu(){
    int choose;
    double distMax;
    cout<<"Set your max distance (Km): "<<endl;
    cin>>distMax;
    busLine->setDistanceMax(distMax);
    cin.clear();
    cin.ignore(1000,'\n');
    stateApplication = true;
    while(stateApplication) {
        printOriginMenuOptions();
        cin>>choose;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid option, enter again!\n\n";
            originPositionMenu();
            break;
        }

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
            default:
                cout << "Invalid option, enter again!\n\n";
                originPositionMenu();
                break;
        }

        if(stateApplication)
            destPositionMenu();
    }
}

void Application1::setOriginCoordenates(){
    cout<<"Latitude: ";
    cin>>this->originLatitude;
    cout<<endl;
    cout<<"Longitude: ";
    cin>>this->originLongitude;
    cout<<endl;
}

void Application1::setOriginStop(){
    cout<<"Origin Stop: ";
    cin>>this->originStop;
    for (auto & c: originStop) c = toupper(c);
    cout<<endl;
}

void Application1::printDestMenuOptions() {
    cout<<"PORTO PUBLIC TRANSPORT SYSTEM\n";
    cout<<"-----------------------------------------\n";
    cout<<"Select the way you will insert your DESTINATION position:\n";
    cout<<"1. Coordinates\n";
    cout<<"2. Code of Stop\n";
    cout<<"0. Exit\n";
}

void Application1::destPositionMenu(){
    int choose;
    printDestMenuOptions();
    cin>>choose;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid option, enter again!\n\n";
        destPositionMenu();
    }

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
        default:
            cout << "Invalid option, enter again!\n\n";
            destPositionMenu();
            break;
    }

    if(stateApplication)
        typeOfTrip();

}

void Application1::setDestCoordenates() {
    cout<<"Latitude: ";
    cin>>this->destLatitude;
    cout<<endl;
    cout<<"Longitude: ";
    cin>>this->destLongitude;
    cout<<endl;
}

void Application1::setDestStop(){
    cout<<"Destination Stop: ";
    cin>>this->destStop;
    for (auto & c: destStop) c = toupper(c);
    cout<<endl;
}

void Application1::printTypeOfTrip() {
    cout<<"PORTO PUBLIC TRANSPORT SYSTEM\n";
    cout<<"-----------------------------------------\n";
    cout<<"Select the type of your trip:\n";
    cout<<"1. Fewer stops\n";
    cout<<"2. Shorter Distance\n";
    cout<<"0. Exit\n";
}

void Application1::typeOfTrip(){
    int choose;
    printTypeOfTrip();
    cin>>choose;
    selectOption=choose;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid option, enter again!\n\n";
        typeOfTrip();
    }

    switch (choose) {
        case 0:
            stateApplication=false;
            break;

        case 1:
            cin.ignore();
            fewerStops();
            break;
        case 2:
            cin.ignore();
            shorterDistance();
            break;
        default:
            cout << "Invalid option, enter again!\n\n";
            typeOfTrip();
            break;
    }
}


void Application1::fewerStops() {

    float distance;
    bestroute.second = INT_MAX / 2;

    if (originType)
        originPossivelStops = possivelStops(originLatitude, originLongitude);

    if (destType)
        destPossivelStops = possivelStops(destLatitude, destLongitude);

    if (originType && destType){
        for (auto i: originPossivelStops) {
            for (auto j: destPossivelStops) {

                distance = busLine->distance(mapStops.find(i.first)->second, mapStops.find(j.first)->second);
                if (distance < bestroute.second && distance!=0) {
                    setBestRoute(i.first, j.first, distance);
                }
            }
        }
    }
    else if (!originType && !destType) {
        int distance = busLine->distance(mapStops.find(originStop)->second, mapStops.find(destStop)->second);
        setBestRoute(originStop, destStop, distance);
    }
    else if (!originType && destType) {

        for (auto i: destPossivelStops) {
            distance = busLine->distance(mapStops.find(originStop)->second, mapStops.find(i.first)->second);
            if (distance < bestroute.second && distance!=0) {
                setBestRoute(originStop, i.first, distance);
            }
        }
    }
    else if (originType && !destType) {
        for (auto i: originPossivelStops) {
            distance = busLine->distance(mapStops.find(i.first)->second, mapStops.find(destStop)->second);
            if (distance < bestroute.second && distance!=0) {
                setBestRoute(i.first, destStop, distance);
            }
        }
    }

    printResult(bestroute);
}

vector<pair<string, double>> Application1::possivelStops(double latitude, double longitude) {
    return busLine->distancePersonStop(latitude, longitude);
}


void Application1::setBestRoute(string origem, string destino, double nStops) {
    bestroute.first.first = origem;
    bestroute.first.second = destino;
    bestroute.second = nStops;
}

void Application1::shorterDistance() {
    double distance;

    bestroute.second=INT_MAX/2;
    if (originType)
        originPossivelStops = possivelStops(originLatitude, originLongitude);
    if (destType)
        destPossivelStops = possivelStops(destLatitude, destLongitude);

    if (originType && destType){
        for (auto i: originPossivelStops) {
            for (auto j: destPossivelStops) {

                distance = busLine->dijkstra_distance(mapStops.find(i.first)->second, mapStops.find(j.first)->second);
                if (distance < bestroute.second && distance!=0) {
                    setBestRoute(i.first, j.first, distance);
                }
            }
        }
    }
    else if (!originType && !destType) {
        distance = busLine->dijkstra_distance(mapStops.find(originStop)->second, mapStops.find(destStop)->second);
        setBestRoute(originStop, destStop, distance);
    }
    else if (!originType && destType) {

        for (auto i: destPossivelStops) {
            distance = busLine->dijkstra_distance(mapStops.find(originStop)->second, mapStops.find(i.first)->second);
            if (distance < bestroute.second && distance!=0) {
                setBestRoute(originStop, i.first, distance);
            }
        }
    }
    else if (originType && !destType) {
        for (auto i: originPossivelStops) {
            distance = busLine->dijkstra_distance(mapStops.find(i.first)->second, mapStops.find(destStop)->second);
            if (distance < bestroute.second && distance!=0) {
                setBestRoute(i.first, destStop, distance);
            }
        }
    }

    list<int> path = busLine->dijkstra_path(mapStops.find(bestroute.first.first)->second,mapStops.find(bestroute.first.second)->second);
    list<string> lines = busLine->linesListShorterPath(path);
    printResultwithLine(bestroute,lines,path);
    callInitialMenu();
}

void Application1::printResult(pair<pair<string,string>,double> bestroute){
    cout << "From: " << bestroute.first.first << "  To: " << bestroute.first.second << "  Have " << bestroute.second << " Stops" << endl<<endl;
    cout << "Your path is:"<<endl;

    list<int> path = busLine->bfs_Path(mapStops.find(bestroute.first.first)->second,mapStops.find(bestroute.first.second)->second);
    list<string> lines = busLine->linesListShorterPath(path);
    list<int>:: iterator it = path.begin();
    for(auto i: lines){
        busLine->showNodeById(*it);
        cout<<" on "<<i<<" until ";
        advance(it,1);
        busLine->showNodeById(*it);
        cout<<endl;
    }
    cout<<endl;
    callInitialMenu();
}

void Application1::printResultwithLine(pair<pair<string,string>,double> bestroute,list<string> lines,list<int> path){
    cout << "From: " << bestroute.first.first << "  To: " << bestroute.first.second << "  Have " << bestroute.second << " Km" << endl<<endl;
    cout << "Your path is:"<<endl;

    list<int>:: iterator itPath = path.begin();
    list<string>::iterator itLine = lines.begin();
    int stop1 = *itPath;
    advance(itPath,1);
    while(itPath != path.end()){
        int stop2 = *itPath;
        cout<<"Take "<<*itLine<<" from ";
        busLine->showNodeById(stop1);
        cout<<" until ";
        busLine->showNodeById(stop2);
        cout<<endl;
        stop1 = stop2;
        advance(itPath,1);
        advance(itLine,1);
    }
    cout<<endl;
}

void Application1::callInitialMenu(){
    int choose;
    cout<<"You want to search another bus?[1]Yes [0]No :";
    cin >> choose;
    cout<<endl;
    if (choose == 0){
        stateApplication=false;
    }
}

