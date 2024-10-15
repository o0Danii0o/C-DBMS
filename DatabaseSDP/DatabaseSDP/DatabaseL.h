#pragma once
#include<iostream>
#include<string>

class DataBaseLL {
	struct Node {
		std::string row;
		Node* next;
		int appearance; 
	};
private:
	std::string name;
	std::string rwInfo;
	int indexedAt;
	Node* first;
	Node* last;
	void copy(const DataBaseLL& other);
	void clean();
public:
	//constructors
	DataBaseLL();
	DataBaseLL(std::string row, std::string tableInfo = "ID:Int; Name:String; Value:Int", std::string name = "Default");
	DataBaseLL(const DataBaseLL& other);
	DataBaseLL(DataBaseLL&& other);
	DataBaseLL& operator=(const DataBaseLL& other);
	DataBaseLL& operator=(DataBaseLL&& other);
	~DataBaseLL();

	//read elements in the list
	const std::string& front()const;
	const std::string& back() const;
	const std::string& at(int index) const;

	//add elements in the list
	void push_front(const std::string& val);
	void push_end(const std::string& val);
	void push_at(const std::string& val, int index);

	//remove elements at
	void pop_front();
	void pop_back();
	void pop_at(int index);

	const std::string& getName()const;
	const void print()const;
	int indexedAtF(std::string data);
	int getIndexed();
	std::string getWord(int index, int wordNumber);
};