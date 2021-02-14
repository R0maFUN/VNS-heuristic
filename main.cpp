#include "Data.h"
#include "Solution.h"
#include <iostream>

int main() {
    srand(time(NULL));
    std::shared_ptr<Data> data = std::make_shared<Data>("zolf50.txt");
    Solution sol(data);
    
    sol.VNS("result50x150.txt");


    return 0;
}