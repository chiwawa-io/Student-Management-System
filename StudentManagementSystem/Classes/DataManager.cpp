// ==================================================
// Created by Behzod berdikulov u2410054 on 5/11/2025.
//====================================================

#include "DataManager.h"
#include "MainManagement.h"
#include "CustomExceptions.h"
#include "Constants.h"
#include "Student.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cctype>

using namespace std;

DataManager::DataManager(const string &stuFile) : studentFilePath(stuFile) {}

int DataManager::splitCsvLine(const string &line, string fields[], int maxFields) const {
    int fieldCount = 0;
    stringstream ss(line);
    string segment;
    while (fieldCount < maxFields && getline(ss, segment, ',')) {
        size_t first = segment.find_first_not_of(" \t\n\r\f\v"); //trying to find at least something that is not just blank
        if (string::npos == first) { //using npos to find out segment is empty or not
            segment = "";
        } else {// removng extra spaces from the start and end
            size_t last = segment.find_last_not_of(" \t\n\r\f\v");
            segment = segment.substr(first, (last - first + 1));//Keeping only the characters between first and last, inclusively.
        }
        fields[fieldCount++] = segment;
    }
    if (fieldCount >= maxFields && ss.peek() != EOF && !ss.eof()) {
        string extraSegment;
        if (getline(ss, extraSegment, ',')) {
             cerr << "Warning: Exceeded max fields (" << maxFields << ") in line: " << line << endl;
        }
    }
    return fieldCount;
}

int DataManager::splitSemicolonSeparated(const string &text, string items[], int maxItems) const {
    int itemCount = 0;
    stringstream ss(text);
    string item;
    while (itemCount < maxItems && getline(ss, item, ';')) {
        if (!item.empty()) {
            size_t first = item.find_first_not_of(" \t\n\r\f\v"); ///does same thing as previous function
            if (string::npos != first) {
                size_t last = item.find_last_not_of(" \t\n\r\f\v");
                items[itemCount++] = item.substr(first, (last - first + 1));
            }
        }
    }
    if (itemCount >= maxItems && ss.peek() != EOF && !ss.eof()) {
        string extraItem;
        if(getline(ss, extraItem, ';')){
             cerr << "Warning: Exceeded max items (" << maxItems << ") in text: " << text << endl;
        }
    }
    return itemCount;
}

bool DataManager::parseStudentLine(const string &line, int lineNumber, StudentData &outData) const {
    string fields[MAX_STUDENT_FIELDS];
    int numFields = splitCsvLine(line, fields, MAX_STUDENT_FIELDS);

    if (numFields < 3) {
         cerr << "Warning: Student line " << lineNumber << ": Expected 3 fields, found " << numFields << ". Skipping. Line: [" << line << "]" << endl;
         return false;
    }

    outData.numEnrolledCourses = 0;
    outData.id = fields[0];
    outData.name = fields[1];
    outData.password = fields[2];

    if (outData.id.empty()) {
        cerr << "Student line " << lineNumber << ": ID empty. Skipping. Line: [" << line << "]" << endl;
        return false;
    }
    try {
        int studentIdInt = stoi(outData.id);
        if (studentIdInt <= 0) {
            cerr << "Student line " << lineNumber << ": Invalid ID '" << fields[0] << "'. Must be positive. Skipping. Line: [" << line << "]" << endl;
            return false;
        }
    } catch (const std::invalid_argument& e) {
        cerr << "Student line " << lineNumber << ": Invalid ID format '" << fields[0] << "'. Must be number. Skipping. Error: " << e.what() << ". Line: [" << line << "]" << endl;
        return false;
    } catch (const std::out_of_range& e) {
         cerr << "Student line " << lineNumber << ": ID '" << fields[0] << "' numerically out of range for int. Skipping. Error: " << e.what() << ". Line: [" << line << "]" << endl;
         return false;
    }

    return true;
}

