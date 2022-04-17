#include "AnimalTree.h"
#include <fstream>
#include <sstream>
#include <iostream>


/************************************************
* Constructors and Destructors
*************************************************/
AnimalTree::AnimalTree() {
	rootNode = nullptr;
	currNode = nullptr;
	nextNode = nullptr;
}

AnimalTree::~AnimalTree() {
    deleteNode(rootNode);

    delete currNode;
    delete nextNode;
    delete rootNode;
    currNode = nullptr;
    nextNode = nullptr;
    rootNode = nullptr;
}

void AnimalTree::deleteNode(AnimalNode* a) {
    if (a->getYesNode() != nullptr)
        deleteNode(a->getYesNode());

    if (a->getNoNode() != nullptr)
        deleteNode(a->getNoNode());

    delete a;
    a = nullptr;
}


/************************************************
* Load and Save to Files
*************************************************/
bool AnimalTree::load(string filename) {
    ifstream inFile(filename);
    if (inFile.fail()) {
        return false;
    }

    string line, path, QA;
    getline(inFile, QA);
    rootNode = new AnimalNode(QA, nullptr, nullptr);

    while (getline(inFile, line)) {
        currNode = rootNode;        // start at root every time
        stringstream ss(line);

        getline(ss, path, ',');     // path before node
        getline(ss, QA, ',');       // question or animal
        for (char c : path) {       // iterate through path
            if (c == '0') {
                if (currNode->getYesNode() == nullptr) { // if this is as far as can be traveled, add another node
                    currNode->setYesNode(new AnimalNode(QA, nullptr, nullptr));
                    break;
                }
                else                                    // else, travel to the next node
                    currNode = currNode->getYesNode();
            }
            else if (c == '1') {
                if (currNode->getNoNode() == nullptr) {
                    currNode->setNoNode(new AnimalNode(QA, nullptr, nullptr));
                    break;
                }
                else
                    currNode = currNode->getNoNode();
            }
        }
    }
    inFile.close();
    currNode = rootNode; // reset currNode to rootNode
    return true;
}

void AnimalTree::saveToFile(string filename) {
    ofstream outFile(filename);
    string path = "";
    string content;

    content = traverse(rootNode, content, path);

    outFile << content;
    outFile.close();
}

string AnimalTree::traverse(AnimalNode* a, string content, string path) {
    if (path != "") content += path + ",";
    content += a->getQA() + "\n"; // add current node's data

    if (a->getYesNode() != nullptr)
        content = traverse(a->getYesNode(), content, path + "0"); // redefine content to all the recursive data

    if (a->getNoNode() != nullptr)
        content = traverse(a->getNoNode(), content, path + "1");

    return content; // return full data
}


/************************************************
* Editing the tree
*************************************************/
void AnimalTree::addNode(string name, string question, char path) {
    AnimalNode* newA = new AnimalNode(name, nullptr, nullptr);
    AnimalNode* newQ = new AnimalNode(question, nullptr, nullptr);

    newQ->setYesNode(path == 'y' ? newA : nextNode);
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


/************************************************
* Accessors
*************************************************/
string AnimalTree::getNextQA() {
    if (nextNode->isAnimal())
        return "Is your animal a(n) " + nextNode->getQA() + "?";
    else
        return nextNode->getQA();
}
