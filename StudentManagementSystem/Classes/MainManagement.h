//
// Created by Behzod Berdikulov u2410054
//

#ifndef MAINMANAGEMENT_H
#define MAINMANAGEMENT_H

#include "Student.h"
#include "Constants.h"
#include "Admin.h"
#include "Course.h"
#include "DataManager.h"
#include <iostream>
#include <string>

using namespace std;

class MainManagement {
private:
    Student studentsList[MAX_STUDENTS];
    int numberOfStudents;

    Course courseAll[MAX_COURSES_OFFERED];
    int numberOfCourses = 7;

    Admin admin;
    DataManager data_manager;

    Student* findStudentByIdPrivate(string studentId);
    Course* findCourseByIdPrivate(const string& courseId); // for inside class search

    void performAdminLogin(); //ui menu functions
    void performStudentLogin();
    void showMainMenu();
    void showAdminMenu(Admin* admin);
    void showStudentMenu(Student* student);

    void addStudent(Student& student);


public:
    MainManagement();
    ~MainManagement();

    void runLoop();

    int getNumStudents() const;
    int getNumCourses() const;

    Student* findStudentById(string studentId);
    Course* findCourseById(const string& courseId); // for inside class search

    Student& addStudent(const string& name, const string& password); 
    void deleteStudent(string studentId);
    void updateStudentName(string studentId, const string& newName);

    void assignCourseToStudent(string studentId, const int& courseId);
    void removeCourseFromStudent(string studentId, const int& courseId);

    const Student* getStudentByIndex(int index) const;
    Student* getStudentByIndexNotConst(int index);

    friend class DataManager;
};



#endif //MAINMANAGEMENT_H
