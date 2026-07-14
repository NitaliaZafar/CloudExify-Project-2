// student_system.cpp
// CloudExify C++ Internship — Month 1, Project 2
// Student Record System

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // for setw(), setprecision()
using namespace std;

const int MAX = 50; // Maximum number of students we can store

// ---------------------------------------------------------
// The struct: groups all the data for ONE student together
// ---------------------------------------------------------
struct Student {
    int id;
    string name;
    int rollNumber;
    float math;
    float physics;
    float english;
    float average;   // calculated field
    char grade;      // calculated field (A/B/C/D/F)
};

// Global array of students and a counter for how many are stored
Student students[MAX];
int count = 0;

// ===========================================================
// Helper functions
// ===========================================================

// Calculate average marks for one student
float calcAverage(Student s) {
    return (s.math + s.physics + s.english) / 3.0f;
}

// Calculate letter grade based on average marks
char calcGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 75) return 'B';
    else if (avg >= 60) return 'C';
    else if (avg >= 50) return 'D';
    else return 'F';
}

// Ask the user for a mark and keep asking until it's valid (0-100)
float getValidMark(string subjectName) {
    float mark;
    cout << subjectName << " marks (0-100): ";
    cin >> mark;
    while (mark < 0 || mark > 100) {
        cout << "Must be 0-100: ";
        cin >> mark;
    }
    return mark;
}

// ===========================================================
// Step 2 — Add a new student
// ===========================================================
void addStudent() {
    if (count >= MAX) {
        cout << "Maximum students reached!" << endl;
        return;
    }

    Student s;
    s.id = count + 1;

    cout << "\n--- ADD STUDENT ---" << endl;

    cout << "Name: ";
    cin.ignore();          // clear leftover newline from previous input
    getline(cin, s.name);  // getline() allows spaces in the name

    cout << "Roll Number: ";
    cin >> s.rollNumber;

    // Get marks with validation (0-100 only)
    s.math    = getValidMark("Math");
    s.physics = getValidMark("Physics");
    s.english = getValidMark("English");

    s.average = calcAverage(s);
    s.grade   = calcGrade(s.average);

    students[count] = s;
    count++;

    cout << "Student added! Average: "
         << fixed << setprecision(1)
         << s.average << "  Grade: " << s.grade << endl;
}

// ===========================================================
// Step 3 — Display all students in a formatted table
// ===========================================================
void displayAll() {
    if (count == 0) {
        cout << "No students yet!" << endl;
        return;
    }

    cout << "\n" << string(75, '=') << endl;
    cout << left << setw(5)  << "ID"
         << setw(20) << "Name"
         << setw(10) << "Roll"
         << setw(8)  << "Math"
         << setw(9)  << "Physics"
         << setw(9)  << "English"
         << setw(8)  << "Avg"
         << setw(6)  << "Grade"
         << endl;
    cout << string(75, '-') << endl;

    for (int i = 0; i < count; i++) {
        Student s = students[i];
        cout << left
             << setw(5)  << s.id
             << setw(20) << s.name
             << setw(10) << s.rollNumber
             << setw(8)  << fixed << setprecision(1) << s.math
             << setw(9)  << s.physics
             << setw(9)  << s.english
             << setw(8)  << s.average
             << setw(6)  << s.grade
             << endl;
    }
    cout << string(75, '=') << endl;
    cout << "Total students: " << count << endl;
}

// ===========================================================
// Step 4 — Class statistics: topper, bottom, class average
// ===========================================================
void showStats() {
    if (count == 0) {
        cout << "No students!" << endl;
        return;
    }

    int topIndex = 0, bottomIndex = 0;
    float classTotal = 0;

    for (int i = 0; i < count; i++) {
        classTotal += students[i].average;
        if (students[i].average > students[topIndex].average)
            topIndex = i;
        if (students[i].average < students[bottomIndex].average)
            bottomIndex = i;
    }

    float classAvg = classTotal / count;

    int passed = 0;
    for (int i = 0; i < count; i++)
        if (students[i].average >= 50) passed++;

    cout << "\n=== CLASS STATISTICS ===" << endl;
    cout << "Total Students : " << count << endl;
    cout << "Class Average  : " << fixed << setprecision(1) << classAvg << endl;
    cout << "Passed         : " << passed << endl;
    cout << "Failed         : " << count - passed << endl;

    cout << "\nCLASS TOPPER : " << students[topIndex].name
         << " (" << students[topIndex].average << ", Grade "
         << students[topIndex].grade << ")" << endl;

    cout << "LOWEST SCORE : " << students[bottomIndex].name
         << " (" << students[bottomIndex].average << ", Grade "
         << students[bottomIndex].grade << ")" << endl;
}

