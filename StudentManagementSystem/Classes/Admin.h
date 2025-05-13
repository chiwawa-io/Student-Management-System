//
// Created by u2410067 Djafarov Akbar on 5/7/2025.
//

#ifndef ADMIN_H
#define ADMIN_H

#include <string>

using namespace std;

// Forward declaration
class MainManagement;

class Admin {
private:
    string username;
    string password;

public:
    // Constructor
    Admin(string user = "admin", string pass = "admin");//default


    string getUsername() const; //getters
    bool checkPassword(const string& inputPassword) const;

    void viewDashboard(const MainManagement& system) const;

    void addNewStudent(MainManagement& system);
    void editStudentData(MainManagement& system);
    void removeStudent(MainManagement& system);
    void viewAllStudents(MainManagement& system);
    void viewStudentDetails(MainManagement& system) const;

    void enrollStudentInCourse(MainManagement& system);
    void dropStudentFromCourse(MainManagement& system);
     
};

#endif // ADMIN_H
