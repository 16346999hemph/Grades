// Anyshya Hemphill
// Assignment 4 - Grades
// This program reads a file containing student id and their submissions, calculates whether each student's submission matches the first sequence of correct answers, and displays the results.

#include "grades.h"

using namespace std;

// Check if string is numeric
bool isNumeric(const string& str) {
	if (str.empty()) return false;
	for (char num : str) {
		if (num < '0' || num > '9') return false;
	}
	return true;
}

// Score counting logic
int countScore(const string& submission, const string& correctAnswers) {
	int score = 0;
	for (size_t i = 0; i < correctAnswers.length() && i < submission.length(); ++i) {
		if (submission[i] == correctAnswers[i]) score += 2;
		else if (submission[i] != ' ') score += 1;
	}
	return score;
}

// Grade assignment
char getLetterGrade(float percentage) {
	if (percentage >= 90) return 'A';
	else if (percentage >= 80) return 'B';
	else if (percentage >= 70) return 'C';
	else if (percentage >= 60) return 'D';
	else return 'F';
}

// Trim leading/trailing whitespace
void trimWhitespace(string* strPtr) {
	if (strPtr == nullptr) return;

	size_t first = strPtr->find_first_not_of(" \t\n\r\f\v");
	if (first == string::npos) {
		strPtr->clear();
		return;
	}
	size_t last = strPtr->find_last_not_of(" \t\n\r\f\v");
	*strPtr = strPtr->substr(first, last - first + 1);
}

int main() {
	const int maxScore = 40;

	ifstream* inputFilePtr = new ifstream("C:/Users/cyber/Downloads/student.txt");
	if (!inputFilePtr->is_open()) {
		cerr << "Error: Could not open input file.\n";
		delete inputFilePtr;
		return 1;
	}

	ofstream* errorFilePtr = new ofstream("error.txt");
	if (!errorFilePtr->is_open()) {
		cerr << "Error: Could not open error.txt for writing.\n";
		delete errorFilePtr;
		delete inputFilePtr;
		return 1;
	}

	string* correctAnswersPtr = new string();
	if (getline(*inputFilePtr, *correctAnswersPtr)) {
		trimWhitespace(correctAnswersPtr);
	}

	vector<studentInfo> students;
	string* linePtr = new string();

	
	while (getline(*inputFilePtr, *linePtr)) {// Goes through the lines in the student.txt file 
		trimWhitespace(linePtr);
		if (linePtr->empty()) continue;

		size_t spacePos = linePtr->find(' ');
		if (spacePos == string::npos) {
			*errorFilePtr << "Rejected Record: Malformed line -> " << *linePtr << endl;
			continue;
		}

		string* idPtr = new string(linePtr->substr(0, spacePos));
		string* submissionPtr = new string(linePtr->substr(spacePos + 1));

		// Removes whitespace from ID and Submission strings 
		trimWhitespace(idPtr);
		trimWhitespace(submissionPtr);

		// Ensures isNumeric IDs meet the numeric condition
		if (!isNumeric(*idPtr)) {
			*errorFilePtr << "Rejected Record: Invalid Student ID '" << *idPtr << "' in line: " << *linePtr << endl;
			delete idPtr;
			delete submissionPtr;
			continue;
		}


		//Defines score, percentage, and grade to be output eventually for the user to see
		int score = countScore(*submissionPtr, *correctAnswersPtr);
		float percentage = (static_cast<float>(score) / maxScore) * 100.0f;
		char grade = getLetterGrade(percentage);

		students.push_back({ *idPtr, *submissionPtr, score, percentage, grade });

		// Frees memory from ID and submissions 
		delete idPtr;
		delete submissionPtr;
	}

	// Formatting for the grade report of all the students
	cout << "\nQuiz Grading Report:\n";
	cout << "--------------------\n";
	cout << "Student ID\tScore\tPercentage\tGrade\n";
	cout << "---------------------------------------------\n";

	// Outputs the student IDs, scores out of 40, the percentages, and the official letter grade after calculation 
	for (const auto& student : students) {
		cout << student.studentID << "\t\t"
			<< student.score << "\t"
			<< student.percentage << "%\t\t"
			<< student.grade << endl;
	}

	// Freeing up the memory so there aren't any leakage or memory allocation errors
	inputFilePtr->close();
	errorFilePtr->close();

	delete inputFilePtr;
	delete correctAnswersPtr;
	delete linePtr;
	delete errorFilePtr;

	cout << "\nGrading complete. Rejected records saved to error.txt\n";
	return 0;
}




