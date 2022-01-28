#include "graph.h"
#include <climits>
#include <iostream>
#include<queue>
#include "AuxFunctions.h"
#include "MinHeap.h"
#include <map>
#include <algorithm>
// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, float weight,string name) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight,name});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

void Graph::setInfoNode(int idNode,vector<string>info) {
        nodes[idNode].codeName = info[0];
        nodes[idNode].adress = info[1];
        nodes[idNode].zone = info[2];
        nodes[idNode].lat = stod(info[3]);
        nodes[idNode].log = stod(info[4]);
}


void Graph::setInfoLine(int src, int dest, string lineName) {
    float distance = haversineFormula(nodes[src].lat,nodes[src].log,nodes[dest].lat,nodes[dest].log);
    addEdge(src,dest,distance,lineName);
}

void Graph::dijkstra(int s){

    MinHeap<int,double>q(n,0);
    for(int v = 1;v<=n;v++){
        nodes[v].dist = INT_MAX/2;
        q.insert(v,INT_MAX/2);
        nodes[v].visited = false;
    }

    nodes[s].dist = 0;
    q.decreaseKey(s,0);
    nodes[s].pred = s;
    while(q.getSize()>0){
        int u = q.removeMin();
        nodes[u].visited = true;

        for(auto e:  nodes[u].adj){
            double v = e.dest;
            double w = e.weight;
            if(!nodes[v].visited && nodes[u].dist + w < nodes[v].dist){
                nodes[v].dist = nodes[u].dist + w;

                q.decreaseKey(v,nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }

}

void Graph::getPath(int src,int dest) {
    list<int> pa = dijkstra_path(src,dest);

    list<int>::iterator it = pa.begin();
    while(it !=pa.end()){
        cout << nodes[*it].codeName << endl;
       // cout<<nodes[*it].codeName<<endl;
        advance(it,1);
    }
}

double Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    return nodes[b].dist;

}


list<int> Graph::dijkstra_path(int a, int b) {

    list<int> path;
    dijkstra(a);
    if(nodes[b].dist == INT_MAX/2)return path;
    int v = b;
    path.push_front(v);

    while(v!= a){
        //cout<<v<<endl;
        v=nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();

        int count = 0;
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist +1;
            }
        }
    }
}

int Graph::distance(int a, int b) {
    bfs(a);
   // cout<<nodes[a].codeName<<" "<<nodes[b].codeName<<endl;
    return nodes[b].dist;
}



void Graph::getEdge(int idStops) {

    for(auto i:nodes[idStops].adj){
        cout<<i.line<<endl;
    }


}

bool Graph::sortBySecond(const pair<Node, double> &a, const pair<Node, double> &b){
    return (a.second < b.second);
}


vector<pair<string, double>> Graph:: distancePersonStop(double lat, double log) {

   pair<string ,double> pairaux ;
   vector<pair<string, double>> paragensProx ;

   //paragensProx.push_back(1);
   //paragensProx.push_back(3);

    for(auto i: nodes){
        double dist=haversineFormula(lat,log,i.lat,i.log);
        if(dist<=distMax){

            pairaux.first=i.codeName;
            pairaux.second=dist;
            paragensProx.push_back(pairaux);
        }
    }

    //sort(paragensProx.begin(), paragensProx.end());
    return paragensProx;

}

void Graph::setDistanceMax(double distance) {
    this->distMax = distance;
}

void Graph::showNodeById(int idStop){
   // cout<<idStop<<endl;
    cout<<nodes[idStop].codeName;

}

