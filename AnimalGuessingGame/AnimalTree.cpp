#include "AnimalTree.h"
#include <fstream>
#include <sstream>
#include <iostream>

AnimalTree::AnimalTree() {
	rootNode = nullptr;
	currNode = nullptr;
	nextNode = nullptr;
}

bool AnimalTree::load(string filename) {
    ifstream inFile(filename);
    if (inFile.fail()) {
        return false;
    }

    string line, path, choice, QA;
    getline(inFile, QA);
    rootNode = new AnimalNode(QA, nullptr, nullptr);

    while (getline(inFile, line)) {
        currNode = rootNode;        // start at root every time
        stringstream ss(line);

        getline(ss, path, ',');     // path before node
        getline(ss, choice, ',');   // which option the node should appear under (y/n)
        getline(ss, QA, ',');       // question or animal
        for (char c : path) {       // iterate through path
            if (c == '0')
                currNode = currNode->getYesNode();
            else if (c == '1')
                currNode = currNode->getNoNode();
            else if (c == '*')
                currNode = rootNode;
        }
        if (choice == "0")
            currNode->setYesNode(new AnimalNode(QA, nullptr, nullptr));
        else if (choice == "1")
            currNode->setNoNode(new AnimalNode(QA, nullptr, nullptr));
    }
    inFile.close();
    currNode = rootNode; // reset currNode to rootNode
    return true;
}

void AnimalTree::addNode(string name, string question, char path) {
    AnimalNode* newA = new AnimalNode(name, nullptr, nullptr);
    AnimalNode* newQ = new AnimalNode(question, nullptr, nullptr);
    newQ->setYesNode(path == 'y' ? newA : nextNode); // otherOption is the incorrectly guessed animal
    newQ->setNoNode(path == 'y' ? nextNode : newA);

    if (currNode->getYesNode() == nextNode)
        currNode->setYesNode(newQ);
    else
        currNode->setNoNode(newQ);
}

bool AnimalTree::answer(char yn) {
    currNode = nextNode; // move currNode forward

    // move nextNode forward
    if (yn == 'y')
        nextNode = currNode->getYesNode();
    else if (yn == 'n')
        nextNode = currNode->getNoNode();

    return nextNode->isAnimal();
}

void AnimalTree::reset() {
    currNode = rootNode;
    nextNode = rootNode;
}

string AnimalTree::getNextQA() {
    if (nextNode->isAnimal())
        return "Is your animal a(n) " + nextNode->getQA() + "?";
    else
        return nextNode->getQA();
}