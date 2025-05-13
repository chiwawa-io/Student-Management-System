//
// Created by Yeahmonny on 5/6/2025.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Constants.h"

using namespace std;

class Course;
class MainManagement;
class DataManager;

class Student {
public:
    Student();
    Student(string name, string password);
    Student(string name, string password, string id);

    void changePassword(string password);

    string getName() const;
    string getPassword() const;
    string getId() const;
    int getEnrolledCoursesNumber() const;

    void setName (string name) {this->name = name;}

    void Display() const;

    void enrollCourse(int courseId);
    void dropCourse(const int &courseId);

    string ForOut () const;

    static void setNextId(int id);
    static int getNextId();

private:
    string studentId;
    string name;
    string password;
    Course* enrolledCourses[MAX_COURSES_PER_STUDENT]; //course array
    int numEnrolledCourses;

    static int nextStudentId;

    bool IsEnrolledInCourse(const string &courseId) const;


    friend class MainManagement;
    friend class DataManager;
};



#endif //STUDENT_H
