#include "Solution.h"

void Solution::generateRandomSolution(unsigned int clusters)
{
    for (auto it = this->machines.begin(); it != this->machines.end(); ++it)
        *it = rand() % clusters;
    for (auto it = this->details.begin(); it != this->details.end(); ++it)
        *it = rand() % clusters;
    this->clustersAmount = clusters;
}

double Solution::calculateGE()
{
    int allOnes = 0;
    int n1_in = 0;
    int n0_in = 0;
    for (int i{ 0 }; i < this->data->machinesAmount; ++i) {
        for (int j{ 0 }; j < this->data->detailsAmount; ++j) {
            if (this->machines[i] == this->details[j]) {
                if ((*this->data)[i][j]) {
                    n1_in++;
                }
                else
                    n0_in++;
            }
            if ((*this->data)[i][j])
                allOnes++;
        }
    }
    return static_cast<double>(n1_in) / (allOnes + n0_in);
}

void Solution::print()
{
    std::cout << "Machines: ";
    for (auto it = this->machines.begin(); it != this->machines.end(); ++it)
        std::cout << *it + 1 << " ";
    std::cout << "\nDetails:";
    for (auto it = this->details.begin(); it != this->details.end(); ++it)
        std::cout << *it + 1 << " ";
    std::cout << "\n\n";
}

void Solution::print(std::string filename)
{
    std::ofstream out(filename);
    for (auto it = this->machines.begin(); it != this->machines.end(); ++it)
        out << *it + 1 << " ";
    out << "\n";
    for (auto it = this->details.begin(); it != this->details.end(); ++it)
        out << *it + 1 << " ";
    out.close();
}

bool Solution::replace2machines_all(int step, double best)
{
    for (int i{ 0 }; i < this->machines.size(); i++) {
        for (int j{ i + 1 }; j < this->machines.size(); j += step) {
            std::swap(this->machines[i], this->machines[j]);
            if (calculateGE() > best) {
                return true;
            }
            else
                std::swap(this->machines[i], this->machines[j]);
        }
    }
    return false;
}

bool Solution::replace2details_all(int step, double best)
{
    for (int i{ 0 }; i < this->details.size(); i++) {
        for (int j{ i + 1 }; j < this->details.size(); j += step) {
            std::swap(this->details[i], this->details[j]);
            if (calculateGE() > best) {
                return true;
            }
            else 
                std::swap(this->details[i], this->details[j]);
        }
    }
    return false;
}

bool Solution::changeClusterDetails(int amount, double best)
{
    int bestJ = -1;
    int bestJCluster;
    double bestVal = best;

    for (int j{ 0 }; j < this->details.size(); j++) {
        int savedD = this->details[j];
        if (savedD < this->clustersAmount)
            this->details[j]++;
        else if (savedD > 1)
            this->details[j]--;
        double GE = calculateGE();
        if (GE > bestVal) {
            bestJ = j;
            bestJCluster = this->details[j];
            bestVal = GE;
            //return true;
        }
        this->details[j] = savedD;
    }
    if (bestJ != -1) {
        this->details[bestJ] = bestJCluster;
        return true;
    }
    return false;
}

bool Solution::changeClusterMachines(int amount, double best)
{
    int bestJ = -1;
    int bestJCluster;
    double bestVal = best;

    for (int j{ 0 }; j < this->machines.size(); j++) {
        int savedD = this->machines[j];
        if (savedD < this->clustersAmount)
            this->machines[j]++;
        else if(savedD > 1)
            this->machines[j]--;
        double GE = calculateGE();
        if (GE > bestVal) {
            bestJ = j;
            bestJCluster = this->machines[j];
            bestVal = GE;
            //return true;
        }
        this->machines[j] = savedD;
    }
    if (bestJ != -1) {
        this->machines[bestJ] = bestJCluster;
        return true;
    }
    return false;
}

void Solution::progressResult(double& localBest, std::string filename)
{
    if (calculateGE() > localBest)
    {
        localBest = calculateGE();
        std::cout << "local GE: " << currentBest << std::endl;
        print();
    }
    if (localBest > currentBest)
    {
        print(filename);
        std::cout << "new GE: " << currentBest << std::endl;
        currentBest = localBest;
    }
}

void Solution::VNS(std::string filename)
{
    for (int i{ 2 }; i < maxClustersAmount; ++i) {
        for (int j = 0; j < 3; ++j)
        {
            double localBest = 0;
            int randBest = 0;
            std::vector<int> randMachines;
            std::vector<int> randDetails;
            for (int k = 0; k < 100; ++k) {
                this->generateRandomSolution(i);
                if (calculateGE() > randBest) {
                    randBest = calculateGE();
                    randMachines = this->machines;
                    randDetails = this->details;
                }
            }
            this->machines = randMachines;
            this->details = randDetails;
            std::cout << "Rand solution:\n";
            print();
            std::cout << "rand GE: " << calculateGE() << "\n\n";
            int step = 5;
            std::cout << i << " Clusters" << std::endl;
            int counter = 0;
            while (step >= 1) {

                if (step >= 8)
                    step = 8;
                if (changeClusterDetails(1, localBest)) {
                    step += 2;
                    progressResult(localBest, filename);
                    continue;
                }

                if (changeClusterMachines(1, localBest)) {
                    step += 2;
                    progressResult(localBest, filename);
                    continue;
                }

                if (replace2machines_all(step, localBest)) {
                    if (step < this->machines.size() / 2)
                        step+=2;
                    else
                        step = this->machines.size() / 5;
                    progressResult(localBest, filename);
                    continue;
                }
                if (replace2details_all(step, localBest)) {
                    if (step < this->details.size() / 2)
                        step+=2;
                    else
                        step = this->details.size() / 5;
                    progressResult(localBest, filename);
                    continue;
                }

                step--;
                std::cout << "step: " << step << std::endl;
            }
        }
    }
}
