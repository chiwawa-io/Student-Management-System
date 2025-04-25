//
// Created by Behzod Beridkulov u2410054 on 23.04.2025.
//
// Edited By Djafarov Akbar u2410067 on 24.04.2025

#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Course.h"
#include <iostream>
using namespace std;

class Student : public Person{
public:
    Student(string n) : Person(n), enrolledCourses(nullptr), courseCount(0), courseCapacity(5) {
        studentID = nextStudentID - 1;
        enrolledCourses = new Course*[courseCapacity];
    };
    ~Student() {
        delete[] enrolledCourses;
    };

private:
    int studentID;
    Course** enrolledCourses;
    int courseCount;
    int courseCapacity;

    static int nextStudentID = 1;

    void resizeCourseArray() {
        if (courseCapacity == 0) int newCapacity = 5;
        else int newCapacity = courseCapacity *= 2;
        
        Course** newArray = new Course*[newCapacity];

        for (int i = 0; i < courseCount; ++i) {
            newArray[i] = enrolledCourses[i];
        }

        delete[] enrolledCourses;

        enrolledCourses = newArray;
        courseCapacity = newCapacity;
    };
};



#endif //STUDENT_H
