#pragma once

#include "edge.h"
#include <string>
#include <vector>
#include <set>

using namespace std;

class GraphMA{
    friend class GraphLA;

    private:
    vector<string> m_headNames;
    vector<vector<double>> m_matrix;

    public:
    //On ne définit pas de constructeur explicite car on passe toujours par la représentation en liste d'adjacence.

    //Affichage de la matrice d'adjacence
    void print();

    //Méthode retournant les arêtes associées à un sommet donné
    vector<Edge> edges(string headName);

    //Deep First Search recursive 
    void dfsRec(std::string headStart, std::set<std::string>& visitedHeads);

    //Floyd-Warshall avec déterminantion de chemin
    vector<string> FWwithPath(string head1, string head2);
};