//
// Created by dominik on 12/21/15.
//

#include "KnapsackState.h"
#include "KnapsackItem.h"
#include "KnapsackInstance.h"

KnapsackState::KnapsackState(KnapsackInstance *instance) : instance(instance) {
    weight = cost = 0;
    itemPresenceVector = new int[instance->getItems()->size()];
}

KnapsackState::~KnapsackState() {
    delete [] itemPresenceVector;
}

void KnapsackState::randomize() {
    weight = cost = 0;
    int i = 0;
    for (KnapsackItem *item : *instance->getItems()) {
        itemPresenceVector[i] = rand() % 2;
        if (itemPresenceVector[i]) {
            weight += item->getWeight();
            cost += item->getCost();
        }
        ++i;
    }
}

ostream &operator << (ostream &out, KnapsackState &state) {
    for (int i = 0; i < state.getInstance()->getItems()->size(); ++i) {
        out << state.itemPresenceVector[i];
    }
    out << endl << "Weight: " << state.weight << endl << "Cost: " << state.cost;
    return out;
}

KnapsackInstance *KnapsackState::getInstance() const {
    return instance;
}

void KnapsackState::transitionAtIndex(int index) {
    if (itemPresenceVector[index]) {
        itemPresenceVector[index] = 0;
        weight -= (*instance->getItems())[index]->getWeight();
        cost -= (*instance->getItems())[index]->getCost();
    } else {
        itemPresenceVector[index] = 1;
        weight += (*instance->getItems())[index]->getWeight();
        cost += (*instance->getItems())[index]->getCost();
    }
}

int KnapsackState::getWeight() const {
    return weight;
}

int KnapsackState::getCost() const {
    return cost;
}