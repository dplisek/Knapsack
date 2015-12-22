//
// Created by dominik on 12/21/15.
//

#include "KnapsackItem.h"


int KnapsackItem::getWeight() const {
    return weight;
}

void KnapsackItem::setWeight(int weight) {
    KnapsackItem::weight = weight;
}

int KnapsackItem::getCost() const {
    return cost;
}

void KnapsackItem::setCost(int cost) {
    KnapsackItem::cost = cost;
}