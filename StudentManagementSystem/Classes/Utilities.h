//
// Created by Behzod Berdikulov u2410054 on 5/11/2025.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

namespace Utilities {

    inline void cleanUpSlashN () {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };
    inline int getInt (const string toWhere) {
        int value;
        while (true) {
            cout << toWhere << endl;
            if (cin >> value) { //checking if user entered only integer
                char next_char = cin.peek();
                if (next_char == '\n' || cin.eof() || isspace(static_cast<unsigned char>(next_char))) {
                    cleanUpSlashN();
                    return value;
                } else {
                    cerr << "Invalid input. Extra characters found after integer. Please enter only an integer." << endl;
                    cleanUpSlashN();
                }
            } else {
                cerr << "Invalid input. Please enter only an integer." << endl;
                cleanUpSlashN();
            }
        }
    };
    inline string getString (const string toWhere) {
        std::string value;
        std::cout << toWhere << std::endl;

        if (std::cin >> value) {
            cleanUpSlashN();
        } else {
            std::cerr << "Error reading string input." << std::endl;
            cleanUpSlashN();
        }
        return value;
    };
};



#endif //UTILITIES_H
