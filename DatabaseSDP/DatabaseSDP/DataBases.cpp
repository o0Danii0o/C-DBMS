#include "DataBases.h"



std::string DataBase::getNameFromStringWhenCreating(std::string data)
{
	bool secondWord = false;
	std::string tempWord = "";
	for (int i = 0;i < data.size();i++) {
		
		if (secondWord && (data[i] == ' ' || data[i+1] == '\0')) {
			if (data[i + 1] == '\0')
				tempWord += data[i];
			return tempWord;
		}
		else if (secondWord) {
			tempWord += data[i];
		}else if (data[i] == ' ') {
			secondWord = true;
		}
	}
}

void DataBase::DetermineFunction(std::string data)
{
	std::string tempWord = "";
	int typeOfFunction = -1;
	int i = 0;
	// 0 is for select/ 1 is for insert / 2 is for remove //3 for DropTable / 4 for TableInfo // 5 for CreateTable//  6 will be ListTables // createTable 7 if its empty // -1 if there is an error
	for (; i < data.size();i++) {
		if (data[i] == ' ') {
			if (tempWord.compare("Select") == 0)
				typeOfFunction = 0;
			else if (tempWord.compare("Insert") == 0)
				typeOfFunction = 1;
			else if (tempWord.compare("Delete") == 0)
				typeOfFunction = 2;
			else if (tempWord.compare("DropTable") == 0)
				typeOfFunction = 3;
			else if (tempWord.compare("TableInfo") == 0)
				typeOfFunction = 4;
			else if (tempWord.compare("CreateTable") == 0)
				typeOfFunction = 5;
			tempWord = "";
			i++;
			break;
			//we jump over the interval
		}
		else
			tempWord += data[i];
	}
	if (tempWord.compare("ListTables") == 0)
		typeOfFunction = 6;
	bool fromIntoIndicator = false;
	switch (typeOfFunction) {
	case 0:
		for (;i < data.size();i++) {
			 if (tempWord.compare("FROM") == 0) {
				 fromIntoIndicator = true;
				tempWord = "";
				continue;
				// we are jumping over the interval.
			}
			 if (data[i] != ' ') {
				 tempWord += data[i];
				 if (data[i + 1] != '\0')
					 continue;
			 }
			 if (fromIntoIndicator && (data[i] == ' ' || data[i+1] == '\0')) {
				 std::string tempNextWord = "";
				 if (data[i + 1] != '\0') {
					 i++;
					 while (data[i] != '\0') {
						 if (data[i] != ' ') {
							 tempNextWord += data[i];
						 }
						 else
							 break;
						 i++;
					 }
					 if (tempNextWord.compare("ORDER") != 0 && tempNextWord.compare("WHERE") != 0) {
						 std::cout << "Invalid use of SELECT clause" << std::endl;
						 return;
					 }
				 }
				 for (int j = 0;j < tables.size();j++) {
					 if (tables[j].tableName.compare(tempWord) != 0 && tables[j].entireInfo->getRowCount()!=0) {
						 RemoveFromTableAll(tables[j].tableName);
						 // we are for sure knowing that there is file because we have made one by deleting the data of the table
						 std::ifstream currFile(tables[j].tableName+ ".csv", std::ios::binary);
						 currFile.seekg(0, std::ios::end);
						 tables[j].sizeOfFile = currFile.tellg();
						 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// check here if sieoffilelogic fails
					 }
				 }
				 // we are simply using the above code to delete all the information we do have in the RAM for all the tables that are not currently used!
				 
				 SelectFromTable(tempWord, data);
				 break;
			 }
			 else if (data[i] == ' ') {
				 tempWord = "";
			 }
		}
		break;
	case 1:
		for (;i < data.size();i++) {
			if (tempWord.compare("INTO") == 0) {
				fromIntoIndicator = true;
				tempWord = "";
				continue;
				// we are jumping over the interval.
			}
			if (data[i] != ' ')
				tempWord += data[i];
			else if (fromIntoIndicator && data[i] == ' ') {
				for (int j = 0;j < tables.size();j++) {
					if (tables[j].tableName.compare(tempWord) != 0 && tables[j].entireInfo->getRowCount() != 0) {
						RemoveFromTableAll(tables[j].tableName);
						// we are for sure knowing that there is file because we have made one by deleting the data of the table
						std::ifstream currFile(tables[j].tableName+ ".csv", std::ios::binary);
						currFile.seekg(0, std::ios::end);
						tables[j].sizeOfFile = currFile.tellg();
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// check here if sieoffilelogic fails
					}
				}
				// we are simply using the above code to delete all the information we do have in the RAM for all the tables that are not currently used!
				InsertInTable(tempWord, data);
				break;
			}
			else if (data[i] == ' ') {
				tempWord = "";
			}
		}
		break;
	case 2:
		for (;i < data.size();i++) {
			if (tempWord.compare("FROM") == 0) {
				fromIntoIndicator = true;
				tempWord = "";
				continue;
				// we are jumping over the interval.
			}
			if (data[i] != ' ') {
				tempWord += data[i];
				if (data[i + 1] != '\0')
					continue;
			}
			if (fromIntoIndicator && (data[i] == ' ' || data[i + 1] == '\0')) {
				if (data[i + 1] == '\0') {
					RemoveFromTableAll(tempWord);

					// we are for sure knowing that there is file because we have made one by deleting the data of the table
					std::ifstream currFile(tempWord+".csv", std::ios::binary);
					currFile.seekg(0, std::ios::end);
					for (int k = 0; k < tables.size();k++) {
						if (tables[k].tableName.compare(tempWord) == 0) {
							tables[k].sizeOfFile = currFile.tellg();
							break;
						}
					}
					//tables[j].sizeOfFile = currFile.tellg();
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// check here if sieoffilelogic fails
				}
				else {
					for (int j = 0;j < tables.size();j++) {
						if (tables[j].tableName.compare(tempWord) != 0 && tables[j].entireInfo->getRowCount() != 0) {
							RemoveFromTableAll(tables[j].tableName);

							// we are for sure knowing that there is file because we have made one by deleting the data of the table
							std::ifstream currFile(tables[j].tableName+".csv", std::ios::binary);
							currFile.seekg(0, std::ios::end);
							tables[j].sizeOfFile = currFile.tellg();
							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// check here if sieoffilelogic fails
						}
					}
					// we are simply using the above code to delete all the information we do have in the RAM for all the tables that are not currently used!
					RemoveFromTable(tempWord, data);
				}
				break;
			}
			else if (data[i] == ' ') {
				tempWord = "";
			}
		}
		break;
	case 3:
		for (;i < data.size();i++) {
			if (data[i] != ' ')
				tempWord += data[i];
		}
		DropTable(tempWord);
		break;
	case 4:
		for (;i < data.size();i++) {
			if (data[i] != ' ')
				tempWord += data[i];
		}
		for (int j = 0;j < tables.size();j++) {
			if (tables[j].tableName.compare(tempWord) != 0 && tables[j].entireInfo->getRowCount() != 0) {
				RemoveFromTableAll(tables[j].tableName);

				// we are for sure knowing that there is file because we have made one by deleting the data of the table
				std::ifstream currFile(tables[j].tableName + ".csv", std::ios::binary);
				currFile.seekg(0, std::ios::end);
				tables[j].sizeOfFile = currFile.tellg();
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// check here if sieoffilelogic fails
			}
		}
		// we are simply using the above code to delete all the information we do have in the RAM for all the tables that are not currently used!
		TableInfo(tempWord);
		break;
	case 5:
		CreateTable(data);
		break;
	case 6:
		ListTables();
		break;
	default:
		std::cout << "Unknown command!" << std::endl;
		break;
	}
}

