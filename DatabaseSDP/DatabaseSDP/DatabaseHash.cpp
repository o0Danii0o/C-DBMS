#include"DatabaseHash.h"

void DatabaseHash::copy(const DatabaseHash& other)
{
	name = other.name;
	tableInfo = other.tableInfo;
	size = other.size;
	indexdAt = other.indexdAt;
	columnNo = other.columnNo;
	usedIndexes = other.usedIndexes;
	Rows* curr;
	Rows* toInsert;
	Rows* currThis;
	for (int i = 0; i < other.size;i++) {
		items[i] = new Rows();
		items[i]->key = other.items[i]->key;
		items[i]->value = other.items[i]->key;
		curr = other.items[i]->next;
		currThis = items[i];
		if (curr) {
			while (curr) {
				toInsert = new Rows();
				toInsert->key = curr->key;
				toInsert->value = curr->value;
				currThis->next = toInsert;
			}
			curr = curr->next;
			currThis = currThis->next;
		}else
			items[i]->next = nullptr;

	}
}

void DatabaseHash::clean()
{
	Rows* toDelete;
	Rows* curr;
	for (int i = 0; i < size;i++) {
		curr = items[i];
		while (curr) {
			toDelete = curr;
			curr = curr->next;
			delete toDelete;
		}
		//items[i] = nullptr;
	}
	delete[] items;
	items = nullptr;
	indexdAt = 0;
	name = "";
	usedIndexes.clear();
	tableInfo = "";
	columnNo = 0;
}

DatabaseHash::DatabaseHash()
{
	int size = 100;
	items = nullptr;
	name = "";
	tableInfo = "";
	indexdAt = 0;
	columnNo = 0;


}

DatabaseHash::DatabaseHash(std::string nm, std::string tblInfo, int size)
{
	std::string tst = "";
	int wordCount = 0;
	for (int i = 0; tblInfo[i];i++) {
		if (tst.compare("Indexed") == 0) {
			indexdAt = wordCount;
		}
		if (tblInfo[i] == ' ') {
			tst = "";
			wordCount++;
		}
		else 
			tst += tblInfo[i];
	}
	tst = "";
	items = new Rows*[size];
	
	columnNo = wordCount;
	for (int i = 0; i < size;i++) {
		items[i] = new Rows();
		items[i]->key = "";
		items[i]->value = "";
		items[i]->next = nullptr;
	}
	this->size = size;
	name = nm;
	tableInfo = tblInfo;
}

DatabaseHash::DatabaseHash(const DatabaseHash& other)
{
	copy(other);
}

DatabaseHash& DatabaseHash::operator=(const DatabaseHash& rhs)
{
	if (this != &rhs) {
		clean();
		copy(rhs);
	}
	return *this;
}

DatabaseHash::~DatabaseHash()
{
	clean();
}

unsigned long DatabaseHash::hashFunc(std::string key)
{
	unsigned long indx = 0;
	for (int i = 0;key[i];i++) {
		indx += key[i];
	}
	return indx % size;
}

void DatabaseHash::insertItem(std::string row)
{
	std::string indxCol = "";
	int indx = indexdAt;
	int i = 0;
	while (row[i] && indx > 0) {
		if (row[i] == ' ') // must be changed
			indx--;
		i++;
	}
	while (row[i] && row[i] != ' ' &&row[i]!=',') {
		indxCol += row[i++];
	}
	unsigned long index = hashFunc(indxCol);
	// checks if the index exists if not push_back
	if (std::find(usedIndexes.begin(), usedIndexes.end(), index) == usedIndexes.end() || usedIndexes.empty()) {
		usedIndexes.push_back(index);
	}
	Rows* newRow = new Rows();
	Rows* curr = items[index];
	newRow->key = indxCol;
	newRow->value = row;
	newRow->next = nullptr;
	if (items[index]->next == nullptr)
		items[index]->next = newRow;
	else {
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = newRow;
	}
}

