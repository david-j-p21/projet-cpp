#include "edge.h"
#include <iostream>
#include <string>

Edge::Edge(std::string a,std::string b,double value):
        m_a(a), m_b(b), m_value(value){};

void Edge::print(){
    std::cout << m_a << " " << m_b << " " << m_value << std::endl;
}