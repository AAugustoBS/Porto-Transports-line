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
}

void Application1::originPositionMenu(){
        int choose;
        stateApplication = true;
        while(stateApplication) {
            printOriginMenuOptions();
            cin>>choose;
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
            if(stateApplication)
                destPositionMenu();
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
}

void Application1::destPositionMenu(){
    int choose;
    printDestMenuOptions();
    cin>>choose;

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
        if(stateApplication)
            typeOfTrip();
}

void Application1::setDestCoordenates() {
    //destLatitude = 41.172245;  //Açoreano COORDENATES
    //destLongitude = -8.597604;
    destLatitude = 41.149875;  //Mercado Bolhao
    destLongitude = -8.606005;
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
    //typeOfTrip();
}

void Application1::typeOfTrip(){
    int choose;
    printTypeOfTrip();
    cin>>choose;
    selectOption=choose;
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
                cin.ignore();
                shorterDistance();
                break;

            case 3:
                cin.ignore();
                //lessBusChanges();
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
    printResult(bestroute);
    /*cout << "From: " << bestroute.first.first << "  To: " << bestroute.first.second << "   Have "
         << bestroute.second << "Km" << endl;*/
}

void Application1::printResult(pair<pair<string,string>,double> bestroute){
    switch (selectOption) {
        case 1:
            cout << "From: " << bestroute.first.first << "  To: " << bestroute.first.second << "  Have " << bestroute.second << " Stops" << endl<<endl<<endl;
            break;
        case 2:
            cout << "From: " << bestroute.first.first << "  To: " << bestroute.first.second << "  Have " << bestroute.second << " Km" << endl<<endl<<endl;
            break;
    }
    callInitialMenu();
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
