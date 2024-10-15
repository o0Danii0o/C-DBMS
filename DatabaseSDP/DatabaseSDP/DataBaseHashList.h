#pragma once
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>


const int SIZE_FOR_INTERVALS = 25;
static int objects = 0;
class HashListBase {

    struct Row {

        std::string key;
        std::string data;
        Row* next;
        bool operator==(const Row& rhs);
        Row() :key(""), data(""), next(nullptr) {};
    };

private:

    std::string tableName;
    std::string tableInfo;
    int rowCount;
    int indexedAt;
    std::vector<Row> children;
    std::vector<std::string> types;

    void copy(const HashListBase& other);
    void clean();

    std::string getColumn(std::string data, int index);
    std::string getColumnFromTable(int index);
    int indexOfColumn(std::string data, std::string colName);
    int asciiVal(std::string data);
    void getAllStringInfo(std::string data, std::string& tblName, std::string &tblInfo, int &indxAt,std::vector<std::string>& tps);
    int compareData(std::string lhs, std::string rhs, std::string type);

    void addElement(std::string data);
    void addElements(std::vector<std::string> rows);
    void removeElement(std::string data);

    bool checkIfValidArg(std::string, std::string valueType, int type);
    bool ifConditionIsMet(std::vector<bool>& values, std::vector<std::string> operations, int& indxForOps, int& indxOfValues);
    void orderByPrint(std::string columnName, std::vector<int> columnIndexesToBeShown, bool allElements, std::vector<std::string>rowsToBeShown, bool typeOfSort);
public:
    const std::string getTableName() const;
    const std::string getTableInfo() const;
    const int getRowCount()const;
    HashListBase();
    HashListBase(std::string fullData);
    HashListBase(const HashListBase& other);
    HashListBase& operator=(const HashListBase& rhs);
    ~HashListBase();
    void deleteFunction(std::string deleteRow);
    void deleteFunctionAll();
    void print(std::vector<int> columnIndexesToBeShown, std::vector<std::string>rowsToBeShown);
    void insertFunction(std::string info);
    void loadFromFile();
    void selectFunction(std::string row);
};