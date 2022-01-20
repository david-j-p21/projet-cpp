#include "graphMA.h"
#include "function.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include <set>


void GraphMA::print(){
    int n = m_headNames.size();
    std::cout << "La liste ordonnée des sommets est : " ;
    for (std::string str : m_headNames){
        std::cout << str << " ";
    }
    std::cout << std::endl << "Affichage de la matrice :" << std::endl;
    for (int i = 0; i<n;i++) {
        for (int j = 0 ; j < n ; j++) {
            std::cout << m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
};

std::vector<Edge> GraphMA::edges(std::string headName) {
    std::vector<Edge> vect;
    int i = getIndex(m_headNames,headName);
    int nHead = m_headNames.size();
    for (int j = 0 ; j < nHead ; j++) {
        if (! std::isnan(m_matrix[i][j])){
            Edge newEdge(headName,m_headNames[j],m_matrix[i][j]);
            vect.push_back(newEdge);
        }
    }
    return vect;
};

void GraphMA::dfsRec(std::string headStart, std::set<std::string>& visitedHeads) { //headStart n'a pas été visité
    visitedHeads.insert(headStart);
    std::cout << "Sommet visité : " << headStart << std::endl ;
    int index = getIndex(m_headNames, headStart);
    int n = m_headNames.size();
    for (int i = 0 ; i < n ; i++) {
        if (! isnan(m_matrix[index][i])) {
            std::cout << "Arête visitée : " << headStart << " " << m_headNames[i] << " " << m_matrix[index][i] << std::endl;
            if (visitedHeads.count(m_headNames[i]) == 0) {
                dfsRec(m_headNames[i],visitedHeads);
            }
        }
    }
};

//Floyd-Warshall
std::vector<std::string> GraphMA::FWwithPath(std::string head1, std::string head2){
    int n = m_headNames.size();
    std::vector<std::vector<double>> dist;
    std::vector<std::vector<int>> next ;
    std::vector<std::string> path;
    dist.resize(n);

    for (int i = 0 ; i<n ;i++) {
        std::vector<int> vect(n,-1); //La valeur -1 correspond à une valeur NULL
        next.push_back(vect); //Initialisation de next.

        dist[i].resize(n);// dist configurée à la bonne taille
    }

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            //S'il y a une arête entre les deux sommets
            if (! std::isnan(m_matrix[i][j])) {
                dist[i][j] = m_matrix[i][j],
                next[i][j] = j;
            }
            //sur la diagonale
            else if (j == i) { 
                dist[i][j] = 0;
                next[i][j] = j;
            }
            //s'il n'y a pas d'arête
            else {
                dist[i][j] = INFINITY; 
            }
        }   
    }
    //Floyd-Marshall
    for (int k = 0 ; k < n ; k++) {
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < n ; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    //Reconstruction du plus court chemin cherché : 
    int ind1 = getIndex(m_headNames,head1);
    int ind2 = getIndex(m_headNames,head2);
    if (next[ind1][ind2] == -1) {
        return path;
    }
    path.push_back(m_headNames[ind1]);
    while (ind1 != ind2) {
        ind1 = next[ind1][ind2];
        path.push_back(m_headNames[ind1]);
    }
    return path; 
};