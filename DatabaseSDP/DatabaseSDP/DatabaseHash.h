#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
class DatabaseHash {
	struct Rows {
		std::string key;
		std::string value;
		Rows* next;
	};
private:
	int size;
	Rows** items;
	std::string name;
	std::string tableInfo;
	int indexdAt;
	std::vector<int> usedIndexes;
	int columnNo;

	void copy(const DatabaseHash& other);
	void clean();
	void findByKey(std::string key);
	void findByNonKeyValue(std::string nkVal);
	//void findByNonKeyValueWithOperation(std::string nkVal,std::string op);
	bool findIfSubst(std::string main, std::string sub);
	unsigned long asciiValue(std::string str);
	//void findByNonKeyValueWithOperationList(std::vector<std::string> values, std::vector<std::string> ops, std::vector<int> colNumbs);
	//void findByKeyValueWithOperationList(std::vector<std::string> values, std::vector<std::string>ops, std::vector<int> colNumbs);
	int getColumnByString(std::string data);

public:
	DatabaseHash();
	DatabaseHash(std::string nm, std::string tblInfo, int size = 100);
	DatabaseHash(const DatabaseHash& other);
	DatabaseHash& operator=(const DatabaseHash& rhs);
	~DatabaseHash ();

	unsigned long hashFunc(std::string key);
	void insertItem(std::string row);
	void deleteItem(std::string row);
	void findAll(std::string val);
	void findAllWithOperations(std::string selectRow); // this is a function that converts an input select requirement into vectors of data to be distributed for searchign!
	// needs to be added ORDER BY// DISTINCT 
	std::string getColData(std::string data, int index);
	void findByNonKeyValueWithOperation(std::string nkVal, std::string op, int colNumb);
	void findByKeyValueWithOperationList(std::vector<std::string> values, std::vector<std::string>ops, std::vector<int> colNumbs);
	void findByNonKeyValueWithOperationList(std::vector<std::string> values, std::vector<std::string> ops, std::vector<int> colNumbs);
	void showUsed();
};
