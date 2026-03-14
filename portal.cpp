#include<iostream>
#include<cctype>
#include<fstream>
#include<string>
using namespace std;


const int maxStudents = 100;
const int numQuiz = 3;
const int numAssign = 2;


struct Student {

	string name;

	int rollNo;

	float quiz[numQuiz];

	float assign[numAssign];

	char section;

	float mid;

	float final;

	char grade;

	float percent;

	float total;

};

// students array of maxStudents and of type Student struct

Student students[maxStudents];

// Number of students entered

int studentCount = 0;

// Functions

void LoadFromFile();

void SaveToFile();

void addStudent();

void updateStudent();

void deleteStudent();

void displayAll();

void searchStudent(int rollno);

void calculateResults();

void assignGrade();

void classStats();

void sortStudents();

void topScorer();

void lowestScorer();

void classAverage();





int main() {
	LoadFromFile();
	int choice;
	do {
		cout << " \n----------------------- Student Performance Management System!----------------------- \n";
		cout << " 1. Add Student \n 2. Update Student \n 3. Delete Student \n 4. Display All Students \n 5. Search Student By their Roll no. \n 6. Calculate Results \n 7. Class Statistics \n 8. topScorer \n 9. lowestScorer \n 10. Class Average \n 11. Exit \n ";
		cout << " \n--------------------------------------------------------------------------------------" << endl;
		cout << " Enter your choice : \n";

		cin >> choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << "Invalid Input! Enter choice again ";
			cin >> choice;
		}
		if (choice == 1) {
			addStudent();
		}
		else if (choice == 2) {
			updateStudent();
		}
		else if (choice == 3) {
			deleteStudent();
		}
		else if (choice == 4) {
			displayAll();
		}

		else if (choice == 5) {
			int roll;
			cout << "Enter the roll No you want to search for: ";
			cin >> roll;
			while (cin.fail() || roll < 1 || roll > 100)
			{
				cin.clear();
				cin.ignore();
				cout << endl << "Invalid input! Enter roll number again btw(1-100): ";
				cin >> roll;
			}
			searchStudent(roll);
		}
		else if (choice == 6) {
			calculateResults();
			assignGrade();
			cout << " Results Calculated Successfully! \n ";
			displayAll();
		}

		else if (choice == 7) {
			calculateResults();
			assignGrade();
			classStats();
			displayAll();
		}
		else if (choice == 8) {
			calculateResults();
			assignGrade();
			topScorer();

		}
		else if (choice == 9) {
			lowestScorer();
		}
		else if (choice == 10) {
			classAverage();
		}
		else if (choice == 11) {
			SaveToFile();
			cout << " Closing Student Management System ! .... \n ";
		}
		else {
			cout << "Invalid Choice !\n";
		}

	} while (choice != 11);
	return 0;
}
// convert string to upper
string toUppercase(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] = s[i] - 32;   // convert to uppercase
		}
	}
	return s;
}

// marks validator 
int getValidatedMark(int min, int max) {
	string input;
	int value;
	bool valid = false;

	while (!valid) {
		cin >> input;

		// Check if all characters are digits
		valid = true;
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				valid = false;
				break;
			}
		}

		if (!valid) {
			cout << "Invalid input! Enter a number between " << min << " and " << max << ": ";
			continue;
		}

		// Convert to integer
		value = stoi(input);

		// Check range
		if (value < min || value > max) {
			cout << "Invalid input! Enter a number between " << min << " and " << max << ": ";
			valid = false;
		}
	}

	return value;
}

// Function Signatures

