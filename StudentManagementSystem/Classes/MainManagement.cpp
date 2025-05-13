//
// Created by Behzod Berdikulov u2410054
//

#include "MainManagement.h"
#include "DataManager.h"
#include "CustomExceptions.h"
#include "Student.h"
#include "Course.h"
#include "Constants.h"
#include "Utilities.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace Utilities;

MainManagement::MainManagement() : numberOfStudents(0), numberOfCourses(0), admin("admin", "admin"), data_manager(STUDENTS_FILE) {
    cout << "----Initializing Student Management System----" << endl;
    try {
        cout << "Loading files..." << endl;
        data_manager.loadStudents(*this);
        cout << "Done!" << endl;
    } catch (const CustomException &e) {
        cerr << "No data found in: " << e.what() << endl;
        cerr << "Initializing with empty student database" << endl;
        numberOfStudents = 0;
        numberOfCourses = 0;
        Student::setNextId(1);
    } catch (const exception &e) {
        cerr << "critical error: " << e.what() << endl;
    } catch (...) {
        cerr << "unknown error!" << endl;
    }
    cout << "Loading done!" << endl;
}

MainManagement::~MainManagement() {
    cout << "Starting closing application..." << endl;
    try {
        cout << "Saving files..." << endl;
        data_manager.saveStudents(*this);
        cout << "Successful!" << endl;
    } catch (const CustomException &e) {
        cerr << "Failed to save to: " << e.what() << endl;
    } catch (const exception &e) {
        cerr << "critical error!" << e.what() << endl;
    } catch (...) {
        cerr << "unknown error!" << endl;
    }
    cout << "Closing complete!" << endl;
}

Student * MainManagement::findStudentById(string studentId) {
    Student * student = findStudentByIdPrivate(studentId);
    if (!student) {
        throw StudentNotFoundException(studentId);
    }
    return student;
}

Course * MainManagement::findCourseById(const string &courseId) {
    Course * course = findCourseByIdPrivate(courseId);
    if (!course) {
        throw CourseNotFoundException(courseId);
    }
    return course;

}

Student * MainManagement::findStudentByIdPrivate(string studentId) {
    for (int i = 0; i < numberOfStudents; ++i) {
        if (studentsList[i].getId() == studentId) {
            return &studentsList[i];
        }
    }
    return nullptr;
}

Course * MainManagement::findCourseByIdPrivate(const string &courseId) {
    for (int i = 0; i < numberOfCourses; ++i) {
        if (courseAll[i].getCourseId() == courseId) {
            return &courseAll[i];
        }
    }
    return nullptr;
}

void MainManagement::performAdminLogin() {
    cout << "Performing admin login..." << endl;
    string username = getString("Username: ");
    string password = getString("Password: ");

    if (admin.getUsername() == username && admin.checkPassword(password)) {
        cout << "Login successful! Admnin panel is accesibble now" << endl;
        showAdminMenu(&admin);
    } else cerr << "Login failed!" << endl;
}

void MainManagement::performStudentLogin() {
    cout << "Performing student login..." << endl;
    string username = getString("ID: ");
    string password = getString("Password: ");
    try {
        Student* student = findStudentById(username); // Throws if not found
        if (student->getPassword() == password) {
            cout << "Login successful. Welcome, " << student->getName() << "!\n";
            showStudentMenu(student);
        } else {
            cerr << "Incorrect password.\n";
        }
    } catch (const StudentNotFoundException& e) {
        cerr << e.what() << endl;
    } catch (const CustomException& e) {
        cerr << "An unexpected error occurred during login: " << e.what() << endl;
    }
}

void MainManagement::showMainMenu() {
    cout << "\n------- Main Menu ------\n";
    cout << "1. Admin Login\n";
    cout << "2. Student Login\n";
    cout << "0. Exit\n";
    cout << "------------------------\n";
}

void MainManagement::showAdminMenu(Admin *admin) {
    int choice;
    do {
        cout << "\n===== Admin Menu (" << admin->getUsername() << ") =====\n";
        cout << "1. View Dashboard\n";
        cout << "2. Add New Student\n";
        cout << "3. Edit Student Data\n";
        cout << "4. Remove Student\n";
        cout << "5. View All Students\n";
        cout << "6. View Student Details\n";
        cout << "7. Enroll Student in Course\n";
        cout << "8. Drop Student from Course\n";
        cout << "0. Logout\n";
        cout << "=============================\n";

        choice = getInt("Enter your choice: ");

        try {
            switch (choice) {
                case 1: admin->viewDashboard(*this); break;
                case 2: admin->addNewStudent(*this); break;
                case 3: admin->editStudentData(*this); break;
                case 4: admin->removeStudent(*this); break;
                case 5: admin->viewAllStudents(*this); break;
                case 6: admin->viewStudentDetails(*this); break;
                case 7: admin->enrollStudentInCourse(*this); break;
                case 8: admin->dropStudentFromCourse(*this); break;
                case 0: cout << "Logging out admin...\n"; break;
                default: cerr << "Invalid choice. Please try again.\n";
            }
        } catch (const CustomException &e) {
            // Catch any exceptions potentially missed in Admin methods (shouldn't happen ideally)
            cerr << "An unexpected system error occurred in admin menu: " << e.what() << endl;
        } catch (const exception &e) {
             cerr << "An unexpected standard error occurred in admin menu: " << e.what() << endl;
        }

    } while (choice != 0);
}

