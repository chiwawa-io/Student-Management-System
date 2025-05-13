//
// Created by Behzod berdikulov u2410054
// Edited by Djafarov Akbar u2410067
//
#include <iostream>
#include "Classes/MainManagement.h"
#include "Classes/CustomExceptions.h"

using namespace std;

int main() {
    cout << "---------Welcome to Student ManagementSystem!-------" << endl;
    try {
        MainManagement system;
        system.runLoop();
    } catch (CustomException &e) {
        cout << "Error: " << e.what() << endl;
        cout << "Programm terminated" << endl;
        return 1;
    } catch (exception &e) {
        cout << "\n Unexpected Error: " << e.what() << endl;
        cout << "Programm terminated" << endl;
        return 1;
    } catch (...) {
        cout << "\n Unknown Error!" << endl;
        cout << "Programm terminated" << endl;
        return 1;
    }

    cout << "Successfull run!" << endl;
    return 0;
}