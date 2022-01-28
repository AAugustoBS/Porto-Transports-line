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
                 //menu1();
                 /*
                  * Para efeitos de melhor compreensão: procurar melhor rota para o usuario com base em suas escolhas
                  * (1) Com saida  de uma origem(codigo paragem, coordenadas)
                  * (2) Com chegeda a um destino (codigo paragem,coordenadas)
                  * (3) perguntar preferencia de rota(menos paragens, mais rapido,se der tempo fazer mais barato)
                  */
                menuSearchRoute();
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
    cout<<"1. Search stops more close\n";
    cout<<"2. Set distance\n";
    cout<<"3. Minimum stops\n";
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


void Application::menuSearchRoute(){
    int origChoose,destChoose,routePreference; //EM ORDEM: (1) COORDENADAS,(2) CODIGO PARAGEM
 // [1] O user prioriza menos paragens [2] o user prioriza menor distancia em km
    double latOrig,logOrig,latDest,logDest;
    string codeStopOrig,codeStopDest;
    vector<pair <string ,double>> possivelStopsOrig,possivelStopsDest;

    cout<<"Search route Menu!\n";
    cout<<"Your origin is [1] coordinate [2] stop code: ";

    cin>>origChoose;
    cin.clear();
    //TRATANDO DA ORIGEM
    switch(origChoose){
        case 1:
            askCoordinates(latOrig,logOrig);
            possivelStopsOrig = busLine->distancePersonStop(latOrig,logOrig);
            break;
        case 2:
            askStop(codeStopOrig);


    }

    //TRATANDO DO DESTINO
    cout<<"Your destination is [1] coordinate [2] stop code: ";
    cin>>destChoose;
    switch ((destChoose)) {
        case 1:
            askCoordinates(latDest,logDest);
            possivelStopsDest = busLine->distancePersonStop(latDest,logDest);
            cout<<possivelStopsDest.size()<<endl;
            break;

        case 2:
            askStop(codeStopDest);
            break;
    }

    //Tratando da escolha do usuario de preferencia de rota
    cout<<"Do you prefer routes with few stops[1] or with shorter distances[2]? ";
    cin>>routePreference;



    if(origChoose == 1 && destChoose == 1){ //se a origem e o destino são coordenadas:
        if(routePreference== 1){
            filterBesRoutesByBFS(possivelStopsOrig,possivelStopsDest);
        }
        else if(routePreference== 2){
            filterBestRouteByDij(possivelStopsOrig,possivelStopsDest);
        }
    }

    if(origChoose==2 && destChoose == 1){// se a origem é codestop e dest coordenadas:
        if(routePreference == 1){

            filterBestWayByBFS(codeStopOrig,possivelStopsDest,1);
        }
        if(routePreference == 2){

        }
    }

    if(origChoose == 1 && destChoose == 2){//se a origem é coordenadas e dest stop:
        if(routePreference == 1){
            filterBestWayByBFS(codeStopDest,possivelStopsOrig,2);
        }
    }

    if(origChoose == 2 && destChoose == 2){
        if(routePreference == 1){//bfs
            int stopCount = busLine->distance(mapStops.find(codeStopOrig)->second,mapStops.find(codeStopDest)->second);
            //Lembrar de colocar couts de instrução
        }
        if(routePreference == 2){//DIJSKTRAUNUIOD
            double distance = busLine->dijkstra_distance(mapStops.find(codeStopOrig)->second,mapStops.find(codeStopDest)->second);
        }
    }

}

void Application::bestWayByDij(string codeStop,vector<pair <string ,double>> possivelStops,int choose){
    pair<pair<string,string>,double> bestRoute;
    bestRoute.first.first = codeStop;
    bestRoute.first.second = "";
    bestRoute.second = INT_MAX/2; //DISTANCIA EM KM
    if(choose == 1){// Se a origem é code e destino é stop
        for(auto dest:possivelStops){
            double distance = busLine->dijkstra_distance(mapStops.find(codeStop)->second,mapStops.find(bestRoute.first.second)->second);
            if(distance<bestRoute.second){
                bestRoute.first.second = dest.first;
                bestRoute.second = distance;
            }
        }

    }

    else if(choose == 2){

    }
}