void DataManager::loadStudents(MainManagement &system) {
    ifstream studentFile(studentFilePath);
     if (!studentFile.is_open()) {
        cerr << "Warning: Student data file '" << studentFilePath << "' not found. Starting empty." << endl;
        Student::setNextId(1);
        return;
    }

    string line;
    int lineNumber = 0;
    StudentData loadedStudentData[MAX_STUDENTS];
    int parsedStudentCount = 0;

    while (parsedStudentCount < MAX_STUDENTS && getline(studentFile, line)) {
         lineNumber++;
        if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == string::npos) {
            continue;
        }
        StudentData currentData;
        if (parseStudentLine(line, lineNumber, currentData)) {
            loadedStudentData[parsedStudentCount++] = currentData;
        }
    }

     if (parsedStudentCount >= MAX_STUDENTS && !studentFile.eof()) {
        string tempLine;
        if(getline(studentFile, tempLine) && !tempLine.empty()){
            cerr << "Warning: Reached student storage limit (" << MAX_STUDENTS << "). Some students may not have been loaded." << endl;
        }
     }
    studentFile.close();

    int studentsSuccessfullyAddedToSystem = 0;
    int maxLoadedId = 0;

    for (int i = 0; i < parsedStudentCount; ++i) {
        StudentData& data = loadedStudentData[i];
        try {
            Student student(data.name, data.password, data.id);
            system.addStudent(student);
            studentsSuccessfullyAddedToSystem++;

            Student* studentPtr = system.findStudentById(data.id);
            if (!studentPtr) {
                cerr << "Critical Error: Could not find student " << data.id << " after adding." << endl;
                continue;
            }

            for (int j = 0; j < data.numEnrolledCourses; ++j) {
                try {
                    if (data.enrolledCourseIds[j].empty()) continue;
                    studentPtr->enrollCourse(stoi(data.enrolledCourseIds[j]));
                } catch (const std::exception& e) {
                    cerr << "Warning: Invalid course ID '" << data.enrolledCourseIds[j] << "' for student " << data.id << ". Skipping. Error: " << e.what() << endl;
                }
            }
            int currentIdInt = stoi(data.id);
            if (currentIdInt > maxLoadedId) {
                maxLoadedId = currentIdInt;
            }
        } catch (const std::exception& e) {
             cerr << "Warning: Error adding student (ID: " << data.id << ") to system: " << e.what() << endl;
        }
    }

    if (studentsSuccessfullyAddedToSystem > 0) {
        Student::setNextId(maxLoadedId + 1);
    } else if (lineNumber == 0 && parsedStudentCount == 0) {
        Student::setNextId(1);
    }
     cout << "Loaded " << studentsSuccessfullyAddedToSystem << " students from file." << endl;
}

void DataManager::saveStudents(const MainManagement &system) {
    std::ofstream studentFile(studentFilePath);
    if (!studentFile.is_open()) {
        cerr << "Error: Could not open student data file '" << studentFilePath << "' for writing. Data NOT saved." << endl;
        throw FileWriteException(studentFilePath + " (could not open for writing)");
    }

    int studentsSaved = 0;
    for (int i = 0; i < system.getNumStudents(); ++i) {
        const Student * student = system.getStudentByIndex(i);
        if (student) {
            studentFile << student->ForOut() << std::endl;
            if (!studentFile.good()) {
                studentFile.close();
                cerr << "Error: Failed to write student data for ID " << student->getId() << ". Data may be incomplete." << endl;
                throw FileWriteException(studentFilePath + " (error during write operation)");
            }
            studentsSaved++;
        }
    }
    studentFile.close();
    if (!studentFile.good() && studentsSaved > 0 && studentsSaved < system.getNumStudents()) {
         cerr << "Error: An error occurred after closing student file '" << studentFilePath << "'. Data may not be fully saved." << endl;
    } else if (studentsSaved == 0 && system.getNumStudents() > 0) {
         cerr << "Error: Failed to save any student data to '" << studentFilePath << "'." << endl;
    }
    else {
        std::cout << "Saved " << studentsSaved << " students to '" << studentFilePath << "'." << std::endl;
    }
}
