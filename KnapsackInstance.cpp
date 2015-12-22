//
// Created by dominik on 12/21/15.
//

#include <sstream>
#include <cmath>
#include "KnapsackInstance.h"
#include "KnapsackState.h"
#include "config.h"

KnapsackInstance::KnapsackInstance() {
    id = 0;
    capacity = 0;
    items = new vector<KnapsackItem *>();
}

KnapsackInstance::~KnapsackInstance() {
    for (KnapsackItem *item : *items) {
        delete item;
    }
    delete items;
}

istream &operator >> (istream &in, KnapsackInstance &instance) {
    int itemCount;
    if (!(in >> instance.id >> itemCount >> instance.capacity)) {
        cerr << "Failed to read instance." << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < itemCount; ++i) {
        int weight, cost;
        if (!(in >> weight >> cost)) {
            cerr << "Failed to read instance." << endl;
            exit(EXIT_FAILURE);
        }
        instance.items->push_back(new KnapsackItem(weight, cost));
    }
    return in;
}

ostream &operator << (ostream &out, KnapsackInstance &instance) {
    out << "ID: " << instance.id << endl;
    out << "Capacity: " << instance.capacity << endl;
    out << "Item count: " << instance.items->size();
    return out;
}

void KnapsackInstance::solve() {
    cerr << "-----------------------------------" << endl;
    cerr << "Starting to solve instance: " << *this << endl;

    KnapsackState state(this);
    state.randomize();
    while (state.getWeight() > capacity) {
        cerr << "Too heavy, regenerating initial state." << endl;
        state.randomize();
    }
    cerr << "Initial state: " << state << endl << endl;

    double temp = START_TEMP;
    while (temp > FINAL_TEMP) {
        cerr << "Temperature set to: " << temp << endl;
        for (int i = 0; i < EQUI_LEN; ++i) {
            cerr << "Inner loop: " << i << endl;
            double costInv = 1.0 / state.getCost();
            int index = (int) (rand() % items->size());
            state.transitionAtIndex(index);
            cerr << "Evaluating neighbor at " << index << ": " << state << endl;
            if (state.getWeight() > capacity) {
                cerr << "This state is too heavy, reverting and skipping." << endl;
                state.transitionAtIndex(index);
                cerr << "----" << endl;
                continue;
            }
            double diff = (1.0 / state.getCost()) - costInv;
            cerr << "Diff: " << diff << endl;
            double randFloat = ((double) rand()) / RAND_MAX;
            cerr << "Random: " << randFloat << endl;
            if (diff < 0 || randFloat < exp(-diff / temp)) {
                cerr << "Sticking to transition." << endl;
                cout << 1.0 / state.getCost() << endl;
            } else {
                state.transitionAtIndex(index);
                cerr << "Reverted back to: " << state << endl;
            }
            cerr << "----" << endl;
        }
        temp *= COOLING_FACTOR;
    }

    cerr << "Finished solving instance with id " << id << endl;
    cerr << "----------------------------------------------------" << endl;
}

vector<KnapsackItem *> *KnapsackInstance::getItems() const {
    return items;
}