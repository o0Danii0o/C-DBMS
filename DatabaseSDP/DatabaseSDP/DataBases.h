#pragma once
#include "DataBaseHashList.h"

class DataBase {
	struct Base {
		HashListBase* entireInfo=nullptr;
		std::string tableName="";
		int rowCount = 0;
		long long sizeOfFile = 0;
	};

	std::vector<Base> tables;
	std::string getNameFromStringWhenCreating(std::string data);
	void InsertInTable(std::string name, std::string data);
	void SelectFromTable(std::string name, std::string data);
	void RemoveFromTable(std::string name, std::string data);
	void RemoveFromTableAll(std::string name);
	void CreateTable(std::string info);
	void DropTable(std::string name);
	void ListTables();
	void TableInfo(std::string name);
public:
	// need to add constructors, destructors and all
	void DetermineFunction(std::string data);
	DataBase();
	DataBase(const DataBase &rhs);
	DataBase& operator=(const DataBase& rhs);
	~DataBase();


};