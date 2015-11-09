#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void studentGrade(string studentName, int grade);

int main2()
{
	string testName;

	getline(cin, testName);

	studentGrade(testName, 4);

	return 0;
}

void studentGrade(string studentName, int grade)
{
	cout << "The student " << studentName << " has grade " << grade << ".";
}