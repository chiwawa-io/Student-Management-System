//
// Created by Yeahmonny on 5/6/2025.
//

#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class CustomException : public runtime_error {
    public:
    CustomException(string msg) : runtime_error(msg) {}; //base class for all errors
};

class FileNotFoundException : public CustomException {
    public:
    FileNotFoundException(string msg) : CustomException(msg) {};
};

class FileReadException : public CustomException {
    public:
    FileReadException(string msg) : CustomException(msg) {};
};
class FileWriteException : public CustomException {
    public:
    FileWriteException(string msg) : CustomException(msg) {};
};
class NotFoundException : public CustomException {
    public:
    NotFoundException(const string &item, const string &id) : CustomException(item + "with id: " + id + "not found here") {};
};

class StudentNotFoundException : public NotFoundException {
    public:
    StudentNotFoundException(string id) : NotFoundException("student", id) {};
};

class CourseNotFoundException : public NotFoundException {
    public:
    CourseNotFoundException(string CourseId) : NotFoundException("course", CourseId) {};
};

class ArrayFullException : public CustomException {
    public:
    ArrayFullException(string typeOfList) : CustomException("The "+ typeOfList + "is full. there is not enough space") {};
};
class AlradyExistException : public CustomException {
    public:
    AlradyExistException(const string &item, const string &id ) : CustomException(item + " with" + id + " already exists") {};
};
class NoCourseException : public CustomException {
    public:
    NoCourseException(const string &student) : CustomException(student  + " dont have course") {};
};
class InvalaidDataException : public CustomException {
    InvalaidDataException(const string &item) : CustomException("please enter valid data to: " + item) {};
};

class OperationFailedException : public CustomException {
    public:
    OperationFailedException(const string &details) : CustomException("operation failed: " + details) {};
};

#endif //CUSTOMEXCEPTIONS_H
