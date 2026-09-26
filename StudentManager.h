#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <string>
#include <vector>

class StudentManager {
private:
    std::string filename;
    std::vector<Student> students;
    SortOption currentSortOption;

    void loadFromFile();
    void saveToFile();

public:
    explicit StudentManager(const std::string& dbFilename);

    // Registration process (returns false if the student ID is duplicated)
    bool insertStudent(const Student& student);

    // Sort Settings
    void setSortOption(SortOption option);
    SortOption getSortOption() const;

    // Search Process
    std::vector<Student> searchByName(const std::string& keyword) const;
    std::vector<Student> searchByStudentId(const std::string& keyword) const;
    std::vector<Student> searchByAdmissionYear(const std::string& keyword) const;
    std::vector<Student> searchByBirthYear(const std::string& keyword) const;
    std::vector<Student> searchByDepartment(const std::string& keyword) const;
    std::vector<Student> getAllStudents() const;

    // Format and output in the current sort order
    void printStudentList(std::vector<Student> list) const;
};

#endif // STUDENT_MANAGER_H