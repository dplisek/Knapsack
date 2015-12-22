//
// Created by dominik on 12/21/15.
//

#ifndef SIMULATEDANNEALING_KNAPSACKINSTANCE_H
#define SIMULATEDANNEALING_KNAPSACKINSTANCE_H

#include "KnapsackItem.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class KnapsackState;

class KnapsackInstance {
    int id, capacity;
    vector<KnapsackItem *> *items;
    ofstream *costsFile;

    bool isFrozen(int accepted, int processed) const;
    double getValueToOptimize(const KnapsackState &state) const;
    void revert(KnapsackState &state, int index) const;
    bool acceptingEnough(int accepted, int processed) const;
    void evalState(KnapsackState &state, KnapsackState &best, double temp, int &accepted, int &processed, bool simulation) const;
public:
    KnapsackInstance();
    virtual ~KnapsackInstance();
    friend istream& operator >> (istream& in, KnapsackInstance &instance);
    friend ostream& operator << (ostream& out, KnapsackInstance &instance);
    vector<KnapsackItem *> * getItems() const;
    void solve();
    int getCapacity() const;
};


#endif //SIMULATEDANNEALING_KNAPSACKINSTANCE_H
