#include "StudentManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

StudentManager::StudentManager(const std::string& dbFilename)
    : filename(dbFilename), currentSortOption(SORT_BY_NAME) {
    loadFromFile();
}

void StudentManager::loadFromFile() {
    students.clear();
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        // If the file does not exist, create an empty file.
        std::ofstream ofs(filename);
        ofs.close();
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Student s;
        // Load tab-delimited data
        if (std::getline(ss, s.name, '\t') &&
            std::getline(ss, s.studentId, '\t') &&
            std::getline(ss, s.birthYear, '\t') &&
            std::getline(ss, s.department, '\t') &&
            std::getline(ss, s.tel, '\t')) {
            students.push_back(s);
        }
    }
    ifs.close();
}

void StudentManager::saveToFile() {
    std::ofstream ofs(filename, std::ios::trunc);
    for (const auto& s : students) {
        ofs << s.name << '\t'
            << s.studentId << '\t'
            << s.birthYear << '\t'
            << s.department << '\t'
            << s.tel << '\n';
    }
    ofs.close();
}

bool StudentManager::insertStudent(const Student& student) {
    // Duplicate Check
    for (const auto& existing : students) {
        if (existing.studentId == student.studentId) {
            return false;
        }
    }
    students.push_back(student);
    saveToFile();
    return true;
}

void StudentManager::setSortOption(SortOption option) {
    currentSortOption = option;
}

SortOption StudentManager::getSortOption() const {
    return currentSortOption;
}

std::vector<Student> StudentManager::searchByName(const std::string& keyword) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (s.name.find(keyword) != std::string::npos) {
            result.push_back(s);
        }
    }
    return result;
}

std::vector<Student> StudentManager::searchByStudentId(const std::string& keyword) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (s.studentId == keyword) {
            result.push_back(s);
        }
    }
    return result;
}

std::vector<Student> StudentManager::searchByAdmissionYear(const std::string& keyword) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (s.studentId.length() >= 4 && s.studentId.substr(0, 4) == keyword) {
            result.push_back(s);
        }
    }
    return result;
}

std::vector<Student> StudentManager::searchByBirthYear(const std::string& keyword) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (s.birthYear == keyword) {
            result.push_back(s);
        }
    }
    return result;
}

std::vector<Student> StudentManager::searchByDepartment(const std::string& keyword) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (s.department.find(keyword) != std::string::npos) {
            result.push_back(s);
        }
    }
    return result;
}

std::vector<Student> StudentManager::getAllStudents() const {
    return students;
}

void StudentManager::printStudentList(std::vector<Student> list) const {
    if (list.empty()) return;

    // Sorting Process
    std::sort(list.begin(), list.end(), [this](const Student& a, const Student& b) {
        switch (currentSortOption) {
            case SORT_BY_NAME:
                return a.name < b.name;
            case SORT_BY_STUDENT_ID:
                return a.studentId < b.studentId;
            case SORT_BY_BIRTH_YEAR:
                return a.birthYear < b.birthYear;
            case SORT_BY_DEPARTMENT:
                return a.department < b.department;
            default:
                return a.name < b.name;
        }
    });

    // Output formatted to match the specifications document layout
    std::cout << std::left 
              << std::setw(16) << "Name"
              << std::setw(12) << "StudentID"
              << std::setw(25) << "Dept"
              << std::setw(12) << "Birth Year"
              << "Tel" << "\n";

    for (const auto& s : list) {
        std::cout << std::left 
                  << std::setw(16) << s.name
                  << std::setw(12) << s.studentId
                  << std::setw(25) << s.department
                  << std::setw(12) << s.birthYear
                  << s.tel << "\n";
    }
}