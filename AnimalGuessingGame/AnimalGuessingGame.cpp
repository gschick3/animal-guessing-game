#include <iostream>
#include <fstream>

#include "AnimalTree.h"

using namespace std;

int main()
{
    AnimalTree tree;

    string filename = "animals.txt";

    if (!tree.load(filename)) {
        cout << "Error loading animal file." << endl;
        return 1;
    }

    cout << "Welcome to the Animal Guessing Game" << endl;
    cout << "I will ask you a series of questions to determine what animal you're thinking of." << endl;
    cout << "Only answer y or n to each." << endl;
    cout << endl;

    string ws; // for whitespace
    char yn = 'y';
    while (yn == 'y') { // game loop
        tree.reset();
        bool nextIsAnimal = false;

        while (true) { // round loopt
            cout << tree.getNextQA() << endl; // print either animal guess or next question
            
            // if the node is an animal guess
            if (nextIsAnimal) { 
                cin >> yn;
                getline(cin, ws); // capture whitespace
                if (yn == 'y') {
                    cout << "Yay!" << endl;
                }
                else {
                    string name;
                    string question;
                    char path;
                    cout << "What was your animal? (Enter only the name in lowercase)" << endl;
                    getline(cin, name);

                    cout << "What yes/no question would differentiate it from a(n) " << tree.getNext()->getQA() << "? (Enter a question with question mark)" << endl;
                    getline(cin, question);
                    cout << "Would the answer be 'y' or 'n' for the new animal?" << endl;
                    cin >> path;

                    tree.addNode(name, question, path);
                }
                break;
            }

            cin >> yn; // guaranteed to have asked question, now looks for answer
            nextIsAnimal = tree.answer(yn);
        }

        cout << "Would you like to play again?" << endl;
        cin >> yn;
    }
    cout << "Would you like to save the current tree?" << endl;
    cin >> yn;
    if (yn == 'y')
        tree.saveToFile(filename);
}