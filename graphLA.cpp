#include "graphLA.h"
#include "graphMA.h"
#include "edge.h"
#include "function.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>

GraphLA::GraphLA (std::string nomFichier) {
    std::ifstream fichier(nomFichier);
    if (fichier){
        std::string line;
        while (getline(fichier, line)){
            std::istringstream iss(line);
            std::string a,b;
            double val;
            iss >> a;
            iss >> b;
            iss >> val;

 
            Edge EdgeLA(a, b, val);
            //Si a est déjà un sommet appartenant au conteneur 
            if (m_graph.count(a) != 0) { 
                m_graph[a].push_back(EdgeLA);
            }
            //Sinon il faut ajouter une nouvelle entrée au dictionnaire
            else { 
                std::vector<Edge> vect{EdgeLA};
                m_graph[a] = vect;
            }
            //Il faut aussi vérifier que les sommets d'arrivée ont une entrée dans le dictionnaire car
            //certains d'entre eux ne pointent pas vers d'autres sommets.
            if (m_graph.count(b) == 0) {  
                std::vector<Edge> vect;
                m_graph[b] = vect;
            }
        }
    }
    else{
        std::cout << "/!\\ ----- Fichier non trouvé !! ----- /!\\" << std::endl << std::endl;
    }
};

std::vector<Edge> GraphLA::edges(std::string headName) {
    return m_graph[headName];
};

void GraphLA::represent(){
    for (auto it = m_graph.begin(); it != m_graph.end(); ++it ) {
        int nEdges = it->second.size() ;
        for (int counter = 0 ; counter < nEdges ; counter++) {
            //std::cout << it->second[counter].m_a << " " << it->second[counter].m_b << " " << it->second[counter].m_value << std::endl;
            it->second[counter].print();
        };
    }
};

GraphMA GraphLA::convertToMA() {
    GraphMA newGraph;

    //Construction de la liste des sommets qui servira d'indiçage de référence pour la matrice
    for (auto iter : m_graph) {
        newGraph.m_headNames.push_back(iter.first);
    }
    int nHead = newGraph.m_headNames.size();
    newGraph.m_matrix.resize(nHead); //La matrice a nHead lignes.

    for (int i = 0 ; i < nHead ; i++) {
        std::vector<double> line(nHead,std::nan(""));
        newGraph.m_matrix[i] = line;
        for (auto itEdge : m_graph[newGraph.m_headNames[i]]){
            int j {getIndex(newGraph.m_headNames,itEdge.m_b)};
            newGraph.m_matrix[i][j] = itEdge.m_value ;
        }
        newGraph.m_matrix.push_back(line);
    }
    return newGraph;
};

void GraphLA::dfsRec(std::string headStart, std::set<std::string>& visitedHeads) { //headStart n'a pas été visité
    visitedHeads.insert(headStart);
    std::cout << "Sommet visité : " << headStart << std::endl ;
    for (auto iEdge : m_graph[headStart]) {
        std::cout << "Arête visitée : ";
        iEdge.print();
        if (visitedHeads.count(iEdge.m_b) == 0) {
            dfsRec(iEdge.m_b,visitedHeads);
        }
    }
};

void GraphLA::dfsIte(std::string headStart, std::set<std::string>& visitedHeads){
    std::stack<std::string> pile;
    std::string head = headStart;
    pile.push(head);
    while (! pile.empty()) {
        head = pile.top();
        pile.pop();
        if (visitedHeads.count(head) == 0) {
            std::cout << "Sommet visité : " << head << std::endl ;
            visitedHeads.insert(head);
            for (Edge iEdge : m_graph[head]) {
                std::cout << "Arête visitée : " ;
                iEdge.print();
                pile.push(iEdge.m_b);
            }
        }
    }
};

void GraphLA::bfs(std::string headStart, std::set<std::string> visitedHeads) {
    std::queue<std::string> q ;
    q.push(headStart);
    visitedHeads.insert(headStart);
    std::cout << "Sommet visité : " << headStart <<std::endl;
    while (not q.empty()){
        std::string head {q.front()} ;
        q.pop();
        for (auto iEdge : m_graph[head]) {
            std::cout << "Arête visitée : " ;
            iEdge.print();
            std::cout << "Sommet visité : " << iEdge.m_b <<std::endl;  
            if (visitedHeads.count(iEdge.m_b) == 0) {
                q.push(iEdge.m_b);
                visitedHeads.insert(iEdge.m_b);
            }
        }
    }
};