#include "Data.h"

Data::Data(std::string filename)
{
    std::ifstream input(filename);
    input >> this->machinesAmount >> this->detailsAmount;
    int machineId;
    bool val;
    this->matrix.resize(this->machinesAmount);
    std::string str;
    std::getline(input, str);
    for (int i{ 0 }; i < this->machinesAmount; ++i)
    {
        std::getline(input, str);
        std::string num;
        this->matrix[i].resize(this->detailsAmount, false);
        str.erase(0, str.find_first_of(" ", 0) + 1);
        
        for (auto it = str.begin(); it != str.end(); ++it) {
            if (*it == ' ' && num.length() > 0) {
                //this->matrix[i].push_back(std::atoi(num.c_str()));
                this->matrix[i][std::atoi(num.c_str()) - 1] = true;
                num.clear();
            }
            else {
                num += *it;
            }
        }
        if(num.length() > 0 && num != " ")
            this->matrix[i][std::atoi(num.c_str()) - 1] = true;
        //this->matrix[i][i] = false;
    }
    input.close();
}

std::vector<bool>& Data::operator[](unsigned int index)
{
    return this->matrix[index];
}
