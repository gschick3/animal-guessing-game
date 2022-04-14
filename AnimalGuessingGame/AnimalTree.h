#pragma once
#include "AnimalNode.h"

class AnimalTree
{
private:
	AnimalNode* rootNode;
	AnimalNode* currNode;
	AnimalNode* nextNode;

public:
	AnimalTree();

	AnimalNode* getRoot() { return rootNode; }
	AnimalNode* getCurr() { return currNode; }
	AnimalNode* getNext() { return nextNode; }
	string getNextQA();

	//pre: take in file name as parameter
	//post: load binary tree of animals
	bool load(string);

	//pre: take in name of animal to add, question to differentiate from other option, and whether the animal should be under the y or n option
	//post: create node between currNode and nextNode for question and create node after question for the animal
	void addNode(string name, string question, char path);

	//pre: take in y or n as an answer
	//post: move currNode and nextNode accordingly, then return whether it is an animal
	bool answer(char);

	// resets all pointers to rootNode
	void reset();

};