void LoadFromFile() {

	// Loads student.txt from storage

	ifstream studentFileIn("students.txt");

	// Error Handeling incase .txt is not found

	if (!studentFileIn) {

		cout << " No file exists ";

		return;

	}

	studentCount = 0;

	// Taking data from the file

	while (studentFileIn >> students[studentCount].rollNo) {

		studentFileIn.ignore(1000, '\n');
		getline(studentFileIn, students[studentCount].name);

		studentFileIn >> students[studentCount].section;
		studentFileIn.ignore(1000, '\n');
		for (int i = 0; i < numQuiz; i++) {

			studentFileIn >> students[studentCount].quiz[i];

		}

		studentFileIn.ignore(1000, '\n');

		for (int i = 0; i < numAssign; i++) {

			studentFileIn >> students[studentCount].assign[i];

		}

		studentFileIn.ignore(1000, '\n');

		studentFileIn >> students[studentCount].mid;
		studentFileIn.ignore(1000, '\n');
		studentFileIn >> students[studentCount].final;
		studentFileIn.ignore(1000, '\n');
		studentCount++;

	}

	// Closes File

	studentFileIn.close();

}

void SaveToFile() {

	sortStudents();

	// Loads student.txt from storage

	ofstream studentFileOut("students.txt", ios::trunc);

	for (int i = 0; i < studentCount; i++) {

		studentFileOut << students[i].rollNo << "\n";
		studentFileOut << students[i].name << "\n";
		studentFileOut << students[i].section << "\n";
		for (int j = 0; j < numQuiz; j++) {

			studentFileOut << students[i].quiz[j] << " ";

		}

		studentFileOut << "\n";

		for (int j = 0; j < numAssign; j++) {

			studentFileOut << students[i].assign[j] << " ";

		}

		studentFileOut << "\n";
		studentFileOut << students[i].mid;
		studentFileOut << "\n";
		studentFileOut << students[i].final;
		studentFileOut << "\n";

	}

	// Closes File

	studentFileOut.close();

}

void addStudent() {

	if (studentCount >= maxStudents) {
		cout << " No more students can be added! ";
		return;
	}

	Student stud;

	string input;
	bool valid = false;

	while (!valid)
	{
		cout << "Enter Roll No. (1 - 100): ";
		cin >> input;

		// Check if all characters are digits
		bool isNumber = true;
		for (int i = 0; i < input.length(); i++)
		{
			if (!isdigit(input[i]))
			{
				isNumber = false;
				break;
			}
		}

		if (!isNumber)
		{
			cout << "Invalid! Only enter integer values between 1 - 100.\n";
			continue;
		}

		// Convert string to number
		stud.rollNo = stoi(input);

		// Check range
		if (stud.rollNo < 1 || stud.rollNo > 100)
		{
			cout << "Invalid! Roll number must be 1 - 100.\n";
			continue;
		}

		// Check uniqueness
		bool duplicate = false;
		for (int i = 0; i < studentCount; i++)
		{
			if (students[i].rollNo == stud.rollNo)
			{
				duplicate = true;
				break;
			}
		}

		if (duplicate)
		{
			cout << "Invalid! This Roll No. is already taken. Enter a unique Roll No.\n";
			continue;
		}

		// If we reach here, Roll No. is valid and unique
		valid = true;
	}



	cin.ignore();

	cout << " Enter your Name : ";

	getline(cin, stud.name);

	string sec;

	cout << "Enter your Section: ";
	cin >> sec;


	sec = toUppercase(sec);

	// Validate
	while (sec.length() != 1 || sec[0] < 'A' || sec[0] > 'Z')
	{
		cout << "Invalid input! Enter Section again (A-Z only): ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> sec;

		sec = toUppercase(sec);   // convert again after input
	}

	stud.section = sec[0];  // Store valid section


	// Quizzes
	for (int i = 0; i < numQuiz; i++) {
		cout << "Enter Quiz " << i + 1 << " marks (0-10): ";
		stud.quiz[i] = getValidatedMark(0, 10);
	}

	// Assignments
	for (int i = 0; i < numAssign; i++) {
		cout << "Enter Assignment " << i + 1 << " marks (0-10): ";
		stud.assign[i] = getValidatedMark(0, 10);
	}

	// Midterm
	cout << "Enter Midterm marks (0-50): ";
	stud.mid = getValidatedMark(0, 50);

	// Final
	cout << "Enter Final marks (0-100): ";
	stud.final = getValidatedMark(0, 100);


	// Store student
	students[studentCount++] = stud;


	cout << " Student Added Successfully! \n ";
	SaveToFile();

}

