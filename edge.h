#pragma once

#include <vector>
#include <string>

using namespace std;

class Edge{
    friend class GraphLA;

    string m_a;
    string m_b;
    double m_value;

    public :
    Edge(string a,string b,double value);
    void print();
};