void DataBase::CreateTable(std::string info)
{
	Base newTable;
	for (int i = 0;i < tables.size();i++) {
		if (tables[i].tableName.compare(getNameFromStringWhenCreating(info)) == 0) {
			std::cout << "You are trying to create a table with a name that already exists!" << std::endl;
			return;
		}
	}
	newTable.entireInfo = new HashListBase(info);
	newTable.tableName = newTable.entireInfo->getTableName();
	tables.push_back(newTable);
	std::cout << "Table " << newTable.tableName << " created!" << std::endl;
}

void DataBase::DropTable(std::string name)
{
	for (int i = 0;i < tables.size();i++) {
		if (name.compare(tables[i].tableName) == 0) {
			delete tables[i].entireInfo;
			tables[i].tableName = "";
			tables[i].rowCount = 0;
			tables.erase(tables.begin()+i);
			std::cout << "Table " << name << " deleted successfully" << std::endl;
			return;
		}
	}
	std::cout << "Table " << name << " not found!" << std::endl;
}

void DataBase::ListTables()
{
	std::cout << "There are " << tables.size() << " tables in the database:"<<std::endl;
	for (int i = 0;i < tables.size();i++) {
		std::cout << tables[i].tableName << std::endl;
	}
}




void DataBase::TableInfo(std::string name)
{
	bool foundName = false;
	for (int i = 0;i < tables.size();i++) {
		if (name.compare(tables[i].tableName) == 0) {
			std::cout << tables[i].entireInfo->getTableInfo() << std::endl;
			//std::cout << "Total " << tables[i].entireInfo->getRowCount() << " rows in the table" << std::endl;
			std::cout << "Total " << tables[i].rowCount << " rows ("<<tables[i].sizeOfFile<<" bytes data)" << " in the table" << std::endl;
			foundName = true;
		}
	}
	if (!foundName)
		std::cout << "There is no such table!" << std::endl;

}

