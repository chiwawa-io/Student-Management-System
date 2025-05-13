// Student.cpp
// Created by U2410067 Akbar Djafarov on 5/6/2025.
//

#include "Student.h"
#include "Constants.h"
#include "Course.h" // For Course class definition
#include <iostream>
#include <sstream>
#include <string> // Required for to_string

using namespace std;


int Student::nextStudentId = 1;


void initializeEmptyCourses (Course* courses[]) {
    for (int i = 0; i < MAX_COURSES_PER_STUDENT; i++) {
        courses[i] = nullptr;
    }
}


Student::Student()
    : studentId(to_string(nextStudentId++)), 
      name(""),
      password(""),
      numEnrolledCourses(0) {
    initializeEmptyCourses(enrolledCourses);
}


Student::Student(string name, string password)
    : studentId(to_string(nextStudentId++)), // Generate new ID
      name(name),
      password(password),
      numEnrolledCourses(0) {
    initializeEmptyCourses(enrolledCourses);
}

Student::Student(string name, string password, string id)
    : studentId(id), // Use provided ID
      name(name),
      password(password),
      numEnrolledCourses(0) {
    initializeEmptyCourses(enrolledCourses);
}

void Student::changePassword(string new_password) {
    this->password = new_password;
}

string Student::getName() const{
    return name;
}

string Student::getPassword() const{
    return password;
}

string Student::getId() const{
    return studentId;
}

int Student::getEnrolledCoursesNumber() const{
    return numEnrolledCourses;
}

void Student::Display() const {
    cout << "Student ID: " << studentId << endl
         << "Name: " << name << endl;
    cout << "Number of enrolled courses: " << numEnrolledCourses << endl;
    if (numEnrolledCourses > 0) {
        cout << "Enrolled Courses:" << endl;
        for (int i = 0; i < numEnrolledCourses; i++) {
            if (enrolledCourses[i] != nullptr) { 
                cout << "  - ";
                enrolledCourses[i]->display();
            }
        }
    } else {
        cout << "No courses enrolled." << endl;
    }
}


void Student::enrollCourse(int courseId) { 
    if (numEnrolledCourses >= MAX_COURSES_PER_STUDENT) {
        cout << "Cannot enroll in more courses. Maximum limit reached." << endl;
        return;
    }


    for(int i=0; i < numEnrolledCourses; ++i) {
        if (enrolledCourses[i] != nullptr && enrolledCourses[i]->getCourseId() == to_string(courseId)) {
            cout << "Student " << this->studentId << " is already enrolled in course " << courseId << "." << endl;
            return;
        }
    }

    Course* newCourse = nullptr;
    switch (courseId) {
        case 1: newCourse = new Course("1", "AE2", 3); break;
        case 2: newCourse = new Course("2", "TWD", 2); break;
        case 3: newCourse = new Course("3", "PH2", 3); break;
        case 4: newCourse = new Course("4", "PE2", 2); break;
        case 5: newCourse = new Course("5", "OOP2", 3); break;
        case 6: newCourse = new Course("6", "CED", 3); break;
        case 7: newCourse = new Course("7", "C2", 3); break;
        default:
            cout << "Error: Invalid course ID " << courseId << " for enrollment." << endl;
            return;
    }

    if (newCourse) {
        enrolledCourses[numEnrolledCourses++] = newCourse;
        cout << "Student " << this->studentId << " successfully enrolled in course " << newCourse->getCourseName() << " (ID: " << newCourse->getCourseId() << ")." << endl;
    }
}

bool removeCourseFromArray(Course* courses[], int& numCourses, const string& courseIdToDrop) {
    int foundIndex = -1;
    for (int i = 0; i < numCourses; ++i) {
        if (courses[i] != nullptr && courses[i]->getCourseId() == courseIdToDrop) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        delete courses[foundIndex];
        for (int i = foundIndex; i < numCourses - 1; ++i) {
            courses[i] = courses[i + 1];
        }
        courses[numCourses - 1] = nullptr;
        numCourses--;
        return true;
    }
    return false;
}


void Student::dropCourse(const int &courseId) {
    string courseIdStrToDrop = to_string(courseId);

    if (removeCourseFromArray(enrolledCourses, numEnrolledCourses, courseIdStrToDrop)) {
        cout << "Student " << this->studentId << " successfully dropped from course ID " << courseIdStrToDrop << "." << endl;
    } else {
        cout << "Error: Student " << this->studentId << " is not enrolled in course ID " << courseIdStrToDrop << ", or course ID is invalid." << endl;
    }
}


string Student::ForOut() const {
    stringstream ss;
    ss << studentId << "," << name << "," << password; // CSV format

    if (numEnrolledCourses > 0) {
        ss << ","; //To add a comma before the first course ID
        for (int i = 0; i < numEnrolledCourses; i++) {
            if (enrolledCourses[i] != nullptr) {
                ss << enrolledCourses[i]->getCourseId(); // Only store Course ID
                if (i < numEnrolledCourses - 1) {
                    ss << ";"; // Semicolon separated list of course IDs
                }
            }
        }
    }
    return ss.str();
}

void Student::setNextId(int id) {
    if (id > 0) { // Basic validation
        nextStudentId = id;
    }
}

// Static method to get the next student ID.
int Student::getNextId() {
    return nextStudentId;
}

bool Student::IsEnrolledInCourse(const string &courseId) const { // Renamed parameter
    for (int i = 0; i < numEnrolledCourses; i++) {
        if (enrolledCourses[i] != nullptr && enrolledCourses[i]->getCourseId() == courseId) {
            return true;
        }
    }
    return false;
}
