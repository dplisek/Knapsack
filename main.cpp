#include <iostream>
#include <fstream>
#include <sstream>
#include "KnapsackInstance.h"
#include "KnapsackState.h"

using namespace std;

int main() {
    srand((unsigned int) time(NULL));
    ifstream file("/home/dominik/ClionProjects/SimulatedAnnealing/data/knap_40.inst.dat");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(file, line)) {
        for (double coolingFactor = 0.800; coolingFactor < 1.0; coolingFactor += 0.001) {
            KnapsackInstance instance;
            instance.setCoolingFactor(coolingFactor);
            istringstream iss(line);
            iss >> instance;
            instance.solve();
        }
        break;
    }
    file.close();
    return EXIT_SUCCESS;
}