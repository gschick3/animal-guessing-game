#pragma once
#include <string>

using namespace std;

class AnimalNode
{
private:
    string QA;
    AnimalNode* yes;
    AnimalNode* no;
public:
    AnimalNode(string, AnimalNode*, AnimalNode*);

    // Accessors and Modifiers
    AnimalNode* getYesNode() { return yes; }
    void setYesNode(AnimalNode* a) { yes = a; }
    AnimalNode* getNoNode() { return no; }
    void setNoNode(AnimalNode* a) { no = a; }
    string getQA() { return QA; }
    void setQ_A(string s) { QA = s; }

    bool isAnimal();
};