void updateStudent() {

	int roll;
	cout << " Enter the roll no: ";
	cin >> roll;

	while (cin.fail() || roll < 1 || roll > 100) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << " Invalid roll! Enter again btw(1-100): ";
		cin >> roll;
	}

	int index = -1;


	for (int i = 0; i < studentCount; i++) {
		if (students[i].rollNo == roll) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		cout << " Student Record Not Found.\n";
		return;
	}

	cout << "\nWhat do you want to update?\n";
	cout << " 1. Name\n"
		<< " 2. Section\n"
		<< " 3. Quiz Marks\n"
		<< " 4. Assignment Marks\n"
		<< " 5. Midterm Marks\n"
		<< " 6. Final Marks\n";

	int choice;
	cin >> choice;

	while (cin.fail() || choice < 1 || choice > 6) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << " Invalid choice! Enter again: ";
		cin >> choice;
	}

	switch (choice) {

	case 1: {
		cin.ignore();
		cout << " Enter new Name: ";
		getline(cin, students[index].name);
		break;
	}

	case 2: {
		cout << " Enter new Section (A-Z): ";
		cin >> students[index].section;

		while (students[index].section < 'A' || students[index].section > 'Z') {
			cout << " Invalid! Enter A-Z: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> students[index].section;
		}
		break;
	}

	case 3: {
		int q;
		cout << " Which quiz to update (1-3): ";
		cin >> q;

		while (cin.fail() || q < 1 || q > 3) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " Invalid! Enter (1-3): ";
			cin >> q;
		}

		cout << " Enter new marks (0-10): ";
		cin >> students[index].quiz[q - 1];

		while (cin.fail() || students[index].quiz[q - 1] < 0 || students[index].quiz[q - 1] > 10) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " Invalid! Enter marks (0-10): ";
			cin >> students[index].quiz[q - 1];
		}
		break;
	}

	case 4: {
		int a;
		cout << " Which assignment to update (1-2): ";
		cin >> a;

		while (cin.fail() || a < 1 || a > 2) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " Invalid! Enter (1-2): ";
			cin >> a;
		}

		cout << " Enter new marks (0-10): ";
		cin >> students[index].assign[a - 1];

		while (cin.fail() || students[index].assign[a - 1] < 0 || students[index].assign[a - 1] > 10) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " Invalid! Enter marks (0-10): ";
			cin >> students[index].assign[a - 1];
		}
		break;
	}

	case 5: {
		cout << " Enter new midterm marks (0-50): ";
		cin >> students[index].mid;

		while (cin.fail() || students[index].mid < 0 || students[index].mid > 50) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " Invalid! Enter marks (0-50): ";
			cin >> students[index].mid;
		}
		break;
	}

	case 6: {
		cout << " Enter new final marks (0-100): ";
		cin >> students[index].final;

		while (cin.fail() || students[index].final < 0 || students[index].final > 100) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " Invalid! Enter marks (0-100): ";
			cin >> students[index].final;
		}
		break;
	}
	}

	cout << "\n Student Record Updated Successfully!\n";
	SaveToFile();
}


