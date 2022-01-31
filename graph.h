// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef GRAPH_H
#define GRAPH_H

//#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

class Graph {
    struct Edge {
        /**
         * destination stop
         */
        int dest;
        /**
         * distance in km
         */
        double weight;
        /**
         * code of the line
         */
        string line;
    };

    struct Node {
        /**
         * list with adjacent lines
         */
        list<Edge> adj;
        double dist;
        int pred;
        bool visited;
        /**
         * code of the stop
         */
        string codeName;
        string address;
        string zone;
        /**
         * coordinates of the stop
         */
        double lat,log;
    };

    /**
     * number of the nodes
     */
    int n;
    /**
     * show if the graph is directed
     */
    bool hasDir;
    /**
     * vector with the nodes
     */
    vector<Node> nodes;
    /**
     * default distance that the user can walk
     */
    double distMax = 0.3;
    void dijkstra(int s);

public:
    /**
     * Constructor of class graph
     * @param nodes number of nodes of the graph
     * @param dir represents if graph have direction
     */
    Graph(int nodes, bool dir = false);
    /**
     * Add an edge to the graph
     * @param src source node
     * @param dest destination node
     * @param weight weight of the edge
     * @param name name of the line
     */
    void addEdge(int src, int dest, float weight,string name);
    /**
     * shows the stop code
     * @param idStop stop code
     */
    void showNodeById(int idStop);
    /**
     * locate stops that are close and create a new edge between them
     * @param mapStops map of stops and corresponding node number
     */
    void stopNextStop(map<string,int> mapStops);
    /**
     * set information of the node
     * @param idNode number of the node
     * @param info vector that contains the information
     */
    void setInfoNode(int idNode,vector<string>info);
    /**
     * returns the path between a source node and a destination node
     * @param src source node
     * @param dest destination node
     */
    void getPath(int src,int dest);
    /**
     * set information of the line
     * @param src source node
     * @param dest destination node
     * @param lineName name of the line
     */
    void setInfoLine(int src,int dest,string lineName);
    /**
     * show lines associated to a node
     * @param idStops number of the node
     */
    void getEdge(int idStops);
    /**
     * distance from one stop to another
     * @param a origin stop
     * @param b destination stop
     * @return distance between stops
     */
    double dijkstra_distance(int a, int b);
    /**
     * return the path, by stops, between two stops using dijkstra algorithm
     * @param a origin stop
     * @param b destination stop
     * @return list with the path, in stops
     */
    list<int> dijkstra_path(int a, int b);
    /**
     * set the distance, by number of stops, between origin stop and all others
     * @param v origin stop
     */
    void bfs(int v);
    /**
     * show the path, by stops, between two stops, using bfs algorithm
     * @param a origin node
     * @param b destination node
     * @return list with the path, in stops
     */
    list<int> bfs_Path(int a,int b);
    /**
     * set distance max that user can walk
     * @param distance distance in km
     */
    void setDistanceMax(double distance );
    /**
     * generate a vector with the stops that the user can reach from his initial position, taking into account the distance he can walk
     * @param lat latitude of the coordinate
     * @param log longitude of the coordinate
     * @return vector with the stops
     */
    vector<pair<string, double>> distancePersonStop(double lat, double log);
    /**
     * distance, by stops, between two stops
     * @param a origin stop
     * @param b destination stop
     * @return number of stops between two stops
     */
    int distance(int a, int b);
    /**
     * list of the lines in the shorter path between two stops
     * @param path list with the stops of the path
     * @return list with the lines
     */
    list<string> linesListShorterPath(list<int> path);
    /**
     * add a line between two stops in a list of lines
     * @param stop1 origin stop
     * @param stop2 destination stop
     * @param lines list with the lines
     */
    void setLineOnList(int stop1,int stop2,list<string> &lines);
};

#endif