#include"DatabaseL.h"


void DataBaseLL::copy(const DataBaseLL& other)
{
	if (other.first == nullptr)
		return;
	Node* curr = other.first;
	Node* currThis = new Node();
	currThis->row = curr->row;
	currThis->appearance = curr->appearance;
	currThis->next = nullptr;
	curr = curr->next;
	first = currThis;
	while (curr) {
		currThis->next = new Node();
		currThis->next->row = curr->row;
		currThis->next->appearance = curr->appearance;
		last = currThis;
		currThis = currThis->next;
		curr = curr->next;
	}
	name = other.name;
	rwInfo = other.rwInfo;
}

void DataBaseLL::clean()
{
	Node* toDelete = first;
	while (first) {
		toDelete = first;
		first = first->next;
		delete toDelete;
	}
	name = "";
	rwInfo = "";
	first = nullptr;
	last = nullptr;
	indexedAt = 0;
}

DataBaseLL::DataBaseLL()
{
	first = nullptr;
	last = nullptr;
	name = "";
	rwInfo = "";
	indexedAt = 0;

}

DataBaseLL::DataBaseLL(std::string rw, std::string tableInfo, std::string nam)
{
	indexedAt = indexedAtF(tableInfo);
	name = nam;
	rwInfo = tableInfo;
	first = new Node();
	first->appearance = 0;
	first->row = rw;
	first->next = nullptr;
	last = first;
}

DataBaseLL::DataBaseLL(const DataBaseLL& other)
{
	copy(other);
}

DataBaseLL::DataBaseLL(DataBaseLL&& other)
{
	first = other.first;
	last = other.last;
	name = other.name;
	rwInfo = other.rwInfo;
	indexedAt = other.indexedAt;
	other.first = nullptr;
	other.last = nullptr;
	other.name = "";
	other.rwInfo = "";
	other.indexedAt = 0;
}

DataBaseLL& DataBaseLL::operator=(const DataBaseLL& other)
{
	if (this != &other) {
		clean();
		copy(other);
	}
	return *this;
}

DataBaseLL& DataBaseLL::operator=(DataBaseLL&& other)
{
	if (this != &other) {
		first = other.first;
		last = other.last;
		name = other.name;
		indexedAt = other.indexedAt;
		other.first = nullptr;
		other.last = nullptr;
		other.name = "";
		other.indexedAt = 0;
	}
	return *this;
}

DataBaseLL::~DataBaseLL()
{
	clean();
}

const std::string& DataBaseLL::front() const
{
	return first->row;
}

const std::string& DataBaseLL::back() const
{
	return last->row;
}

const std::string& DataBaseLL::at(int index) const
{
	if (index == 0)
		return front();
	Node* curr = first;
	while (index > 0) {
		curr = curr->next;
		index--;
	}
	return curr->row;
}

void DataBaseLL::push_front(const std::string& val)
{
	Node* newElem = new Node();
	newElem->row = val;
	newElem->appearance = 0;
	newElem->next = first;
	first = newElem;
}

void DataBaseLL::push_end(const std::string& val)
{
	Node* newNode = new Node();
	newNode->row = val;
	newNode->appearance = 0;
	newNode->next = nullptr;
	last->next = newNode;
	last = newNode;
}

void DataBaseLL::push_at(const std::string& val, int index)
{
	if (index == 0) {
		push_front(val);
		return;
	}
	Node* curr = first;
	Node* prev = curr;
	while (index > 0) {
		prev = curr;
		curr = curr->next;
		index--;
	}
	Node* newNode = new Node();
	newNode->row = val;
	newNode->appearance = 0;
	newNode->next = curr;
	prev->next = newNode;

}

void DataBaseLL::pop_front()
{
	Node* toDelete = first;
	first = toDelete->next;
	delete toDelete;
}

void DataBaseLL::pop_back()
{
	Node* toDelete = first;
	while (toDelete->next != last) {
		toDelete = toDelete->next;
	}
	last = toDelete;
	toDelete = toDelete->next;
	delete toDelete;

}

void DataBaseLL::pop_at(int index)
{
	Node* curr = first;
	Node* prev = first;
	while (index > 0) {
		prev = curr;
		curr = curr->next;
		index--;
	}
	prev->next = curr->next;
	curr->next = nullptr;
	delete curr;
}

const std::string& DataBaseLL::getName() const
{
	return name;
}

const void DataBaseLL::print() const
{
	Node* curr = first;
	std::cout << rwInfo << std::endl;
	while (curr) {
		std::cout << curr->row << std::endl;
		curr = curr->next;
	}
}

int DataBaseLL::getIndexed()
{
	return indexedAt;
}

int DataBaseLL::indexedAtF(std::string data) {
	int i = 0;
	int res = 0;
	std::string tester = "";
	while (data[i] != '\0') {
		if (data[i] == ' ') {
			tester = "";
			res++;
		}
		else {
			tester += data[i];
			if (tester.compare("Indexed") == 0)
				return res;
		}
		i++;
	}
	return 0;
}

std::string DataBaseLL::getWord(int index, int wordNumber)
{
	int i = 0;
	std::string row = at(index);
	while (row[i] != '\0' && wordNumber > 0) {
		if (row[i] == ' ')
			wordNumber--;
		i++;
	}
	std::string res = "";
	while (row[i] != ' ' && row[i] != '\0') {
		if (row[i] != ',') {
			res += row[i];
		}
		i++;
	}
	return res;
}
