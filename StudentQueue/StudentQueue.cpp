#include "StudentQueue.h"

void StudentQueue::Student::Print()
{
	std::cout << "[" << name << "] " << waitingTime << "m  [" << groupNumber << "]" << std::endl;
}

void StudentQueue::Free()
{
	Student* iter = head;
	while (iter != nullptr)
	{
		Student* prev = iter;
		iter = iter->next;
		delete prev;
	}
	head = tail = nullptr;
}

void StudentQueue::CopyFrom(const StudentQueue& other)
{
	Student* iter = other.head;
	while (iter != nullptr)
	{
		Enqueue(iter);
		iter = iter->next;
	}
}

bool StudentQueue::IsEmpty() const
{
	if (head == NULL && tail == NULL)
		return true;
	else
		return false;

}

StudentQueue::StudentQueue()
{
	head = nullptr;
	tail = nullptr;
}

StudentQueue::StudentQueue(const StudentQueue& other)
{
	CopyFrom(other);
}

StudentQueue StudentQueue::operator=(const StudentQueue& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

StudentQueue::~StudentQueue()
{
	Free();
}

void StudentQueue::Enqueue(Student* student)
{

	if (IsEmpty())
	{
		head = student;
		tail = student;
	}
	else
	{
		tail->next = student;
		tail = student;
	}
}


void StudentQueue::Dequeue()
{
	if (IsEmpty())
	{
		throw std::runtime_error("The Queue is Empty!");
	}

	Student* temp = head;
	head = head->next;
	if (head == NULL)
		tail = NULL;

	delete (temp);
}


std::string StudentQueue::Peek()
{
	if (IsEmpty())
	{
		throw std::runtime_error("The Queue is Empty!");
	}
	return head->name;
}

void StudentQueue::AddInQueue(std::ifstream& file)
{
	std::string name;
	std::string number;

	int count = 0;
	bool FindFirend = false;

	while (!file.eof())
	{
		std::getline(file, name, ' ');
		std::getline(file, number);
		count++;
		unsigned int groupNumber = std::stoi(number);
		Student* newStudent = new Student(name, groupNumber);
		FindFirend = TryToFindFriend(name, groupNumber);

		if (FindFirend == true)
		{
			InsertAfter(head, name, groupNumber);
		}
		else
		{
			Enqueue(newStudent);
		}
		WaitingTime();
		if (count % 2 == 0)
		{
			head->Print();
			Dequeue();
		}
	}
	while (head != nullptr)
	{
		count++;
		WaitingTime();
		if (count % 2 == 0)
		{
			head->Print();
			Dequeue();
		}
	}
}
bool StudentQueue::TryToFindFriend(std::string name, unsigned int groupNumber)
{
	Student* iter = head;
	if (iter == NULL)
		return false;
	while (iter != NULL)
	{
		if (iter->groupNumber == groupNumber && iter->name != name)
		{
			return true;
		}
		iter = iter->next;
	}
}
void StudentQueue::WaitingTime()
{
	Student* iter = head;
	int count = 0;
	while (iter != NULL)
	{
		iter->waitingTime = iter->waitingTime + 1;
		iter = iter->next;
	}
}
void StudentQueue::InsertAfter(Student* head, std::string name, unsigned int groupNumber)
{
	Student* newStudent = new Student(name, groupNumber);
	if (groupNumber == head->groupNumber) {
		newStudent->next = head->next;
		head->next = newStudent;
		return;
	}

	Student* temp = head;
	while (temp->groupNumber != groupNumber) {
		temp = temp->next;
		if (temp == NULL) {
			return;
		}
	}
	newStudent->next = temp->next;
	temp->next = newStudent;
}