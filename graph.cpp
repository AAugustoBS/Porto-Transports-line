#include "graph.h"
#include <climits>
#include <iostream>
#include<queue>
#include "AuxFunctions.h"
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

void Graph::showNodes() {

    for(auto v: nodes){
        cout<<v.codeName<<" "<<v.adress<<endl;
    }
}

void Graph::setInfoLine(int src, int dest, string lineName) {
    float distance = haversineFormula(nodes[src].lat,nodes[src].log,nodes[dest].lat,nodes[dest].log);
    addEdge(src,dest,distance,lineName);
}

int Graph::dijkstra_distance(int a, int b) {

    // vetor de distâncias
    int dist[nodes.size()];

    /*
       vetor de visitados serve para caso o vértice já tenha sido
       expandido (visitado), não expandir mais
    */
    int visitados[nodes.size()];

    // fila de prioridades de pair (distancia, vértice)
    priority_queue < pair<int, int>,
    vector<pair<int, int> >, greater<pair<int, int> > > pq;

    // inicia o vetor de distâncias e visitados
    for(int i = 0; i < nodes.size(); i++)
    {
        dist[i] = 1000;
        visitados[i] = false;
    }

    // a distância de orig para orig é 0
    dist[a] = 0;

    // insere na fila
    pq.push(make_pair(dist[a], a));

    // loop do algoritmo
    while(!pq.empty())
    {
        pair<int, int> p = pq.top(); // extrai o pair do topo
        int u = p.second; // obtém o vértice do pair
        pq.pop(); // remove da fila

        // verifica se o vértice não foi expandido
        if(visitados[u] == false)
        {
            // marca como visitado
            visitados[u] = true;

            list<Edge>::iterator it;

            // percorre os vértices "v" adjacentes de "u"
            for(it = nodes[u].adj.begin();it != nodes[u].adj.end();it++){

                // obtém o vértice adjacente e o custo da aresta
                int v = it->dest;
                int custo_aresta = it->weight;

                // relaxamento (u, v)
                if(dist[v] > (dist[u] + custo_aresta))
                {
                    // atualiza a distância de "v" e insere na fila
                    dist[v] = dist[u] + custo_aresta;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    // retorna a distância mínima até o destino
    return dist[b];

}


list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    // vetor de distâncias
    int dist[nodes.size()];

    /*
       vetor de visitados serve para caso o vértice já tenha sido
       expandido (visitado), não expandir mais
    */
    int visitados[nodes.size()];

    // fila de prioridades de pair (distancia, vértice)
    priority_queue < pair<int, int>,
    vector<pair<int, int> >, greater<pair<int, int> > > pq;

    // inicia o vetor de distâncias e visitados
    for(int i = 0; i < nodes.size(); i++)
    {
        dist[i] = 1000;
        visitados[i] = false;
    }

    // a distância de orig para orig é 0
    dist[a] = 0;
    path.push_back(a);
    // insere na fila
    pq.push(make_pair(dist[a], a));

    // loop do algoritmo
    while(!pq.empty())
    {
        pair<int, int> p = pq.top(); // extrai o pair do topo
        int u = p.second; // obtém o vértice do pair
        pq.pop(); // remove da fila

        // verifica se o vértice não foi expandido
        if(visitados[u] == false)
        {
            // marca como visitado
            visitados[u] = true;

            list<Edge>::iterator it;

            // percorre os vértices "v" adjacentes de "u"
            for(it = nodes[u].adj.begin();it != nodes[u].adj.end();it++){
                /* for(it = adj[u].begin(); it != adj[u].end(); it++)
                 {*/
                // obtém o vértice adjacente e o custo da aresta
                int v = it->dest;
                int custo_aresta = it->weight;

                // relaxamento (u, v)
                if(dist[v] > (dist[u] + custo_aresta))
                {
                    // atualiza a distância de "v" e insere na fila

                    dist[v] = dist[u] + custo_aresta;
                    pq.push(make_pair(dist[v], v));
                    path.push_back(u);
                }

            }

        }
    }
    path.push_back(b);
    // retorna a distância mínima até o destino
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
       // cout << u << " "; // show node order
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
    cout<<nodes[a].codeName<<" "<<nodes[b].codeName<<endl;
    return nodes[b].dist;
}
