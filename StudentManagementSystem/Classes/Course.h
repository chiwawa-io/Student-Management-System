//
// Created by U2410067 Djafarov Akbar
//

#ifndef COURSE_H
#define COURSE_H

#include <string>

using namespace std;

class Course {
public:
    // for arrays
    Course();
    // Parameterized constructor
    Course(string id, string name, int cred);

    // Getters
    string getCourseId() const;
    string getCourseName() const;
    int getCourseCredit() const;

    // Setters (use with caution, maybe only via Admin/System)
    void setCourseName(const string& name);
    void setCourseId(const string& id); // Needed for loading
    void setCourseCredit(int courseCredits);

    // Display
    void display() const;

    // for DataManger
    string ForOut() const;

private:
    string courseId;
    string courseName;
    int courseCredits;
};



#endif //COURSE_H
