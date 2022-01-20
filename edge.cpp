#pragma once

#include "edge.h"
#include "graphMA.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class GraphLA{
    
    unordered_map<string, vector<Edge>> m_graph; 

    public:
    GraphLA(string nomFichier);
    vector<Edge> edges(string headName); //méthode retournant l'arête associée à un sommet donné
    void represent();
    GraphMA convertToMA();

    //Deep First Search
    void dfsRec(string headStart, set<string>& visitedHeads);
    void dfsIte(string headStart, set<string>& visitedHeads);
    //Breadth First Search
    void bfs(string headStart, set<string> visitedHeads);
};