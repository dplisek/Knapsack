//
// Created by dominik on 12/21/15.
//

#ifndef SIMULATEDANNEALING_KNAPSACKINSTANCE_H
#define SIMULATEDANNEALING_KNAPSACKINSTANCE_H

#include "KnapsackItem.h"
#include <vector>
#include <iostream>

using namespace std;

class KnapsackInstance {
    int id, capacity;
    vector<KnapsackItem *> *items;

public:
    KnapsackInstance();
    virtual ~KnapsackInstance();
    friend istream& operator >> (istream& in, KnapsackInstance &instance);
    friend ostream& operator << (ostream& out, KnapsackInstance &instance);

    vector<KnapsackItem *> * getItems() const;

    void solve();
};


#endif //SIMULATEDANNEALING_KNAPSACKINSTANCE_H
