# CloudExify-Project-2
# Student Record System — C++ Month 1, Project 2

**CloudExify Summer Internship 2026**

## Student Info
- **Name:** [Nitalia Zafar]
- **Registration Number:** [CX-INT-2026-CPP-0364]

## Description
A console-based Student Record System built in C++ that uses a `struct` to
group each student's data (name, roll number, marks, average, grade) into a
single unit. Students are stored in an array, and the program supports
adding, viewing, sorting, searching, deleting, and saving/loading records
to a file.

## Features
- Add a student (with input validation — marks must be between 0 and 100)
- View all students in a formatted table
- Show class statistics (topper, lowest scorer, class average, pass/fail count)
- Sort students by average marks (Bubble Sort — ascending)
- Save all student records to a file (`students.txt`)
- Load student records from file (also runs automatically on startup)

### Bonus Features
- Letter grade (A/B/C/D/F) calculated automatically for each student
- Sort students alphabetically by name
- Search for a student by roll number
- Delete a student by ID
- Show subject-wise class average (Math, Physics, English)

## How to Run

1. Make sure you have a C++ compiler installed (e.g. `g++`).
2. Open a terminal in the project folder.
3. Compile the program:
```bash
   g++ -o student_system student_system.cpp
```
4. Run it:
```bash
   ./student_system
```
   On Windows, run:
```bash
   student_system.exe
```
5. Use the on-screen menu to add students, view records, sort, search, delete,
   and save/load data. Your data is saved to `students.txt` in the same folder
   and will automatically reload the next time you run the program.

## Concepts Used
- `struct` for grouping related data
- Arrays of structs
- Functions that take/return structs
- File I/O (`ofstream` / `ifstream`)
- Bubble sort
- `getline()` for reading names with spaces
- `setw()` / `setprecision()` for formatted table output
