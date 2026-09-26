#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// Enumeration Types for Sorting Criteria
enum SortOption {
    SORT_BY_NAME = 1,
    SORT_BY_STUDENT_ID = 2,
    SORT_BY_BIRTH_YEAR = 3,
    SORT_BY_DEPARTMENT = 4
};

// Student Information Entity
struct Student {
    std::string name;
    std::string studentId;   // 10 digits (the first 4 digits represent the year of enrollment)
    std::string birthYear;   // 4 digits
    std::string department;  // May contain spaces
    std::string tel;         // Up to 12 digits
};

#endif // STUDENT_H