void MainManagement::showStudentMenu(Student *student) {
    int choice;
    do {
        cout << "\n------- Student Menu (ID: " << student->getId() << ", Name: " << student->getName() << ") --------\n";
        cout << "1. View My Profile\n";
        cout << "2. Change My Password\n";
        cout << "0. Logout\n";
        cout << "---------------------------------\n";

        choice = getInt("Enter your choice: ");

        try {
            switch (choice) {
                case 1:
                    student->Display(); // Don't show password by default
                    break;
                case 2: {
                    string newPass = getString("Enter new password: ");
                    string confirmPass = getString("Confirm new password: ");
                    if (newPass == confirmPass) {
                        student->changePassword(newPass); // Handles update and message
                    } else {
                        cerr << "Passwords do not match. Password not changed.\n";
                    }
                    break;
                }
                case 0:
                    cout << "Logging out student...\n";
                    break;
                default:
                    cerr << "Invalid choice. Please try again.\n";
            }
        } catch (const CustomException &e) {
            cerr << "An error occurred: " << e.what() << endl;
        } catch (const exception &e) {
             cerr << "An unexpected system error occurred: " << e.what() << endl;
        }

    } while (choice != 0);
}

void MainManagement::addStudent(Student &student) {
    if (numberOfStudents >= MAX_STUDENTS) {
        throw ArrayFullException("student list");
    }
    // Check for duplicates before adding
    if (findStudentByIdPrivate(student.getId()) != nullptr) {
        throw AlradyExistException("Student", student.getId());
    }
    studentsList[numberOfStudents++] = student; // Copy student object into array
    // Ensure nextId is updated correctly based on loaded IDs
    if (stoi(student.getId()) >= Student::getNextId()) {
        Student::setNextId(stoi(student.getId()) + 1);
    }
}

const Student * MainManagement::getStudentByIndex(int index) const {
    if (index < 0 || index >= numberOfStudents) {
        throw out_of_range("Student index out of range");
    }
    return &studentsList[index];
}

Student * MainManagement::getStudentByIndexNotConst(int index) {
    if (index < 0 || index >= numberOfStudents) {
        throw out_of_range("Student index out of range");
    }
    return &studentsList[index];
}


void MainManagement::runLoop() {
    int choice;
    do {
        showMainMenu();
        choice = getInt("Enter your choice: ");

        switch (choice) {
            case 1:
                performAdminLogin();
            break;
            case 2:
                performStudentLogin();
            break;
            case 0:
                cout << "Exiting program...\n";
            break;
            default:
                cerr << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int MainManagement::getNumStudents() const {
    return numberOfStudents;
}

int MainManagement::getNumCourses() const {
    return numberOfCourses;
}

Student & MainManagement::addStudent(const string &name, const string &password) {
    if (numberOfStudents >= MAX_STUDENTS) {
        throw ArrayFullException("student list");
    }
    studentsList[numberOfStudents] = Student(name, password);
    return studentsList[numberOfStudents++];
}


void MainManagement::deleteStudent(string studentId) {
    int index = -1;
    for (int i = 0; i < numberOfStudents; ++i) {
        if (studentsList[i].getId() == studentId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw StudentNotFoundException(studentId);
    }

    // Shift remaining students down
    for (int i = index; i < numberOfStudents - 1; ++i) {
        studentsList[i] = studentsList[i + 1];
    }
    numberOfStudents--;
}

void MainManagement::updateStudentName(string studentId, const string &newName) {
    Student* student = findStudentById(studentId); // Throws if not found
    student->setName(newName);
}

void MainManagement::assignCourseToStudent(string studentId, const int &courseId) {
    Student* student = findStudentById(studentId);
    student->enrollCourse(courseId);
}


void MainManagement::removeCourseFromStudent(string studentId, const int &courseId) {
    Student* student = findStudentById(studentId);
    student ->dropCourse(courseId);
}
