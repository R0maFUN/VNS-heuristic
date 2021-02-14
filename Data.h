#pragma once

#include <vector>
#include <string>
#include <fstream>

struct Data {
public:
    Data(std::string filename="data.txt");
    std::vector<bool>& operator[](unsigned int index);
    std::vector<std::vector<bool> > matrix;
    unsigned int detailsAmount;
    unsigned int machinesAmount;
};