void deleteStudent() {
	int roll;
	cout << " Enter the studnet's roll you want to delete : ";
	cin >> roll;
	while (cin.fail() || roll < 1 || roll > 100)
	{
		cin.clear();
		cin.ignore();
		cout << endl << "Invalid input! Enter roll number again btw(1-100): ";
		cin >> roll;
	}
	bool found = false;
	for (int i = 0; i < studentCount; i++) {
		if (students[i].rollNo == roll) {
			for (int j = i; j < studentCount - 1; j++) {
				students[j] = students[j + 1];
			}
			found = true;
			studentCount--;
			break;
		}
	}
	if (found == false) {
		cout << " Student not found ";
	}
	else {
		SaveToFile();
		cout << " Student Record Deleted Successfully !!! \n";
	}
}
void displayAll() {
	cout << "----------------------------------------\n";
	cout << " All Students Records : \n";
	for (int i = 0; i < studentCount; i++) {
		cout << "Roll No: " << students[i].rollNo << endl;
		cout << "Name: " << students[i].name << endl;
		cout << "Section: " << students[i].section << endl;
		cout << "Quiz Marks 1: " << students[i].quiz[0] << endl;
		cout << "Quiz Marks 2: " << students[i].quiz[1] << endl;
		cout << "Quiz Marks 3: " << students[i].quiz[2] << endl;
		cout << "Assignment Marks 1: " << students[i].assign[0] << endl;
		cout << "Assignment Marks 2: " << students[i].assign[1] << endl;
		cout << "Midterm Marks: " << students[i].mid << endl;
		cout << "Final Marks: " << students[i].final << endl;
		cout << "Total Marks: " << students[i].total << endl;
		cout << "Percentage: " << students[i].percent << "%" << endl;
		cout << "Grade: " << students[i].grade << "\n";
	}
	cout << "----------------------------------------\n";
	return;
}

void searchStudent(int rollno) {
	bool found = false;
	int j = 0;
	for (int i = 0; i < studentCount; i++) {
		if (students[i].rollNo == rollno) {
			found = true;
			cout << " Found Student Data : ";
			cout << " Name : " << students[i].name << endl;
			cout << " Roll No : " << students[i].rollNo << endl;
			cout << " Section : " << students[i].section << endl;
			for (int j = 1; j <= numQuiz; j++) {
				cout << " Quiz " << j << " marks : " << students[i].quiz[j - 1] << endl;
			}
			for (int j = 1; j <= numAssign; j++) {
				cout << " Assignment " << j << " marks : " << students[i].assign[j - 1] << endl;
			}
			cout << " Mid marks : " << students[i].mid << endl;
			cout << " Final marks : " << students[i].final << endl;
		}
	}

	if (found == false) {
		cout << "Not Found!!" << endl;
	}
}

void calculateResults() {


	if (studentCount == 0) {
		cout << " No students available for results. \n";
		return;
	}
	else {
		float quizTotal = 0;
		float assignTotal = 0;
		for (int i = 0; i < studentCount; i++) {
			quizTotal = 0;
			assignTotal = 0;
			for (int j = 0; j < numQuiz; j++) {
				quizTotal += students[i].quiz[j];
			}
			for (int j = 0; j < numAssign; j++) {
				assignTotal += students[i].assign[j];
			}
			students[i].total = quizTotal + assignTotal + students[i].mid + students[i].final;
			students[i].percent = float(students[i].total * 100 / 200.0);
		}
	}
	return;
}

void assignGrade() {
	sortStudents();

	for (int i = 0; i < studentCount; i++) {
		if (students[i].percent >= 90 && students[i].percent <= 100) {
			students[i].grade = 'A';
		}
		else if (students[i].percent >= 80 && students[i].percent < 90) {
			students[i].grade = 'B';
		}
		else if (students[i].percent >= 70 && students[i].percent < 80) {
			students[i].grade = 'C';
		}
		else if (students[i].percent >= 60 && students[i].percent < 70) {
			students[i].grade = 'D';
		}
		else if (students[i].percent >= 50 && students[i].percent < 60) {
			students[i].grade = 'E';
		}
		else {
			students[i].grade = 'F';
		}
	}
}

