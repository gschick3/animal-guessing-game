#include <iostream>
#include <fstream>

#include "AnimalTree.h"

using namespace std;

int main()
{
    AnimalTree tree;

    if (!tree.load("animals.txt")) {
        cout << "Error loading animal file." << endl;
        return 1;
    }


    char yn = 'y';
    while (yn == 'y') { // game loop
        tree.reset();
        bool nextIsAnimal = false;

        while (true) { // round loopt
            cout << tree.getNextQA() << endl; // print either animal guess or next question

            if (nextIsAnimal) { // if the node is an animal guess
                cin >> yn;
                if (yn == 'y') {
                    cout << "Yay!" << endl;
                }
                else {
                    string name;
                    string question;
                    char path;
                    cout << "What was your animal?" << endl;
                    cin >> name;
                    getline(cin, question); // get whitespace

                    cout << "What yes/no question would differentiate it from a(n) " << tree.getNext()->getQA() << "?" << endl;
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
        tree.saveToFile("output.txt");
}