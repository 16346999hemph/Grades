#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function to read student data from the file and return correct answers
void readFile(const string& filename, vector<string>& studentIDs, vector<string>& submissions, string& correctAnswers);

// Function to check if the submission matches the correct answers
bool checkSubmission(const string& submission, const string& correctAnswers);

// Function to calculate the number of correct answers
int countCorrectAnswers(const string& submission, const string& correctAnswers);

// Function to calculate letter grades based on percentage
char getLetterGrade(float percentage);

// Structure to store student information
struct studentInfo {
    string studentID;
    string submission;
    int score;
    float percentage;
    char grade;
};
