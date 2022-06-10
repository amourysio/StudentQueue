#include<iostream>
#include<string>
#include<fstream>
#include"StudentQueue.h"

using namespace std;

void openFile(ifstream&,string);
void processFile(ifstream&);

int main()
{

	std::ifstream myFile;
	openFile(myFile, "students.txt");
	StudentQueue studentQueue;
	studentQueue.AddInQueue(myFile);

	myFile.close();

	return 0;
}

void openFile(ifstream& myFile, string fileName)
{
	myFile.open(fileName);
	if (myFile.is_open())
	{
		cout << "Successfully opened file!" << endl;
	}
	else
	{
		cout << "Failed to opened file!" << endl;
		exit(-1);
	}
}
void processFile(ifstream& myFile)
{
	string line;
	while (!myFile.eof())
	{
		getline(myFile, line);
		if (myFile.good())
		{
			cout << line << endl;
		}
	}
}