// ===========================================================
// Sort by Average (ascending) — Bubble Sort
// ===========================================================
void sortByAverage() {
    if (count == 0) {
        cout << "No students to sort!" << endl;
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].average > students[j + 1].average) {
                // Swap students[j] and students[j+1]
                Student temp   = students[j];
                students[j]    = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "Students sorted by average (ascending)!" << endl;
    displayAll();
}

// ===========================================================
// BONUS (Medium): Sort by Name — Bubble Sort, alphabetical
// ===========================================================
void sortByName() {
    if (count == 0) {
        cout << "No students to sort!" << endl;
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].name > students[j + 1].name) {
                Student temp    = students[j];
                students[j]     = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "Students sorted alphabetically by name!" << endl;
    displayAll();
}

// ===========================================================
// BONUS (Easy): Search student by roll number
// ===========================================================
void searchByRoll() {
    if (count == 0) {
        cout << "No students yet!" << endl;
        return;
    }

    int roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;

    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == roll) {
            cout << "\n--- STUDENT FOUND ---" << endl;
            cout << "ID       : " << students[i].id << endl;
            cout << "Name     : " << students[i].name << endl;
            cout << "Roll No  : " << students[i].rollNumber << endl;
            cout << fixed << setprecision(1);
            cout << "Math     : " << students[i].math << endl;
            cout << "Physics  : " << students[i].physics << endl;
            cout << "English  : " << students[i].english << endl;
            cout << "Average  : " << students[i].average << endl;
            cout << "Grade    : " << students[i].grade << endl;
            return;
        }
    }

    cout << "No student found with roll number " << roll << endl;
}

// ===========================================================
// BONUS (Medium): Delete student by ID
// ===========================================================
void deleteById() {
    if (count == 0) {
        cout << "No students to delete!" << endl;
        return;
    }

    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    int indexToDelete = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "No student found with ID " << id << endl;
        return;
    }

    // Shift every student after the deleted one, one position back
    for (int i = indexToDelete; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;

    cout << "Student with ID " << id << " deleted successfully!" << endl;
}

// ===========================================================
// BONUS (Medium): Subject-wise class average
// ===========================================================
void subjectWiseAverage() {
    if (count == 0) {
        cout << "No students yet!" << endl;
        return;
    }

    float mathTotal = 0, physicsTotal = 0, englishTotal = 0;

    for (int i = 0; i < count; i++) {
        mathTotal    += students[i].math;
        physicsTotal += students[i].physics;
        englishTotal += students[i].english;
    }

    cout << "\n=== SUBJECT-WISE CLASS AVERAGE ===" << endl;
    cout << fixed << setprecision(1);
    cout << "Math    : " << mathTotal / count << endl;
    cout << "Physics : " << physicsTotal / count << endl;
    cout << "English : " << englishTotal / count << endl;
}

// ===========================================================
// Step 5 — Save all students to a file
// ===========================================================
void saveToFile() {
    ofstream file("students.txt");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    file << count << endl;
    for (int i = 0; i < count; i++) {
        Student s = students[i];
        file << s.id << "\n"
             << s.name << "\n"
             << s.rollNumber << "\n"
             << s.math << "\n"
             << s.physics << "\n"
             << s.english << "\n";
    }

    file.close();
    cout << "Saved " << count << " students!" << endl;
}

// ===========================================================
// Step 5 — Load all students from a file
// ===========================================================
void loadFromFile() {
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "No saved file found yet!" << endl;
        return; // no file yet, that's ok
    }

    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        Student s;
        file >> s.id;
        file.ignore();
        getline(file, s.name);
        file >> s.rollNumber
             >> s.math
             >> s.physics
             >> s.english;
        file.ignore();

        s.average = calcAverage(s);
        s.grade   = calcGrade(s.average);
        students[i] = s;
    }

    file.close();
    cout << "Loaded " << count << " students." << endl;
}

// ===========================================================
// Step 6 — Main Menu
// ===========================================================
void showMenu() {
    cout << "\n========== STUDENT RECORD SYSTEM ==========" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. View All Students" << endl;
    cout << "3. Show Class Statistics" << endl;
    cout << "4. Sort by Average" << endl;
    cout << "5. Sort by Name (Bonus)" << endl;
    cout << "6. Search Student by Roll Number (Bonus)" << endl;
    cout << "7. Delete Student by ID (Bonus)" << endl;
    cout << "8. Show Subject-wise Class Average (Bonus)" << endl;
    cout << "9. Save to File" << endl;
    cout << "10. Load from File" << endl;
    cout << "0. Exit" << endl;
    cout << "=============================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    // Try to load any previously saved students when the program starts
    loadFromFile();

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                showStats();
                break;
            case 4:
                sortByAverage();
                break;
            case 5:
                sortByName();
                break;
            case 6:
                searchByRoll();
                break;
            case 7:
                deleteById();
                break;
            case 8:
                subjectWiseAverage();
                break;
            case 9:
                saveToFile();
                break;
            case 10:
                loadFromFile();
                break;
            case 0:
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
