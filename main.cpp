#include "graphLA.h"
#include "graphMA.h"
#include "edge.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

int main(int argc, char** argv) {

    //Si l'utilisateur enter un nom de fichier, c'est lui là qui est chargé, sinon 
    //il y en a un par défaut.
    std::string fileName {"fichier.graph"};

    if (argc > 1) {
        fileName = argv[1];
    }

    GraphLA graphTestLA(fileName);

    //Conversion en graphe de matrice d'adjacence
    GraphMA graphTestMA = graphTestLA.convertToMA();

    //Accès aux arêtes
    vector<Edge> edgs1 {graphTestLA.edges("a")};
    vector<Edge> edgs2 {graphTestMA.edges("a")};
    cout << "Question 1 :" << endl ;
    cout <<"Accès aux arêtes de 'a' par liste d'adjacence : " << endl;
    for (Edge it : edgs1) {
        it.print();
    }
    cout << "Accès aux arêtes de 'a' par matrice d'adjacence : " << endl;
    for (Edge it : edgs2) {
        it.print();
    }
    cout << endl;

    cout << "Question 2 :" << std::endl;
    graphTestLA.represent();
    cout << endl;

    set<std::string> S1,S2,S3; //Ensemble des arêtes qui seront visitées
    cout << "Question 3 : Parcours en profondeur récursif :" << endl;
    graphTestLA.dfsRec("a",S1);
    //graphTestMA.dfsRec("a",S1);
    cout << endl;
    cout << "Question 4 : Parcours en profondeur itératif :" << endl;
    graphTestLA.dfsIte("a",S2);
    cout << endl;
    cout << "Question 5 : Parcours en largeur :" << endl;
    graphTestLA.bfs("a",S3);
    cout << endl;

    cout << "Question 7 : Floyd-Warshall : " << endl; 
    //Choisir les points d'arrivée et de départ
    std::string headStart {"a"}, headEnd {"e"};
    vector<std::string> path = graphTestMA.FWwithPath(headStart,headEnd);
    cout << "Affichage du chemin " << headStart << " -> " << headEnd << " : ";
    for (std::string str : path) {
        cout << " " << str ;
    }
    cout << endl;

    return 0;
}
