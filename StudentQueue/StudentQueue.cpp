#include "StudentQueue.h"


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
	return head == nullptr;
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


StudentQueue::Student* StudentQueue::Dequeue()
{
	if (IsEmpty())
	{
		throw std::runtime_error("The Queue is Empty!");
	}
	else if (head == tail)
	{
		Student* element = head;
		delete head;

		head = nullptr;
		tail = nullptr;

		return element;
	}
	else
	{
		Student* element = head;
		Student* temp = head->next;

		delete head;

		head = temp;
		return element;
	}

}

void StudentQueue::Print(Student* newStudent)
{
	newStudent = head;
	std::cout << "-----------At the Queue Is --------\n";
	while (newStudent != NULL)
	{
		std::cout << "[" << newStudent->name << "] " << newStudent->waitingTime << "m  [" << newStudent->groupNumber << "]" << std::endl;
		newStudent = newStudent->next;
	}
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
			Dequeue();
		}
		Print(newStudent);

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