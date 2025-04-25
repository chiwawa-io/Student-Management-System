//
// Created by Djafarov Akbar u2410067 on 23.04.2025.
//

#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std; 

class Course {
public:
    Course(string& code, string& name, int& cred) : courseCode(code), courseName(name), credits(cred) {
        if (code.empty() || name.empty() || cred < 0) throw invalid_argument("Invalid parameters");
    }; //parametrized

    string getCourseCode() const{
        return courseCode;
    }
    string getCourseName() const {
        return courseName;
    }
    int getCredits() const {
        return credits;
    };

    void displayDetails() const {
        cout << "Code: " << courseCode << ", Name: " << courseName << ", Credits: " << credits;
    }


private:
    string courseCode;
    string courseName;
    int credits;
};

#endif //COURSE_H
