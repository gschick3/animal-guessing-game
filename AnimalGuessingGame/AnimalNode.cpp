#include "AnimalNode.h"

using namespace std;

AnimalNode::AnimalNode(string q, AnimalNode* y, AnimalNode* n) {
    QA = q;
    yes = y;
    no = n;
}

bool AnimalNode::isAnimal() {
    return (yes == nullptr && no == nullptr);
}