void DatabaseHash::deleteItem(std::string row)
{
	std::string indxCol = "";
	int indx = indexdAt;
	int i = 0;
	while (row[i] && indx > 0) {
		if (row[i] == ' ') // must be changed
			indx--;
		i++;
	}
	while (row[i] && row[i] != ' '&&row[i]!=',') {
		indxCol += row[i++];
	}
	unsigned long index = hashFunc(indxCol);
	Rows* curr = items[index];
	Rows* prev = items[index];
	if (!items[index]->next->next) {
		usedIndexes.erase(find(usedIndexes.begin(), usedIndexes.end(), index));
	}
	while (curr) {
		if (curr->value.compare(row) == 0) {
			prev->next = curr->next;
			curr->next = nullptr;
			delete curr;
			break;
		}
		prev = curr;
		curr = curr->next;
	}
}

void DatabaseHash::findByKey(std::string key)
{
	unsigned int index = hashFunc(key);
	Rows* curr = items[index];
	std::cout << tableInfo << std::endl;
	while (curr) {
		if (curr->key.compare(key) == 0) {
			std::cout << curr->value << std::endl;
		}
		curr = curr->next;
	}
}

void DatabaseHash::findByNonKeyValue(std::string nkVal)
{
	Rows* it;
	for (int i = 0;i < usedIndexes.size();i++) {
		it = items[usedIndexes[i]]->next;
		while (it) {
			if (findIfSubst(it->value,nkVal))
				std::cout << "Row matching: " << it->value << std::endl;
			it = it->next;
		}
	}
}

std::string DatabaseHash::getColData(std::string data, int index)
{
	std::string res = "";
	int i;
	for (i = 0;data[i] && index>0;i++) {
		if (data[i] == ' ')
			index--;
	}
	
	for (;data[i] &&  data[i] != ' ';i++) {
		if(data[i]!=',')
			res += data[i];
	}
	return res;
}

void DatabaseHash::findByNonKeyValueWithOperationList(std::vector<std::string> values, std::vector<std::string> ops, std::vector<int> colNumbs)
{
	// We are comparing the key requirement based on the ops and following the logic to check the rest of the operations.
	Rows* it;
	bool printable = true;
	for (int i = 0;i < usedIndexes.size();i++) {
		it = items[usedIndexes[i]]->next;
		while (it) {
			for (int j = 0;j < ops.size();j++) {
				if (ops[j].compare("=") == 0) {
					if (asciiValue(getColData(it->value, colNumbs[j])) != asciiValue(values[j])) {
						printable = false;
						break;
					}
				}
				else if (ops[j].compare(">") == 0) {
					if (asciiValue(getColData(it->value, colNumbs[j])) <= asciiValue(values[j])){
						printable = false;
						break;
					}
				}
				else if (ops[j].compare("<") == 0) {
					if (asciiValue(getColData(it->value, colNumbs[j])) >= asciiValue(values[j])) {
						printable = false;
						break;
					}
				}
				else if (ops[j].compare(">=") == 0) {
					if (asciiValue(getColData(it->value, colNumbs[j])) < asciiValue(values[j])) {
						printable = false;
						break;
					}
				}
				else if (ops[j].compare("<=") == 0) {
					if (asciiValue(getColData(it->value, colNumbs[j])) > asciiValue(values[j])) {
						printable = false;
						break;
					}
				}
				else if (ops[j].compare("!=") == 0) {
					if (asciiValue(getColData(it->value, colNumbs[j])) == asciiValue(values[j])) {
						printable = false;
						break;
					}
				}
			}
			if (printable)
				std::cout <<"Row matched: "<< it->value << std::endl;
			it = it->next;
			printable = true;
		}
	}
}

