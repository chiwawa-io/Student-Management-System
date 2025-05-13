//
// Created by Yeahmonny on 5/7/2025.
//

#include "Admin.h"

#include <iostream>
#include <ostream>
#include <string>

#include "CustomExceptions.h"
#include "MainManagement.h"
#include "Utilities.h"

using namespace std;

Admin::Admin(string user, string pass) : username(user), password(pass) {
}

string Admin::getUsername() const {
    return username;
}

bool Admin::checkPassword(const string &inputPassword) const {
    return password == inputPassword;
}

void Admin::viewDashboard(const MainManagement &system) const {
    cout << "\n--- Admin Dashboard ---\n";
    cout << "Total Students: " << system.getNumStudents() << " / " << MAX_STUDENTS << endl;
    cout << "Total Courses:  " << system.getNumCourses() << " / " << MAX_COURSES_OFFERED << endl;
    cout << "Next Student ID:" << Student::getNextId() << endl; 
    cout << "-----------------------" << endl;
}

void Admin::addNewStudent(MainManagement &system) {
    cout << "\n--- Add New Student ---\n";
    string name = Utilities::getString("Enter student name: ");
    string pass = Utilities::getString("Enter temporary password: "); // Consider generating one

    try {
        Student& newStudent = system.addStudent(name, pass);
        cout << "Student '" << name << "' added successfully with ID: " << newStudent.getId() << endl;
    } catch (const ArrayFullException& e) {
        cerr << "Error adding student: " << e.what() << endl;
    } catch (const CustomException& e) {
        cerr << "An unexpected error occurred: " << e.what() << endl;
    }
}

void Admin::editStudentData(MainManagement &system) {
    cout << "\n--- Edit Student Data ---\n";
    string studentId = Utilities::getString("Enter ID of student to edit: ");

    try {
        Student* student = system.findStudentById(studentId); 

        cout << "Editing student: " << student->getName() << " (ID: " << studentId << ")" << endl;
        string newName = Utilities::getString("Enter new name (leave blank to keep current): ");

        if (!newName.empty()) {
            system.updateStudentName(studentId, newName); 
            cout << "Student name updated successfully.\n";
        } else
            cout << "Name not changed.\n";
    } catch (const StudentNotFoundException& e) {
        cerr << e.what() << endl;
    } catch (const CustomException& e) {
        cerr << "An error occurred during editing: " << e.what() << endl;
    }
}

void Admin::removeStudent(MainManagement &system) {
    cout << "\n--- Remove Student ---\n";
    string studentId = Utilities::getString("Enter ID of student to remove: ");

    try {
        // Optional: Display student name for confirmation
        Student* student = system.findStudentById(studentId); // Verify existence first
        cout << "Found student: " << student->getName() << " (ID: " << studentId << ")" << endl;
        string confirm = Utilities::getString("Are you sure you want to remove this student? (y/n): ");

        if (confirm == "y" || confirm == "Y" || confirm == "y " || confirm == " y") {
            system.deleteStudent(studentId);
            cout << "Student removed successfully.\n";
        } else {
            cout << "Removal cancelled.\n";
        }
    } catch (const StudentNotFoundException& e) {
        cerr << e.what() << endl;
    } catch (const CustomException& e) {
        cerr << "An error occurred during removal: " << e.what() << endl;
    }
}

void Admin::viewAllStudents(MainManagement& system) {
    std::cout << "\n--- All Students (" << system.getNumStudents() << ") ---\n";
    if (system.getNumStudents() == 0) {
        std::cout << "No students in the system.\n";
    } else {
        for (int i = 0; i < system.getNumStudents(); ++i) {
            const Student* student = system.getStudentByIndex(i);
            if (student) std::cout << "ID: " << student->getId() << ", Name: " << student->getName() << std::endl;
        }
    }
    std::cout << "------------------------\n";
}

void Admin::viewStudentDetails(MainManagement& system) const {
     std::cout << "\n--- View Student Details ---\n";
     string studentId = Utilities::getString("Enter ID of student to view: ");
     try {
         const Student* student = system.findStudentById(studentId); // Const access is enough
         student->Display();
     } catch (const StudentNotFoundException& e) {
         std::cerr << e.what() << std::endl;
     } catch (const CustomException& e) {
         std::cerr << "An error occurred: " << e.what() << std::endl;
     }
}


void Admin::enrollStudentInCourse(MainManagement& system) {
    std::cout << "\n--- Enroll Student in Course ---\n";
    string studentId = Utilities::getString("Enter student ID: ");
    std::string courseId = Utilities::getString("Enter course ID to enroll in: ");

    try {
        system.assignCourseToStudent(studentId, stoi(courseId));
        std::cout << "Student " << studentId << " enrolled in course " << courseId << " successfully.\n";
    } catch (const StudentNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const CourseNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const ArrayFullException& e) { // Student's course list is full
        std::cerr << "Enrollment failed: " << e.what() << std::endl;
    } catch (const OperationFailedException& e) { // e.g., already enrolled
         std::cerr << "Enrollment failed: " << e.what() << std::endl;
    } catch (const CustomException& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }
}

void Admin::dropStudentFromCourse(MainManagement& system) {
    std::cout << "\n--- Drop Student from Course ---\n";
    string studentId = Utilities::getString("Enter student ID: ");
    std::string courseId = Utilities::getString("Enter course ID to drop: ");

    try {
        system.removeCourseFromStudent(studentId, stoi(courseId));
        std::cout << "Student " << studentId << " dropped from course " << courseId << " successfully.\n";
    } catch (const StudentNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const CourseNotFoundException& e) { // Should be caught by student->dropCourse logic ideally
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const OperationFailedException& e) { // e.g., not enrolled
         std::cerr << "Drop failed: " << e.what() << std::endl;
    } catch (const CustomException& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }
}