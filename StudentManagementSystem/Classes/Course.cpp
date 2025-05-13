//
// Created by U2410054 Berdiqulov Behzod
//

#include "Course.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using  namespace std;

Course::Course() : courseId(""), courseName(""), courseCredits(0) {}

Course::Course(string id, string name, int cred) : courseId(id), courseName(name), courseCredits(cred) {
    if (courseCredits < 0) throw invalid_argument("Credits must be positive");
}

string Course::getCourseId() const {
    return courseId;
}

string Course::getCourseName() const {
    return courseName;
}

int Course::getCourseCredit() const {
    return courseCredits;
}

void Course::setCourseName(const string &name) {
    courseName = name;
}

void Course::setCourseId(const string &id) {
    courseId = id;
}

void Course::setCourseCredit(int cred) {
    courseCredits = cred;
}

void Course::display() const {
    cout << "Course ID: " << courseId << ", Name: " << courseName << ", Credits: " << courseCredits << endl;
}

string Course::ForOut() const {
    stringstream ssovec;
    ssovec << courseId << "," << courseName << "," << courseCredits;
    return ssovec.str();
}
