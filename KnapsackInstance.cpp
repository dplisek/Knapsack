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
    if (costsFile) {
        costsFile->close();
        delete costsFile;
    }
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
    stringstream sstm;
    sstm << "/home/dominik/ClionProjects/SimulatedAnnealing/data/costs." << instance.id << ".dat";
    instance.costsFile = new ofstream(sstm.str());
    if (!instance.costsFile->is_open()) {
        cerr << "Couldn't open costs file for instance " << instance.id << endl;
        exit(EXIT_FAILURE);
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
    KnapsackState best(this);
    state.randomize();
    cerr << "Initial state: " << state << endl << endl;

    int accepted, processed;
    double temp = 0.0000000001;
    do {
        temp *= WARMING_FACTOR;
        evalState(state, best, temp, accepted, processed, true);
    } while (!acceptingEnough(accepted, processed));

    cerr << "Found starting temperature: " << temp << endl;

    do {
        evalState(state, best, temp, accepted, processed, false);
        temp *= COOLING_FACTOR;
    } while (!isFrozen(accepted, processed));

    cerr << "Finished solving instance with id " << id << endl;
    cerr << "----------------------------------------------------" << endl;
}

void KnapsackInstance::evalState(KnapsackState &state, KnapsackState &best, double temp, int &accepted, int &processed, bool simulation) const {
    cerr << "-------------------------" << endl << "Temperature set to: " << temp << endl << "-------------------------" << endl ;
    accepted = 0;
    processed = 0;
    while (processed < items->size() * 2 && accepted < items->size()) {
        double origValue = getValueToOptimize(state);
        int index = (int) (rand() % items->size());
        state.transitionAtIndex(index);
        cerr << "Evaluating neighbor at " << index << ": " << state << endl;
        double diff = getValueToOptimize(state) - origValue;
        cerr << "Diff: " << diff << endl;
        double randFloat = ((double) rand()) / RAND_MAX;
        cerr << "Random: " << randFloat << endl;
        if (state.getWeight() > capacity) {
            cerr << "State too heavy." << endl;
            revert(state, index);
        } else if (diff > 0 && randFloat > exp(-diff / temp)) {
            cerr << "State worse by too much." << endl;
            ++processed;
            revert(state, index);
        } else {
            cerr << "Sticking to transition." << endl;
            if (simulation) {
                if (diff > 0) {
                    ++processed;
                    ++accepted;
                }
            } else {
                ++processed;
                ++accepted;
                *costsFile << getValueToOptimize(state) << endl;
                if (getValueToOptimize(state) < getValueToOptimize(best)) {
                    best.copyOf(state);
                    cerr << "Found new best result: " << best << endl;
                }
            }
        }
        cerr << "----" << endl;
    }
}

void KnapsackInstance::revert(KnapsackState &state, int index) const {
    state.transitionAtIndex(index);
    cerr << "Reverted transition." << endl;
}

double KnapsackInstance::getValueToOptimize(const KnapsackState &state) const {
    return 1.0 / state.getCost();
//    if (state.getWeight() > capacity) {
//        base += (((double) (state.getWeight() - capacity)) / capacity) * base;
//    }
//    return base;
}

bool KnapsackInstance::acceptingEnough(int accepted, int processed) const {
    double ratio = ((double) accepted) / processed;
    cerr << "Accepted: " << accepted << ", Processed: " << processed << ", ratio: " << ratio << endl;
    return ratio > 0.5;
}

bool KnapsackInstance::isFrozen(int accepted, int processed) const {
    double ratio = ((double) accepted) / processed;
    cerr << "Accepted: " << accepted << ", Processed: " << processed << ", ratio: " << ratio << endl;
    return ratio < 0.05;
}

vector<KnapsackItem *> *KnapsackInstance::getItems() const {
    return items;
}


int KnapsackInstance::getCapacity() const {
    return capacity;
}