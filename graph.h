// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef GRAPH_H
#define GRAPH_H

//#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight(km's distance)
        string line; //
    };

    //PARAGENS DE AUTOCARRO
    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double dist;
        int pred;
        bool visited;

        string codeName;
        string adress;
        string zone;
      //  Coordinates c1;
        double lat,log;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    double distMax = 0.3;
    void dijkstra(int s);
    vector <Edge> stoplines={} ;
    vector <int> trajeto={};

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, float weight,string name);

    void showNodeById(int idStop);

    void setInfoNode(int idNode,vector<string>info);

    void getPath(int src,int dest);

    void setInfoLine(int src,int dest,string lineName);

    void showNodes();

    void getEdge(int idStops);

    // ----- Functions to implement in this class -----
    double dijkstra_distance(int a, int b);

    list<int> dijkstra_path(int a, int b);

    void bfs(int v);

    void setDistanceMax(double distance );

    vector<pair<string, double>> distancePersonStop(double lat, double log);

    int distance(int a, int b);

    void setStoplines(int idStops);

    const vector<Edge> &getStoplines();

    void createtrajeto(queue<int> q);

    bool sortBySecond(const pair<Node, double> &a, const pair<Node, double> &b);
};

#endif