void Application::filterBestWayByBFS(string codeStop,vector<pair <string ,double>> possivelStops,int choose){
    pair<pair<string,string>,int> bestRoute;
    if(choose == 1){//Trata-se da ordem Origem:stop  Destino:coordenada

        bestRoute.first.first = codeStop;
        bestRoute.first.second = "";
        bestRoute.second = INT_MAX/2;
        for(auto dest: possivelStops){
            int distance = busLine->distance(mapStops.find(codeStop)->second,mapStops.find(dest.first)->second);
            if(distance<bestRoute.second){
                cout<<distance<<endl;
                bestRoute.first.second = dest.first;
                bestRoute.second = distance;
            }
        }

        cout<<"Go to ";
        busLine->showNodeById(mapStops.find(codeStop)->second);
        cout<<" and wait for "<<bestRoute.second<<"stops  until "<<endl;
        busLine->showNodeById(mapStops.find(bestRoute.first.second)->second);
        cout<<endl;
        return;
    }

    else if(choose == 2){//Trata-se da ordem Origem:coordenada  Destino:stop
        bestRoute.first.first = codeStop;
        bestRoute.first.second = "";
        bestRoute.second = INT_MAX/2;
        for(auto orig : possivelStops){
            int distance = busLine->distance(mapStops.find(orig.first)->second,mapStops.find(codeStop)->second);
            if(distance<bestRoute.second){
                bestRoute.first.second = orig.first;
                bestRoute.second = distance;
            }
        }

        cout<<"Go to ";
        busLine->showNodeById(mapStops.find(bestRoute.first.first)->second);
        cout<<" and wait for "<<bestRoute.second<<" until ";
        busLine->showNodeById(mapStops.find(codeStop)->second);
        return;
    }

}


void Application::filterBestRouteByDij(vector<pair <string ,double>> possivelStopsOrig,vector<pair <string ,double>> possivelStopsDest){
    pair<pair<string,string>,double> bestRoute;
    bestRoute.first.first = "";
    bestRoute.first.second = "";
    bestRoute.second = INT_MAX/2; //DISTANCIA EM KM

    for(auto orig: possivelStopsOrig){
        for(auto dest: possivelStopsDest){
            //cout<<orig.first.<<endl;
            double distance = busLine->dijkstra_distance(mapStops.find(orig.first)->second,mapStops.find(dest.first)->second);
            if(distance < bestRoute.second){
                bestRoute.first.first = orig.first;
                bestRoute.first.second = dest.first;
                bestRoute.second = distance;
            }
        }
    }
    cout<<"Go to ";
    busLine->showNodeById(mapStops.find(bestRoute.first.first)->second);
    cout<<" and wait for "<<bestRoute.second<<"km until ";
    busLine->showNodeById(mapStops.find(bestRoute.first.second)->second);

}

void Application::filterBesRoutesByBFS(vector<pair <string ,double>> possivelStopsOrig,vector<pair <string ,double>> possivelStopsDest){
    pair<pair<string,string>,int> bestRoute; //par do ponto a pra b, int=numero de paragens

    //AQUI INICIAMOS A MELHOR ROTA COM UM VALOR ALTISSIMO
    bestRoute.first.first = "";
    bestRoute.first.second = "";
    bestRoute.second = INT_MAX/2; // O QUE NOS INTERESSSA A NIVEL DE COMPARAÇÃO É ISSO! QUANTIDADE DE PARAGEM!

    for(auto ori:possivelStopsOrig){
        for(auto dest: possivelStopsDest){
            int auxDistance = busLine->distance(mapStops.find(ori.first)->second,mapStops.find(dest.first)->second);
            if(auxDistance< bestRoute.second){
                bestRoute.first.first = ori.first;
                bestRoute.first.second = dest.first;
                bestRoute.second = auxDistance;
            }
        }
    }

    cout<<"Go to ";
    busLine->showNodeById(mapStops.find(bestRoute.first.first)->second);
    cout<<" and wait for "<<bestRoute.second<<" until ";
    busLine->showNodeById(mapStops.find(bestRoute.first.second)->second);
}


/*
//NESSA USA-SE BFS PARA ROTA!!!
 lessStopMenu(origChoose,destChoose);
void Application::lessStopMenu(int origChoose,int destChoose){
    double latOri,logOri;
    string codeStopOrig;
    vector<pair <string ,double>> possivelStops;

    if(origChoose == 1){ // se a origem partir de uma coordenada
        cout<<"Digit your origin coordinates: ";
        double latDest,logDest;
        cin>>latOri;
        cin>>logOri;
        possivelStops = busLine->distancePersonStop(latOri,logOri);
        if(destChoose == 1){
            cout<<"Now digit the coordinates of your destination:  "
        }
    }



}*/


void Application::askCoordinates(double &lat,double &log){
    cout<<"Digit your latitude: ";
    cin>>lat;
    cout<<"Digit your longitude: ";
    cin>>log;
}

void Application::askStop(string &codeStop){
    cout<<"Digit your stop code: ";
    cin>>codeStop;
}
