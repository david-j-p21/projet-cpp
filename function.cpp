#include "function.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int getIndex(std::vector<std::string> vect, std::string val){
    auto it = std::find(vect.begin(),vect.end(), val);
    return it - vect.begin();
};