void DataBase::InsertInTable(std::string name, std::string data)
{
	bool foundName = false;
	for (int i = 0;i < tables.size();i++) {
		if (name.compare(tables[i].tableName) == 0) {
			if (tables[i].entireInfo->getRowCount() == 0) {
				try {
					tables[i].entireInfo->loadFromFile();
				}
				catch (std::invalid_argument) {
					std::cout << "The file contains corrupted rows, unable to be added!" << std::endl;
					return;
				}
			}
			tables[i].entireInfo->insertFunction(data);
			// newly added test
			tables[i].rowCount = tables[i].entireInfo->getRowCount();
			foundName = true;
			break;
		}
	}
	if (!foundName)
		std::cout << "There is no such table!" << std::endl;
}

void DataBase::SelectFromTable(std::string name, std::string data)
{
	bool foundName = false;
	for (int i = 0;i < tables.size();i++) {
		if (name.compare(tables[i].tableName) == 0) {
			if (tables[i].entireInfo->getRowCount() == 0) {
				try {
					tables[i].entireInfo->loadFromFile();
				}
				catch (std::invalid_argument) {
					std::cout << "The file contains corrupted rows, unable to be added!" << std::endl;
					return;
				}
			}
			tables[i].entireInfo->selectFunction(data);
			foundName = true;
			break;
		}
	}
	if (!foundName)
		std::cout << "There is no such table!" << std::endl;
}

void DataBase::RemoveFromTable(std::string name, std::string data)
{
	bool foundName = false;
	for (int i = 0;i < tables.size();i++) {
		if (name.compare(tables[i].tableName) == 0) {
			if (tables[i].entireInfo->getRowCount() == 0) {
				try {
					tables[i].entireInfo->loadFromFile();
				}
				catch (std::invalid_argument) {
					std::cout << "The file contains corrupted rows, unable to be added!" << std::endl;
					return;
				}

			}
			tables[i].entireInfo->deleteFunction(data);
			// newly added below.
			tables[i].rowCount = tables[i].entireInfo->getRowCount();
			foundName = true;
			break;
		}
	}
	if (!foundName)
		std::cout << "There is no such table!" << std::endl;
}

void DataBase::RemoveFromTableAll(std::string name)
{
	for (int i = 0; i < tables.size();i++) {
		if (tables[i].tableName.compare(name) == 0) {
			//delete tables[i].entireInfo;
			tables[i].rowCount = tables[i].entireInfo->getRowCount();
			// newly added above

			tables[i].entireInfo->deleteFunctionAll();
			break;
		}
	}
}

DataBase::DataBase()
{

}

DataBase::DataBase(const DataBase& rhs)
{
	for (int i = 0;i < rhs.tables.size();i++) {
		Base newItem; 
		newItem.entireInfo = new HashListBase(*(rhs.tables[i].entireInfo));
		newItem.tableName = rhs.tables[i].tableName;

		//newly added below
		newItem.rowCount = rhs.tables[i].rowCount;
		newItem.sizeOfFile = rhs.tables[i].sizeOfFile;
		tables.push_back(newItem);
	}
}

DataBase& DataBase::operator=(const DataBase& rhs)
{
	if (this != &rhs) {

		//delete
		for (int i = 0;i < tables.size();i++) {
			delete tables[i].entireInfo;
			tables[i].tableName = "";
			tables[i].rowCount = 0; //new
			tables[i].sizeOfFile = 0;
			tables.erase(tables.begin() + i);
		}
		//copy
		for (int i = 0;i < rhs.tables.size();i++) {
			Base newItem;
			newItem.entireInfo = new HashListBase(*(rhs.tables[i].entireInfo));
			newItem.tableName = rhs.tables[i].tableName;
			newItem.rowCount = rhs.tables[i].rowCount; // new
			newItem.sizeOfFile = rhs.tables[i].sizeOfFile;
			tables.push_back(newItem);
		}
	}
	return *this;
}


DataBase::~DataBase()
{
	while(!tables.empty()) {
		delete tables[0].entireInfo;
		tables[0].tableName = "";
		tables[0].rowCount = 0;
		tables[0].sizeOfFile = 0;
		tables.erase(tables.begin());
	}
}