void classStats() {
	sortStudents();
	for (int i = 1; i <= studentCount; i++) {
		cout << "---------------------------------------------------------------------" << endl;
		cout << "Student no. " << i << endl;
		cout << students[i - 1].name << "    " << students[i - 1].rollNo << "    " << students[i - 1].section << endl;
		cout << students[i - 1].quiz[0] << "    " << students[i - 1].quiz[1] << "    " << students[i - 1].quiz[2] << endl;
		cout << students[i - 1].assign[0] << "    " << students[i - 1].assign[1] << "    " << students[i - 1].mid << endl;
		cout << students[i - 1].final << "    " << students[i - 1].total << "    " << students[i - 1].grade << endl;
		cout << "---------------------------------------------------------------------" << endl;
	}
}
void topScorer() {


	if (studentCount == 0) {
		cout << "No students available.\n";
		return;
	}

	calculateResults();
	assignGrade();
	sortStudents();

	float highest = students[0].percent;

	cout << "\n========== TOP SCORER(S) ==========\n";

	for (int i = 0; i < studentCount; i++) {
		if (students[i].percent == highest) {

			cout << "\nName       : " << students[i].name;
			cout << "\nRoll No    : " << students[i].rollNo;
			cout << "\nSection    : " << students[i].section;
			cout << "\nTotal Marks: " << students[i].total;
			cout << "\nPercentage : " << students[i].percent << "%";
			cout << "\nGrade      : " << students[i].grade << endl;

		}
		else break;
	}

	cout << "\n===================================\n";
}



void lowestScorer() {
	sortStudents();
	calculateResults();
	assignGrade();

	if (studentCount == 0) {
		cout << "No students available.\n";
		return;
	}



	float lowest = students[studentCount - 1].percent;

	cout << "\n======== LOWEST SCORER(S) =========\n";

	for (int i = studentCount - 1; i >= 0; i--) {
		if (students[i].percent == lowest) {

			cout << "\nName       : " << students[i].name;
			cout << "\nRoll No    : " << students[i].rollNo;
			cout << "\nSection    : " << students[i].section;
			cout << "\nTotal Marks: " << students[i].total;
			cout << "\nPercentage : " << students[i].percent << "%";
			cout << "\nGrade      : " << students[i].grade << endl;


		}
		else break;
	}

	cout << "\n===================================\n";
}




void classAverage() {
	if (studentCount == 0) {
		cout << "No students available.\n";
		return;
	}

	float quizAvg = 0, assignAvg = 0, midAvg = 0, finalAvg = 0, totalAvg = 0, percentAvg = 0;

	for (int i = 0; i < studentCount; i++) {
		float quizSum = 0, assignSum = 0;

		for (int q = 0; q < numQuiz; q++)
			quizSum += students[i].quiz[q];

		for (int a = 0; a < numAssign; a++)
			assignSum += students[i].assign[a];

		quizAvg += quizSum;
		assignAvg += assignSum;
		midAvg += students[i].mid;
		finalAvg += students[i].final;
		totalAvg += students[i].total;
		percentAvg += students[i].percent;
	}

	quizAvg /= studentCount;
	assignAvg /= studentCount;
	midAvg /= studentCount;
	finalAvg /= studentCount;
	totalAvg /= studentCount;
	percentAvg /= studentCount;

	cout << "\n----------- CLASS AVERAGE -----------\n";
	cout << "Average Quiz Total     : " << quizAvg << endl;
	cout << "Average Assignment Total: " << assignAvg << endl;
	cout << "Average Mid Marks      : " << midAvg << endl;
	cout << "Average Final Marks    : " << finalAvg << endl;
	cout << "Average Total Marks    : " << totalAvg << endl;
	cout << "Average Percentage     : " << percentAvg << "%" << endl;
	cout << "-------------------------------------\n";
}


void sortStudents() {
	Student temp;
	for (int i = 0; i < studentCount - 1; i++) {
		for (int j = i + 1; j < studentCount; j++) {
			if (students[i].total < students[j].total) {
				temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}
}
