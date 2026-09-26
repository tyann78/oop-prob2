#include "StudentManager.h"
#include <iostream>
#include <string>

void handleInsertionUI(StudentManager& manager) {
    Student s;

    std::cout << "Name ? ";
    std::getline(std::cin, s.name);

    std::cout << "Student ID (10 digits)? ";
    std::getline(std::cin, s.studentId);

    std::cout << "Birth Year (4 digits) ? ";
    std::getline(std::cin, s.birthYear);

    std::cout << "Department ? ";
    std::getline(std::cin, s.department);

    std::cout << "Tel ? ";
    std::getline(std::cin, s.tel);

    if (s.name.empty() || s.studentId.empty()) {
        std::cout << "Error : Name and Student ID cannot be blank.\n";
        return;
    }

    if (!manager.insertStudent(s)) {
        std::cout << "Error : Already inserted\n";
    }
}

void handleSearchUI(StudentManager& manager) {
    std::cout << "- Search -\n";
    std::cout << "1. Search by name\n";
    std::cout << "2. Search by student ID (10 digits)\n";
    std::cout << "3. Search by admission year (4 digits)\n";
    std::cout << "4. Search by birth year (4 digits)\n";
    std::cout << "5. Search by department name\n";
    std::cout << "6. List All\n";
    std::cout << "> ";

    std::string choiceStr;
    std::getline(std::cin, choiceStr);
    if (choiceStr.empty()) return;

    int choice = 0;
    try {
        choice = std::stoi(choiceStr);
    } catch (...) {
        return;
    }

    std::vector<Student> result;
    std::string keyword;

    switch (choice) {
        case 1:
            std::cout << "Name keyword? ";
            std::getline(std::cin, keyword);
            result = manager.searchByName(keyword);
            break;
        case 2:
            std::cout << "Student ID keyword? ";
            std::getline(std::cin, keyword);
            result = manager.searchByStudentId(keyword);
            break;
        case 3:
            std::cout << "Admission year keyword? ";
            std::getline(std::cin, keyword);
            result = manager.searchByAdmissionYear(keyword);
            break;
        case 4:
            std::cout << "Birth year keyword? ";
            std::getline(std::cin, keyword);
            result = manager.searchByBirthYear(keyword);
            break;
        case 5:
            std::cout << "Department name keyword? ";
            std::getline(std::cin, keyword);
            result = manager.searchByDepartment(keyword);
            break;
        case 6:
            result = manager.getAllStudents();
            break;
        default:
            return;
    }

    manager.printStudentList(result);
}

void handleSortingOptionUI(StudentManager& manager) {
    std::cout << "- Sorting Option\n";
    std::cout << "1. Sort by Name\n";
    std::cout << "2. Sort by Student ID\n";
    std::cout << "3. Sort by Birth Year\n";
    std::cout << "4. Sort by Department name\n";
    std::cout << "> ";

    std::string choiceStr;
    std::getline(std::cin, choiceStr);
    if (choiceStr.empty()) return;

    try {
        int choice = std::stoi(choiceStr);
        if (choice >= 1 && choice <= 4) {
            manager.setSortOption(static_cast<SortOption>(choice));
        }
    } catch (...) {}
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::string filename = argv[1];
    StudentManager manager(filename);

    while (true) {
        std::cout << "1. Insertion\n";
        std::cout << "2. Search\n";
        std::cout << "3. Sorting Option\n";
        std::cout << "4. Exit\n";
        std::cout << "> ";

        std::string input;
        if (!std::getline(std::cin, input)) break;
        if (input.empty()) continue;

        int choice = 0;
        try {
            choice = std::stoi(input);
        } catch (...) {
            continue;
        }

        if (choice == 1) {
            handleInsertionUI(manager);
        } else if (choice == 2) {
            handleSearchUI(manager);
        } else if (choice == 3) {
            handleSortingOptionUI(manager);
        } else if (choice == 4) {
            break;
        }
    }

    return 0;
}