void DatabaseHash::findByKeyValueWithOperationList(std::vector<std::string> values, std::vector<std::string> ops, std::vector<int> colNumbs)
{
	unsigned long keyHash = hashFunc(values[0]);
	bool printable = true;
	if (ops[0].compare("=")==0) {
		Rows* curr = items[keyHash]->next;
		while (curr) {
			for (int i = 1;i < ops.size();i++) {
				if (ops[i].compare("<=") == 0) {
					if (asciiValue(getColData(curr->value, colNumbs[i])) > asciiValue(values[i])) {
						printable = false;
						break;
					}
				}
				else if (ops[i].compare(">=") == 0) {
					if (asciiValue(getColData(curr->value, colNumbs[i])) < asciiValue(values[i])) {
						printable = false;
						break;
					}
				}
				else if (ops[i].compare("=") == 0) {
					if (asciiValue(getColData(curr->value, colNumbs[i])) != asciiValue(values[i])) {
						printable = false;
						break;
					}
				}
				else if (ops[i].compare("<") == 0) {
					if (asciiValue(getColData(curr->value, colNumbs[i])) >= asciiValue(values[i])) {
						printable = false;
						break;
					}
				}
				else if (ops[i].compare(">") == 0) {
					if (asciiValue(getColData(curr->value, colNumbs[i])) <= asciiValue(values[i])) {
						printable = false;
						break;
					}
				}
				else if (ops[i].compare("!=") == 0) {
					if (asciiValue(getColData(curr->value, colNumbs[i])) == asciiValue(values[i])) {
						printable = false;
						break;
					}
				}
			}
			if (printable)
				std::cout << "Row found: " << curr->value << std::endl;
			curr = curr->next;
			printable = true;
		}
	}else if (ops[0].compare(">")==0) {
		for (int i = 1;i < usedIndexes.size();i++) {
			if (usedIndexes[i] > keyHash || asciiValue(values[0]) < asciiValue(items[usedIndexes[i]]->next->value)) {
				Rows* curr = items[usedIndexes[i]]->next;
				while (curr) {
					for (int i = 1;i < ops.size();i++) {
						if (ops[i].compare("<=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) > asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) < asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) != asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("<") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) >= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) <= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("!=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) == asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
					}
					if (printable)
						std::cout << "Row found: " << curr->value << std::endl;
					curr = curr->next;
					printable = true;
				}
			}
		}
	}else if (ops[0].compare("<")==0) {
		for (int i = 1;i < usedIndexes.size();i++) {
			if (usedIndexes[i] < keyHash) {
				Rows* curr = items[usedIndexes[i]]->next;
				while (curr) {
					for (int i = 1;i < ops.size();i++) {
						if (ops[i].compare("<=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) > asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) < asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) != asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("<") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) >= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) <= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("!=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) == asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
					}
					if (printable)
						std::cout << "Row found: " << curr->value << std::endl;
					curr = curr->next;
					printable = true;
				}
			}
		}
	}if (ops[0].compare("<=")==0) {
		for (int i = 1;i < usedIndexes.size();i++) {
			if (usedIndexes[i] <= keyHash) {
				Rows* curr = items[usedIndexes[i]]->next;
				while (curr) {
					for (int i = 1;i < ops.size();i++) {
						if (ops[i].compare("<=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) > asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) < asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) != asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("<") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) >= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) <= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("!=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) == asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
					}
					if (printable)
						std::cout << "Row found: " << curr->value << std::endl;
					curr = curr->next;
					printable = true;
				}
			}
		}
	}if (ops[0].compare(">=")==0) {
		for (int i = 1;i < usedIndexes.size();i++) {
			if (usedIndexes[i] >= keyHash) {
				Rows* curr = items[usedIndexes[i]]->next;
				while (curr) {
					for (int i = 1;i < ops.size();i++) {
						if (ops[i].compare("<=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) > asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) < asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) != asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("<") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) >= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) <= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("!=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) == asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
					}
					if (printable)
						std::cout << "Row found: " << curr->value << std::endl;
					curr = curr->next;
					printable = true;
				}
			}
		}
	}if (ops[0].compare("!=")==0) {
		for (int i = 1;i < usedIndexes.size();i++) {
			if (usedIndexes[i] != keyHash) {
				Rows* curr = items[usedIndexes[i]]->next;
				while (curr) {
					for (int i = 1;i < ops.size();i++) {
						if (ops[i].compare("<=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) > asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) < asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) != asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("<") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) >= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare(">") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) <= asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
						else if (ops[i].compare("!=") == 0) {
							if (asciiValue(getColData(curr->value, colNumbs[i])) == asciiValue(values[i])) {
								printable = false;
								break;
							}
						}
					}
					if (printable)
						std::cout << "Row found: " << curr->value << std::endl;
					curr = curr->next;
					printable = true;
				}
			}
		}
	}
}
void DatabaseHash::findByNonKeyValueWithOperation(std::string nkVal, std::string op, int colNumb)
{
	if (op.compare("=") == 0) {
		findByNonKeyValue(nkVal);
	}
	else if(op.compare("<=") == 0) {
		Rows* it;
		for (int i = 0;i < usedIndexes.size();i++) {
			it = items[usedIndexes[i]]->next;
			while (it) { // the idea is to compare the colData with the given data, to check if its greater/ smaller etc
				if (getColData(it->value,colNumb).compare(nkVal) == 0 || getColData(it->value, colNumb).compare(nkVal)== -1)
					std::cout << "Row matching: " << it->value << std::endl;
				it = it->next;
			}
		}
	}
	else if (op.compare(">=") == 0) {
		Rows* it;
		for (int i = 0;i < usedIndexes.size();i++) {
			it = items[usedIndexes[i]]->next;
			while (it) {
				if (getColData(it->value, colNumb).compare(nkVal) == 0 || getColData(it->value, colNumb).compare(nkVal) == 1)
					std::cout << "Row matching: " << it->value << std::endl;
				it = it->next;
			}
		}
	}
	else if (op.compare("<") == 0) {
		Rows* it;
		for (int i = 0;i < usedIndexes.size();i++) {
			it = items[usedIndexes[i]]->next;
			while (it) {
				if (getColData(it->value, colNumb).compare(nkVal) == -1)
					std::cout << "Row matching: " << it->value << std::endl;
				it = it->next;
			}
		}
	}
	else if (op.compare(">") == 0) {
		Rows* it;
		for (int i = 0;i < usedIndexes.size();i++) {
			it = items[usedIndexes[i]]->next;
			while (it) {
				if (getColData(it->value, colNumb).compare(nkVal) == 1)
					std::cout << "Row matching: " << it->value << std::endl;
				it = it->next;
			}
		}
	}
	else if (op.compare("!=") == 0) {
		Rows* it;
		for (int i = 0;i < usedIndexes.size();i++) {
			it = items[usedIndexes[i]]->next;
			while (it) {
				if (getColData(it->value, colNumb).compare(nkVal) == 1 || getColData(it->value, colNumb).compare(nkVal) == -1)
					std::cout << "Row matching: " << it->value << std::endl;
				it = it->next;
			}
		}
	}
}

bool DatabaseHash::findIfSubst(std::string main, std::string sub)
{
	std::string curr = "";
	for (int i = 0;main[i];i++) {
		if (main[i] == ' ')
			curr = "";
		else if (main[i] != ',')
			curr += main[i];
		if (curr.compare(sub) == 0 && (main[i + 1] == '\0' || main[i + 1] == ' '))
			return true;

		
	}
	return false;
}

unsigned long DatabaseHash::asciiValue(std::string str)
{
	unsigned long sum = 0;
	for (int i = 0; str[i];i++) {
		sum += str[i];
	}
	return sum;
}

int DatabaseHash::getColumnByString(std::string data)
{
	int i = 0;
	std::string toCompare = "";
	for (int j = 0; tableInfo[j];j++) {
		if (tableInfo[j] == ';') {
			i++;
			toCompare = "";
			continue;
		}
		if (toCompare.compare(data) == 0) {
			return i;
		}
		if(tableInfo[j]!=' ')
			toCompare += tableInfo[j];
	}
}



void DatabaseHash::findAll(std::string val)
{
	if (val.compare(items[usedIndexes[0]]->next->key) == 0)
		findByKey(val);
	else
		findByNonKeyValue(val);
	
}

void DatabaseHash::findAllWithOperations(std::string selectRow)
{
	std::vector < std::string> values;
	std::vector<std::string> whichRowsToBeShown;
	int whereToBeAdded = -1;
	std::vector < std::string> operations;
	std::vector < std::string > extraRequirementsOperations;
	std::string name = "";
	std::vector<int> colNumbs;
	std::vector<std::string>colName;
	std::string orderedBy;
	bool SELECT = false, FROM = false, WHERE = false, ORDERBY = false, DISTINCT = false;
	bool ALL = false;
	int i = 0;
	std::string tempWord = "";
	while (selectRow[i] != '\0') {
		tempWord += selectRow[i];
		if (selectRow[i] == ' ') {
			if (WHERE) {
				whereToBeAdded++;
			}
			tempWord = "";
			i++;
			continue;
		}
		if (tempWord.compare("Select") == 0) {
			SELECT = true;
			i++;
			continue;
		}
		if (tempWord.compare("FROM") == 0) {
			FROM = true;
			SELECT = false;
			i++;
			continue;
		}
		if (tempWord.compare("WHERE") == 0) {
			WHERE = true;
			FROM = SELECT = false;
			i++;
			continue;
		}
		if (tempWord.compare("ORDER") == 0) {
			WHERE = false;
			ORDERBY = true;
			i++;
			continue;
		}
		if (ORDERBY) {
			if (tempWord.compare("BY") == 0) {
				i++;
				continue;
			}
			else {
				if (selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ') {
					i++;
					orderedBy = tempWord;
					continue;
				}
			}
		}
		if (SELECT) {
			if (tempWord.compare("*")==0) {
				ALL = true;
				SELECT = false;
				i++;
				continue;
			}
			if (selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ') {
				if (tempWord.compare("DISTINCT")) {
					DISTINCT = true;
					i++;
					continue;
				}
				whichRowsToBeShown.push_back(tempWord);
				i++;
				continue;
			}
		}
		if (FROM) {
			if (selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ') {
				name = tempWord;
				i++;
				continue;
			}
		}
		if (WHERE) {
			if (whereToBeAdded % 4 == 0 && (selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ')) {
				colNumbs.push_back(getColumnByString(tempWord));
				colName.push_back(tempWord);
			}
			else if (whereToBeAdded % 4 == 1 &&(selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ')) {
				operations.push_back(tempWord);
			}
			else if (whereToBeAdded % 4 == 2 && (selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ')) {
				values.push_back(tempWord);

			}
			else if (whereToBeAdded % 4 == 3 && (selectRow[i + 1] == '\0' || selectRow[i + 1] == ' ')) {
				extraRequirementsOperations.push_back(tempWord);
			}
		}
		i++;
		
	}
	for (int i = 0;i < colNumbs.size();i++) {
		std::cout << "ColNumb" << i << ": " << colNumbs[i] << std::endl;
	}
	for (int i = 0;i < colName.size();i++) {
		std::cout << "colName" << i << ": " << colName[i] << std::endl;
	}
	for (int i = 0;i < operations.size();i++) {
		std::cout << "Operation" << i << ": " << operations[i] << std::endl;
	}
	for (int i = 0;i < values.size();i++) {
		std::cout << "Value" << i << ": " << values[i] << std::endl;
	}
	for (int i = 0;i < extraRequirementsOperations.size();i++) {
		std::cout << "SpecialOperation" << i << ": " << extraRequirementsOperations[i] << std::endl;
	}
	std::cout << std::endl;
	std::cout << "DISTINCT FLAG : " << DISTINCT << std::endl;
	if(ORDERBY)
		std::cout << "ORDERED BY: "<< orderedBy << std::endl;
}





void DatabaseHash::showUsed()
{
	std::cout << "Number of columns " << columnNo << std::endl;
	for (std::vector<int>::iterator it = usedIndexes.begin(); it != usedIndexes.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


