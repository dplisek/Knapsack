//
// Created by dominik on 12/21/15.
//

#ifndef SIMULATEDANNEALING_KNAPSACKSTATE_H
#define SIMULATEDANNEALING_KNAPSACKSTATE_H

#include <vector>
#include "KnapsackInstance.h"

using namespace std;

class KnapsackState {
    int weight, cost;
    KnapsackInstance *instance;
    int *itemPresenceVector;

public:
    KnapsackState(KnapsackInstance *instance);
    virtual ~KnapsackState();
    friend ostream &operator << (ostream &out, KnapsackState &state);

    KnapsackInstance * getInstance() const;

    void randomize();

    void transitionAtIndex(int index);

    void copyOf(KnapsackState &state);

    int getWeight() const;

    int getCost() const;
};


#endif //SIMULATEDANNEALING_KNAPSACKSTATE_H
