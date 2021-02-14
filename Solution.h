#pragma once

#include "Data.h"
#include <time.h>
#include <iostream>

class Solution {
public:
    unsigned int maxClustersAmount;
    Solution(std::shared_ptr<Data> data) : data(data) {
        this->maxClustersAmount = data->detailsAmount < data->machinesAmount ? data->detailsAmount : data->machinesAmount;
        this->clustersAmount = 2;
        machines.resize(data->machinesAmount);
        details.resize(data->detailsAmount);
        this->currentBest = -1;
    }
    void generateRandomSolution(unsigned int clusters);
    double calculateGE();
    void print();
    void print(std::string filename);
    bool replace2machines_all(int step, double best);
    bool replace2details_all(int step, double best);
    bool changeClusterDetails(int amount, double best);
    bool changeClusterMachines(int amount, double best);
    void progressResult(double& localBest, std::string filename);
    void VNS(std::string filename = "results.txt");
private:
    std::shared_ptr<Data> data;
    std::vector<int> machines;
    std::vector<int> details;
    unsigned int clustersAmount;
    double currentBest;
};