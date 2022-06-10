#pragma once
#include<iostream>
#include <string>
#include <stdexcept>
#include<fstream>
class StudentQueue
{
	struct Student
	{
		std::string name;
		unsigned int groupNumber;
		int waitingTime;
		Student* next;

		Student(std::string name, unsigned int groupNumber)
		{
			this->name = name;
			this->groupNumber = groupNumber;
			this->waitingTime = 0;
			next = nullptr;
		}

	};
	Student* head;
	Student* tail;


	void Free();
	void CopyFrom(const StudentQueue& other);
	bool IsEmpty() const;

public:
	StudentQueue();
	StudentQueue(const StudentQueue& other);
	StudentQueue operator=(const StudentQueue& other);
	~StudentQueue();

	void Print(Student* head);
	void Enqueue(Student* student);
	Student* Dequeue();
	std::string Peek();
	void AddInQueue(std::ifstream& file);
	void WaitingTime();
	bool TryToFindFriend(std::string name, unsigned int groupNumber);
	void InsertAfter(Student* head, std::string name, unsigned int groupNumber);

}; 
