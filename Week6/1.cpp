#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void showName(string name);

int main1()
{
	string testName;

	getline(cin, testName);

	showName(testName);

	return 0;
}

void showName(string name)
{
	cout << "And his name is " << name << endl;
}