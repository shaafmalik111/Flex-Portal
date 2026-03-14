# Student Performance Management System (C++)

A **console-based Student Performance Management System** written in C++ that allows users to manage student records, calculate results, assign grades, and store data using file handling.

---

## Features

- Add new student records
- Update student information
- Delete student records
- Search student by roll number
- Display all student records
- Calculate total marks and percentage
- Automatic grade assignment
- View class statistics
- Find top scorer
- Find lowest scorer
- Calculate class average
- Data persistence using file handling (`students.txt`)

---

## Technologies Used

- **C++**
- **Structures**
- **Arrays**
- **File Handling (`fstream`)**
- **Input Validation**
- **Sorting Algorithms**

---

## How It Works

The system stores student information such as:

- Roll Number  
- Name  
- Section  
- Quiz Marks (3 quizzes)  
- Assignment Marks (2 assignments)  
- Midterm Marks  
- Final Exam Marks  

It calculates:

- **Total Marks**
- **Percentage**
- **Grade (A–F)**

All records are saved in a file called **`students.txt`** so data remains stored even after the program closes.

---

## How to Run

1. Clone the repository

```bash
git clone https://github.com/your-username/student-management-system.git
````

2. Open the project in any C++ compiler (VS Code, Dev C++, CodeBlocks, etc.)

3. Compile the program

```bash
g++ main.cpp -o student_system
```

4. Run the program

```bash
./student_system
```

---

## Grade Criteria

| Percentage | Grade |
| ---------- | ----- |
| 90 – 100   | A     |
| 80 – 89    | B     |
| 70 – 79    | C     |
| 60 – 69    | D     |
| 50 – 59    | E     |
| Below 50   | F     |

---

## Author

**Shaaf Malik**

```

If you want, I can also show you **3 small improvements that will make your GitHub project look much more professional** (like badges, screenshots, and project structure).
```
