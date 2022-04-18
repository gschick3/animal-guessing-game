#include <iostream>
#include <fstream>
#include <vector>

#include "AnimalTree.h"

using namespace std;

bool vectorContains(vector<string>, string);

int main()
{
    vector<string> knownFiles;

    AnimalTree tree;

    string filename = "animals.txt";
    string temp; // used when value can be thrown out quickly
    char yn;

    ifstream inFile("known.txt");
    while (getline(inFile, temp))
        knownFiles.push_back(temp);

    inFile.close();

    cout << "Would you like to load a tree?" << endl;
    getline(cin, temp);
    yn = temp.at(0);
    if (yn == 'y') {
        cout << "What file would you like to load?" << endl;
        getline(cin, temp);

        if (vectorContains(knownFiles, temp))
            filename = temp;
        else
            cout << "File not found. Using default." << endl;
    }

    if (!tree.load(filename)) {
        cout << "Error loading animal file." << endl;
        return 1;
    }

    cout << endl;
    cout << "Welcome to the Animal Guessing Game" << endl;
    cout << "I will ask you a series of questions to determine what animal you're thinking of." << endl;
    cout << "Only answer y or n to each." << endl;
    cout << endl;

    yn = 'y';
    while (yn == 'y') { // game loop
        tree.reset();
        bool nextIsAnimal = false;

        while (true) { // round loop
            cout << tree.getNextQA() << endl; // print either animal guess or next question
            
            // if the node is an animal guess
            if (nextIsAnimal) { 
                getline(cin, temp);
                yn = temp.at(0);
                if (yn == 'y') {
                    cout << "Yay!" << endl;
                }
                else if (yn == 'n') {
                    string name;
                    string question;
                    char path = '\0';
                    cout << "What was your animal? (Enter only the name in lowercase)" << endl;
                    getline(cin, name);

                    cout << "What yes/no question would differentiate it from a(n) " << tree.getNext()->getQA() << "? (Include question mark)" << endl;
                    getline(cin, question);

                    while (path != 'y' && path != 'n') {
                        cout << "Would the answer be 'y' or 'n' for the new animal?" << endl;
                        getline(cin, temp);
                        path = temp.at(0);
                    }

                    tree.addNode(name, question, path);
                }
                else {
                    cout << "Not even sure what that means." << endl;
                }
                break;
            }

            // guaranteed to have asked question, now looks for answer
            getline(cin, temp);
            yn = temp.at(0);
            nextIsAnimal = tree.answer(yn);
        }

        cout << "Would you like to play again?" << endl;
        getline(cin, temp);
        yn = temp.at(0);
    }
    cout << "Would you like to save the current tree?" << endl;
    getline(cin, temp);
    yn = temp.at(0);
    if (yn == 'y') {
        cout << "Enter a file name for the tree." << endl;
        cin >> temp;
        tree.saveToFile(temp);

        knownFiles.push_back(temp);
        
        ofstream outFile("known.txt");
        for (string line : knownFiles)
            outFile << line << endl;

        outFile.close();
    }
}


bool vectorContains(vector<string> v, string line) {
    for (string fileLine : v)
        if (line == fileLine) return true;

    return false;
}