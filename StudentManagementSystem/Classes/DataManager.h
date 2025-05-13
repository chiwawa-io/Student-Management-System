//
// Created by U2410067 Djafarov Akbar  on 5/11/2025.
//

#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <string>
#include "Constants.h"
using namespace std;

class MainManagement;
class Course;
class Student;

struct StudentData {
    string id = "0";
    string name;
    string password;
    string enrolledCourseIds[MAX_COURSES_PER_STUDENT];
    int numEnrolledCourses = 0;
};

class DataManager {
private:
    string studentFilePath;

    int splitCsvLine(const string& line, string fields[], int maxFields) const;
    int splitSemicolonSeparated(const std::string& text, std::string items[], int maxItems) const;

    bool parseStudentLine(const string& line, int lineNumber, StudentData& outData) const;

public:
    DataManager(const string& stuFile);

    void loadStudents(MainManagement& system);

    void saveStudents(const MainManagement& system);

};



#endif //DATAMANAGER_H
