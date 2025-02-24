#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	string line[10];
	fstream myFile;
	myFile.open("writeOnThisFile.txt", ios::out);
	if (myFile.is_open())
	{
		myFile << "Hello I have written something here.\n" <<
			"I hope this text will help you.\n";
		myFile.close();
	}

	myFile.open("writeOnThisFile.txt", ios::app);
	if (myFile.is_open())
	{
		myFile << "Here my advise for you:\n" <<
			"Don't be afraid to try something new!\n";
		myFile.close();
	}

	myFile.open("writeOnThisFile.txt", ios::in);
	if (myFile.is_open())
	{
		
		for (int i = 0; i < 4; i++) 
			getline(myFile, line[i]);
		
		myFile.close();
	}

	for (int i = 0; i < 4; i++)
		cout << line[i] << endl;
	
}