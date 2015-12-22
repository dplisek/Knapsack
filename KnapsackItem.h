//
// Created by dominik on 12/21/15.
//

#ifndef SIMULATEDANNEALING_KNAPSACKITEM_H
#define SIMULATEDANNEALING_KNAPSACKITEM_H


class KnapsackItem {
    int weight, cost;

public:
    KnapsackItem(int weight, int cost) : weight(weight), cost(cost) { }
    int getWeight() const;
    void setWeight(int weight);
    int getCost() const;
    void setCost(int cost);
};


#endif //SIMULATEDANNEALING_KNAPSACKITEM_H
