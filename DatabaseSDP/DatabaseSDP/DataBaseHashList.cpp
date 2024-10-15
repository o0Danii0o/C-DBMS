#include"DataBaseHashList.h"
 
std::string returnOppositeOperation(std::string element) {
    if (element.compare("<") == 0)
        return ">=";
    if (element.compare("=") == 0)
        return "!=";
    if (element.compare("!=") == 0)
        return "=";
    if (element.compare("<=") == 0)
        return ">";
    if (element.compare(">") == 0)
        return "<=";
    if (element.compare(">=") == 0)
        return "<";
}
std::string returnOppositeSpecialOperation(std::string element) {
    if (element.compare("AND") == 0)
        return "OR";
    if (element.compare("OR") == 0)
        return "AND";
}
void printSpaces(int nmbr) {
    for (int i = 0;i < nmbr; i++)
         std::cout << " ";
}
bool ifInt(std::string data) {
    for (int i = 0; i < data.size();i++) {
        if (data[i] < 48 || data[i]>57)
            return false;
    }
    return true;
}

// we are going to test if columnName 0 / operation 1 / valu 2/ specOperations 3/  are valid inputs
bool HashListBase::checkIfValidArg(std::string data, std::string valueType, int type) {
    switch (type) {
    case 0:
        for (int i = 0;i < types.size();i++) {
            if (getColumnFromTable(i).compare(data) == 0)
                return true;
        }
        break;
    case 1:
        // if its different than the one below that means the data input is valid.
        if (data.compare("<=") == 0 || data.compare(">=") == 0 || data.compare("<") == 0 || data.compare(">") == 0 || data.compare("=") == 0 || data.compare("!=") == 0)
            return true;
        break;
    case 2:
        if (valueType.compare("Date") == 0) {
            // date must be only used with separator of dots in this logic.
            int counterOfDots = 0;
            std::string tempWord = "";
            for (int i = 0;i < data.size();i++) {
                if (data[i] == '.') {
                    // if any of the inbetween dots are not integers, it should return false;
                    if (!ifInt(tempWord))
                        return false;
                    if (counterOfDots == 0 && stoi(tempWord) > 31)
                        return false;
                    if (counterOfDots == 1 && stoi(tempWord) > 12)
                        return false;
                    tempWord = "";
                    counterOfDots++;
                }
                else
                    tempWord += data[i];
            }
            if (counterOfDots != 2)
                return false;
            return ifInt(tempWord);
        }
        else if (valueType.compare("Int") == 0) {
            return ifInt(data);
        }
        else return true;
        break;
    case 3:
        if (data.compare("AND") == 0 || data.compare("OR") == 0 || data.compare("(") == 0 || data.compare(")") == 0)
            return true;
        break;
    default:
        std::cout << "Invalid type entered!" << std::endl;
        break;
    }
    return false;
}

bool HashListBase::Row::operator==(const Row& rhs) {

    if (data == rhs.data && key == rhs.key) {
        return true;
    }
    return false;
}

void HashListBase::print(std::vector<int> columnIndexesToBeShown, std::vector<std::string>rowsToBeShown) {
    // this is formatted printing based on columns we want to show and rows we want to show.
    if (columnIndexesToBeShown.empty()) {
        for (int i = 0;i < types.size();i++) {
            if (i == types.size() - 1) {
                std::cout << getColumnFromTable(i) << std::endl << std::endl;
            }
            else {
                std::string toBePrinted = getColumnFromTable(i);
                std::cout << toBePrinted;
                printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
            }
        }
    }
    else {
        for (int i = 0;i < columnIndexesToBeShown.size();i++) {
            if (i == columnIndexesToBeShown.size() - 1) {
                std::cout << getColumnFromTable(columnIndexesToBeShown[i]) << std::endl << std::endl;
            }
            else {
                std::string toBePrinted = getColumnFromTable(columnIndexesToBeShown[i]);
                std::cout << toBePrinted;
                printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
            }
        }
    }

    if (columnIndexesToBeShown.empty()) {
        for (int itr = 0; itr < rowsToBeShown.size();itr++) {
            //std::cout << rowsToBeShown[itr] << std::endl;
            for (int itr2 = 0;itr2 < types.size();itr2++) {
                if (itr2 == types.size() - 1) {
                    std::cout << getColumn(rowsToBeShown[itr], itr2) << std::endl;
                }
                else {
                    std::string toBePrinted = getColumn(rowsToBeShown[itr], itr2);
                    std::cout << toBePrinted;
                    printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
                }
            }
        }
    }
    else {
        for (int itr = 0; itr < rowsToBeShown.size();itr++) {
            for (int itr2 = 0;itr2 < columnIndexesToBeShown.size();itr2++) {
                if (itr2 == columnIndexesToBeShown.size() - 1) {
                    std::cout << getColumn(rowsToBeShown[itr], columnIndexesToBeShown[itr2]) << std::endl;
                }
                else {
                    std::string toBePrinted = getColumn(rowsToBeShown[itr], columnIndexesToBeShown[itr2]);
                    std::cout << toBePrinted;
                    printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
                }
            }
        }
    }
    
   /* std::cout << "Table Info: " << tableInfo << std::endl;

   // for (int i = 0;i < types.size();i++) {
   //     std::cout << "Type " << i << ": " << types[i] << std::endl;
   // }
    int k = 0;
    for (int i = 0;i < children.size();i++) {
        Row* curr = &children[i];

        while (curr) {
            std::cout << curr->data << std::endl;
            curr = curr->next;
            k++;
        }
        k = 0;
    }
    */
    std::cout <<"Total " << rowsToBeShown.size() << " rows selected." << std::endl;
}

void HashListBase::insertFunction(std::string info)
{
    int i = 0; 
    bool insideScope = false;
    std::string tempWord = "";
    std::vector<std::string> rows;
    for (;info[i];i++) {
        if (info[i] == '(') 
            insideScope = true;
        if (insideScope)
            tempWord += info[i];
        if (info[i] == ')') {
            insideScope = false;
            rows.push_back(tempWord);
            tempWord = "";
        }
    }
   // rowCount += rows.size();
    if (rows.empty()) {
        std::cout << "You have tried to insert invalid arguments" << std::endl;
        return;
    }
    try {
        addElements(rows);
        std::cout << rows.size() << " rows inserted" << std::endl;
    }
    catch (std::invalid_argument) {
        rows.clear();
        std::cout << "You have tried to insert invalid arguments" << std::endl;
    }
    
}

void HashListBase::loadFromFile()
{
    std::fstream fileForLoad;
    fileForLoad.open(tableName + ".csv", std::ios::in);
    if (fileForLoad.is_open()) {
        std::string eachRow;
        std::string skipFirst;
        std::getline(fileForLoad, skipFirst);
        // new in order to try to get the types;
        if (types.empty()) {
            std::string tempWord = "";
            for (int i = 0;i < skipFirst.size();i++) {
                if (skipFirst[i] == ':') {
                    i++;
                    while (skipFirst[i] != ',' && skipFirst[i] != ';' && skipFirst[i + 1] != '\0') {
                        tempWord += skipFirst[i];
                        i++;
                    }
                    if (skipFirst[i + 1] == '\0') {
                        tempWord += skipFirst[i];
                    }
                    types.push_back(tempWord);
                    tempWord = "";
                }
            }
        }
        //test 
        while (std::getline(fileForLoad, eachRow)) {
            addElement("("+eachRow+")"); /// doing this simply so the results to be in format (X, X, X) 
        }
        fileForLoad.close();
    }
    
}

std::string HashListBase::getColumn(std::string data, int index) {

    int i = 0;
    std::string res = "";

    for (; data[i] && index > 0;i++) {
        if (data[i] == ',') {
            index--;
        }
    }
    //i++; newly added
    bool insideString = false;
    while (data[i] != ',' && data[i] != '\0') {
        if (data[i] == '"')
            insideString = true;
        if (data[i] != ',' && data[i]!='('&&data[i]!=')') {
            if(insideString && data[i]==' ')
                res += data[i];
            else if(data[i] != ' ')
                res += data[i];
        }
        i++;
    }
    return res;
}

std::string HashListBase::getColumnFromTable(int index)
{
    int i = 0;
    std::string res = "";

    for (; tableInfo[i] && index > 0;i++) {
        if (tableInfo[i] == ';') {
            index--;
        }      
    }
    for (; tableInfo[i];i++) {
        if ((tableInfo[i] >= 65 && tableInfo[i] <= 90) || (tableInfo[i] >= 97 && tableInfo[i] <= 122)) {
            res += tableInfo[i];
        }
        if (tableInfo[i] == ':') {
            return res;
        }
    }
}

void HashListBase::getAllStringInfo(std::string data, std::string& tblName, std::string &tblInfo, int &indxAt, std::vector<std::string> &tps)
{
    int i = 0;
    std::vector<std::string> columns;
    bool insideScopes = false;
    bool afterScopes = false;
    int flag = 0;
    std::string tempWord = "";
    std::string tableInfo = "";
    std::string tableName = "";
    for (;data[i];i++) {
        if (afterScopes) {
            if (tempWord.compare(" Index ON ") == 0) {
                tempWord = "";
            }
            tempWord += data[i];
        }
        else {
            if (flag == 1 && data[i]!=' ') {
                tableName += data[i];
            }
            if (data[i] == '(')
                insideScopes = true;
            if (data[i] == ')') {
                insideScopes = false;
                afterScopes = true;
                tableInfo += data[i];
                types.push_back(tempWord);
                tempWord = "";
            }
            if (data[i] == ' ') {
                tempWord = "";
                flag++;
            }
            if (data[i] != ',' && data[i] != ':' && data[i] != '(' && data[i] != ')' && data[i] != ' ')
                tempWord += data[i];
            if (insideScopes && data[i + 1] == ':') {
                columns.push_back(tempWord);
                tempWord = ""; // new add
            }
            if (insideScopes && data[i + 1] == ',') {
                types.push_back(tempWord);
                tempWord = ""; // new add
            }
            if (insideScopes)
                tableInfo += data[i];
        }
    }
    tblName = tableName;
    for (int j = 0; j < columns.size();j++) {
        if (columns[j].compare(tempWord) == 0) {
            indxAt = j;
            break;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////// check
    bool toInsert = true;
    int whereToBeInserted = indxAt;
    for (int j = 0;tableInfo[j];j++) {
        if (tableInfo[j] == ',') {
            if (toInsert && whereToBeInserted==0) {
                tableInfo.insert(j, ", Indexed");
                toInsert = false;
            }
            else {
                tableInfo[j] = ';';
                whereToBeInserted--;
            }
        }
    }
    //tblInfo = tableInfo;
    if (tableInfo.compare("") == 0) {
        tblInfo = "(ID:Int, Indexed; Name:String; Date:Date)";
        indxAt = 0;
    }
    else 
        tblInfo = tableInfo; // new 
    if (types.empty()) {
        types.push_back("Int");
        types.push_back("String");
        types.push_back("Date");
    }
}

void HashListBase::copy(const HashListBase& other) {

    tableInfo = other.tableInfo;
    tableName = other.tableName;
    indexedAt = other.indexedAt;
    rowCount = other.rowCount;
    for (int i = 0;i < other.types.size();i++) {
        types.push_back(other.types[i]);
    }

    for (int i = 0;i < other.children.size();i++) {

        Row newChild;
        Row* creationNC = &newChild;
        newChild.key = other.children[i].key;
        newChild.data = other.children[i].data;
        Row* curr = other.children[i].next;

        while (curr) {

            Row* newChildListData = new Row();
            newChildListData->key = curr->key;
            newChildListData->data = curr->data;
            creationNC->next = newChildListData;
            creationNC = creationNC->next;
            curr = curr->next;
        }
        children.push_back(newChild);
    }
}

void HashListBase::clean() {

    std::ofstream editFile;
    editFile.open(tableName + ".csv", editFile.trunc);
    if (editFile.is_open()) {
        editFile << tableInfo.substr(1, tableInfo.size() - 2) << std::endl; // first row will be table info
        for (int i = 0;i < children.size();i++) {
            Row* curr = children[i].next;
            editFile << children[i].data.substr(1, children[i].data.size() - 2) << std::endl;
            while (curr) {
                editFile << curr->data.substr(1, curr->data.size() - 2) << std::endl; // we do it like this so it removes the ( and ) 
                curr = curr->next;
            }
        }
        editFile.close();
    }

    for (int i = 0;i < children.size();i++) {
        Row* toDelete = children[i].next;
        Row* curr = children[i].next;
        while (curr) {
            toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }

    }
    children.clear();
    types.clear();
    tableName = "";
    tableInfo = "";
    indexedAt = 0;
    rowCount = 0;
}

void HashListBase::addElement(std::string data) {

    // have to make a function to get the indexedAt;
    std::string testKey = getColumn(data, indexedAt);
    bool noElements = true;
    for (int i = 0;i < types.size();i++) {
        if (types[i].compare("Int") == 0) {
            if (!ifInt(getColumn(data, i)))
                throw std::invalid_argument("invalid");
        }
        else if (types[i].compare("Date") == 0) {
            std::string tempPart = "";
            std::string tempData = getColumn(data, i);
            int counterOfDots = 0;
            for (int j = 0; j < tempData.size();j++) {
                if (tempData[j] == '.') {
                    if (!ifInt(tempPart))
                        throw std::invalid_argument("invalid");
                    if (counterOfDots == 0 && stoi(tempPart) > 31)
                        throw std::invalid_argument("invalid");
                    if (counterOfDots == 1 && stoi(tempPart) > 12)
                        throw std::invalid_argument("Invalid");
                    tempPart = "";
                    counterOfDots++;
                }
                else {
                    tempPart += tempData[j];
                }
            }
            if (counterOfDots != 2)
                throw std::invalid_argument("Invalid");
            if (!ifInt(tempPart))
                throw std::invalid_argument("invalid");
        }
    }

    for (int i = 0;i < children.size() && noElements;i++) {
        if (testKey.compare(children[i].key) == 0) {
            Row* curr = &children[i];
            while (curr->next) {
                curr = curr->next;
            }

            Row* newChild2 = new Row();
            newChild2->key = testKey;
            newChild2->data = data;
            newChild2->next = nullptr;
            curr->next = newChild2;
            noElements = false;
        }
    }

    if (noElements) {
        Row newChild;
        newChild.key = testKey;
        newChild.data = data;
        newChild.next = nullptr;
        children.push_back(newChild);
        rowCount++;
        return;
    }
    rowCount++;
}

int HashListBase::indexOfColumn(std::string data, std::string colName)
{
    int i = 0;
    int res = 0;
    std::string tempWord = "";
    while (data[i] != '\0') {
        if (tempWord.compare(colName) == 0)
            return res;
        if (data[i] == ';') {
            res++;
            tempWord = "";
        }
        if (data[i] == ' ' || data[i] == ':') {
            tempWord = "";
        }
        else if(data[i]!=' '&&data[i]!= ',' && data[i]!='(' && data[i]!= ')' && data[i]!='\0' && data[i] !=':' && data[i]!=';')
            tempWord += data[i];
        i++;
    }
    return -1;
}



int HashListBase::asciiVal(std::string data)
{
    int i = 0;
    int res = 0;
    for (;data[i];i++) {
        res += data[i];
    }
    return res;
}

bool HashListBase::ifConditionIsMet(std::vector<bool>& values, std::vector<std::string> operations, int& indxForOps, int& indxOfValues)
{
    static int z = indxOfValues;
    static int i = indxForOps;
    if (values.empty()) {
        //std::cout << "Invalid use of WHERE clause, values of items to be added is empty!" << std::endl;
        throw std::invalid_argument("invalid where clause");
    }
    for (;i < operations.size();i++) {
        if (operations[i].compare("AND") == 0) {
            if (i != operations.size() - 1) {
                if (operations[i + 1].compare("(") != 0 && operations[i + 1].compare(")") != 0) {
                    if (values[z] && values[z + 1]) {
                        values[z + 1] = true;
                        z++;
                    }
                    else {
                        values[z + 1] = false;
                        z++;
                    }
                }
                else {
                    if (operations[i + 1].compare("(") == 0) {
                        if (i >= 1) {
                            if (operations[i - 1].compare(")") == 0) {
                                int currindx = z;
                                i += 2;
                                z++;
                                bool temp = ifConditionIsMet(values, operations, i, z);
                                z--;
                                if (values[currindx] && temp) {
                                    values[z + 1] = true;
                                    z++;
                                }
                                else {
                                    values[z + 1] = false;
                                    z++;
                                }
                            }
                            else {
                                int currindx = z;
                                i += 2;
                                z++;
                                bool temp = ifConditionIsMet(values, operations, i, z);
                                z--;
                                if (values[currindx] && temp) {
                                    values[z + 1] = true;
                                    z++;
                                }
                                else {
                                    values[z + 1] = false;
                                    z++;
                                }
                            }
                        }
                        else {
                            int currindx = z;
                            i += 2;
                            z++;//
                            bool temp = ifConditionIsMet(values, operations, i, z);
                            z--;//
                            if (values[currindx] && temp) {
                                values[z + 1] = true;
                                z++;
                            }
                            else {
                                values[z + 1] = false;
                                z++;
                            }
                        }
                    }
                    else if (operations[i + 1].compare(")") == 0) {
                        i += 1;
                        if (values[z] && values[z + 1]) {
                            values[z + 1] = true;
                            z++;
                            return true;
                        }
                        else {
                            values[z + 1] = false;
                            z++;
                            return false;
                        }
                    }
                }
            }
            else {
                if (values[z] && values[z + 1]) {
                    values[z + 1] = true;
                    z++;
                }
                else {
                    values[z + 1] = false;
                    z++;
                }
            }
        }
        else if (operations[i].compare("OR") == 0) {
            if (i != operations.size() - 1) {
                if (operations[i + 1].compare("(") != 0 && operations[i + 1].compare(")") != 0) {
                    if (values[z] || values[z + 1]) {
                        values[z + 1] = true;
                        z++;
                    }
                    else {
                        values[z + 1] = false;
                        z++;
                    }
                }
                else {
                    if (operations[i + 1].compare("(") == 0) {
                        if (i >= 1) {
                            if (operations[i - 1].compare(")") == 0) {
                                int currindx = z;
                                i += 2;
                                z++;
                                bool temp = ifConditionIsMet(values, operations, i, z);
                                z--;
                                if (values[currindx] || temp) {
                                    values[z + 1] = true;
                                    z++;
                                }
                                else {
                                    values[z + 1] = false;
                                    z++;
                                }
                            }
                            else {
                                int currindx = z;
                                i += 2;
                                z++;
                                bool temp = ifConditionIsMet(values, operations, i, z);
                                z--;
                                if (values[currindx] || temp) {
                                    values[z + 1] = true;
                                    z++;
                                    //
                                }
                                else {
                                    values[z + 1] = false;
                                    z++;
                                    //
                                }
                            }
                        }
                        else {
                            int currindx = z;
                            i += 2;
                            z++;//
                            bool temp = ifConditionIsMet(values, operations, i, z);
                            z--;//
                            if (values[currindx] || temp) {
                                values[z + 1] = true;
                                z++;
                            }
                            else {
                                values[z + 1] = false;
                                z++;
                            }
                        }

                    }
                    else if (operations[i + 1].compare(")") == 0) {
                        i += 1;
                        if (values[z] || values[z + 1]) {
                            values[z + 1] = true;
                            z++;
                            return true;
                        }
                        else {
                            values[z + 1] = false;
                            z++;
                            return false;
                        }
                    }
                }
            }
            else {
                if (values[z] || values[z + 1]) {
                    values[z + 1] = true;
                    z++;
                }
                else {
                    values[z + 1] = false;
                    z++;
                }
            }
        }
        else if (operations[i].compare(")") == 0) {
            return values[z]; // new
        }
        else if (operations[i].compare("(") == 0) {
            //int currindx = z;
            i += 1;
            bool temp = ifConditionIsMet(values, operations, i, z); // i+2, z+1
            //  return values[z]; 
        }

    }
    z = 0;
    i = 0;
    int result = values[values.size() - 1];
    values.clear();
    return result;
}

void HashListBase::deleteFunction(std::string toDeleteRow)
{
    std::vector<std::string> columnName;
    std::vector<std::string> operation;
    std::vector<std::string> value;
    std::vector<std::string> specOperation;
    
    int i = 0;
    std::string tempWord = "";
    for (;toDeleteRow[i];i++) {
        if ((toDeleteRow[i] >=65 && toDeleteRow[i]<=90) ||(toDeleteRow[i]>=97&&toDeleteRow[i]<=122)) { //adds only alphabet chars
            tempWord += toDeleteRow[i];
        }
        if (toDeleteRow[i] == ' ') {
            tempWord = "";
            continue;
        }
        if (tempWord.compare("WHERE") == 0) {
            tempWord = "";
            if (i + 2 > toDeleteRow.size()) {
                std::cout << "Invalid use of WHERE clause!" << std::endl;
                return;
            }
            i+=2;
            break;
        }
    }
    // opposite expression is if there is an expression () ,, in case there is a insideNot meaning not(not(...)) insideNot goes up, if its a single not ,, meaning
    // not a we are using the signle one, 
    // we are just changing the elemenets by using the NOT for the specialOperation and the operation vectors so to be checkign just for AND and OR later on.
    bool keyExists = false;
    std::string keyVal = getColumnFromTable(indexedAt);


    // newly added code to test in case ther are multiple times the key found.
    std::vector<int> keyIndexes;
    ///newly added above


    int keyIndex = 0;
    int separator = 0;
    bool toAddOppositeSingle = false;
    int insideNot = 0;
    bool toAddOppositeExpression = false;
    for (;toDeleteRow[i];i++) {
        if (toDeleteRow[i] == ' ') {
            tempWord = "";
            continue;
        }
        if (toDeleteRow[i] != ' ' && toDeleteRow[i] != '(' && toDeleteRow[i] != ')') {
            tempWord += toDeleteRow[i];
        }
        if (toDeleteRow[i] == '(') {
            specOperation.push_back("(");
        }
        if (tempWord.compare("NOT") == 0) {
            if (i + 2 > toDeleteRow.size()) {
                std::cout << "Invalid use of special operation: NOT" << std::endl;
                return;
            }
            if (toDeleteRow[i + 2] == '(') {
                if (toAddOppositeExpression)
                    insideNot++;
                else
                    toAddOppositeExpression = true;
            }
            else
                toAddOppositeSingle = true;
            continue;
        }
        if (toDeleteRow[i] == ')') {
            specOperation.push_back(")");
            if (toAddOppositeExpression && insideNot == 0)
                toAddOppositeExpression = false;
            if (insideNot > 0)
                insideNot--;
            
        }
        if ((toDeleteRow[i + 1] == ' ' || toDeleteRow[i + 1] == '\0') && tempWord.compare("") != 0) {
            //if (toDeleteRow[i] != ' ' || toDeleteRow[i] != '\0')
                if (separator % 4 == 0) {
                    if (!checkIfValidArg(tempWord, "", 0)) {
                        std::cout << "Invalid parameter for column name." << std::endl;
                        specOperation.clear();
                        operation.clear();
                        columnName.clear();
                        value.clear();
                        return;
                    }
                    columnName.push_back(tempWord);
                    if (tempWord.compare(keyVal) == 0) {
                        keyExists = true;
                        keyIndex = columnName.size() - 1;

                        ///////////////////////////////////////////////////////////////////////////////////////////
                        keyIndexes.push_back(keyIndex);
                    }
                }
                else if (separator % 4 == 1) {
                    if ((toAddOppositeExpression && (insideNot % 2 == 0) && toAddOppositeSingle) || (!toAddOppositeExpression && !toAddOppositeSingle) ||
                        (toAddOppositeExpression && !toAddOppositeSingle && (insideNot % 2 != 0))) {
                        if (!checkIfValidArg(tempWord, "", 1)) {
                            std::cout << "Invalid parameter for operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        operation.push_back(tempWord);
                    }
                    else {
                        if (!checkIfValidArg(tempWord, "", 1)) {
                            std::cout << "Invalid parameter for operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        operation.push_back(returnOppositeOperation(tempWord)); 
                    }
                    if (toAddOppositeSingle)
                        toAddOppositeSingle = false;

                }
                else if (separator % 4 == 2) {
                    if (!checkIfValidArg(tempWord, types[indexOfColumn(tableInfo, columnName[columnName.size() - 1])], 2)) {
                        // we are getting the type we need by using the function indexofcolumn using the tableInfo and as element taht we are searching, this is going to be the name of the column
                        // we do know that in order to get here for sure columnName was added and the one that represents this value is the last one in the vector.
                        std::cout << "Invalid parameter for value." << std::endl;
                        specOperation.clear();
                        operation.clear();
                        columnName.clear();
                        value.clear();
                        return;
                    }
                    value.push_back(tempWord);
                }
                else if (separator % 4 == 3) {
                    if ((toAddOppositeExpression && (insideNot % 2 == 0) && toAddOppositeSingle) || (!toAddOppositeExpression && !toAddOppositeSingle) ||
                        (toAddOppositeExpression && !toAddOppositeSingle && (insideNot % 2 != 0))) {
                        if (!checkIfValidArg(tempWord, "", 3)) {
                            std::cout << "Invalid parameter for special operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        specOperation.push_back(tempWord);
                    }
                    else {
                        if (!checkIfValidArg(tempWord, "", 3)) {
                            std::cout << "Invalid parameter for special operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        specOperation.push_back(returnOppositeSpecialOperation(tempWord));
                    }
                    if (toAddOppositeSingle)
                        toAddOppositeSingle = false;
                    //specOperation.push_back(tempWord);
                }
            separator++;
            tempWord = "";
        }
    }
    /*
    for (int i = 0;i < columnName.size();i++) {
        std::cout << "ColumnName " << i << ": " << columnName[i] << std::endl;
    }
    for (int i = 0;i < operation.size();i++) {
        std::cout << "operation " << i << ": " << operation[i] << std::endl;
    }
    for (int i = 0;i < value.size();i++) {
        std::cout << "value " << i << ": " << value[i] << std::endl;
    }
    for (int i = 0;i < specOperation.size();i++) {
        std::cout << "specOperation " << i << ": " << specOperation[i] << std::endl;
    }*/
    std::vector<std::string> rowsToBeDeleted;
    // this is the logic in case none of the columns are part of the key!.
    if (!keyExists) {
        for (int k = 0;k < children.size();k++) {
            std::vector<bool> checkersForSpecOp;
            Row* curr = &children[k];
            while (curr) {
                for (int j = 0;j < columnName.size();j++) {
                    int indxOfCol = indexOfColumn(tableInfo, columnName[j]);
                    if (operation[j].compare("<") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol),value[j],types[indxOfCol]) == -1) { // column j must be changed to real column 
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare(">") == 0) {
                       // if (asciiVal(getColumn(curr->data, indxOfCol)) > asciiVal(value[j])) { // all are the same but == and !=
                        if(compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 1){
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare(">=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) >= 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare("<=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) <= 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare("=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare("!=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) != 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else {
                        std::cout << "Error" << std::endl;
                        return;
                    }
                }
                int o = 0;
                int p = 0;
                // newly added to be checked!!!!!!!!!
                try {
                    if (ifConditionIsMet(checkersForSpecOp, specOperation, o, p)) {
                        rowsToBeDeleted.push_back(curr->data);
                    }
                }
                catch (std::invalid_argument) {
                    std::cout << "Invalid arguments passed to WHERE clause!" << std::endl;
                    return;
                }
                curr = curr->next;
            }
        }
    }
    else {
        for (int k = 0;k < children.size();k++) {
            std::vector<bool> checkersForSpecOp;
            Row* curr = &children[k];
            // this is used to skip all elements that are not suiting the operation connected to the key
            // newly added test !!!!
            for (int itrOverKeyIndexes = 0;itrOverKeyIndexes < keyIndexes.size();itrOverKeyIndexes++) {
                if (operation[keyIndexes[itrOverKeyIndexes]].compare("<") == 0) {
                    if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) != -1) {
                        continue;
                    }
                }
                else if (operation[keyIndexes[itrOverKeyIndexes]].compare(">") == 0) {
                    if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) != 1) {
                        continue;
                    }
                }
                else if (operation[keyIndexes[itrOverKeyIndexes]].compare(">=") == 0) {
                    if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) == -1) {
                        continue;
                    }
                }
                else if (operation[keyIndexes[itrOverKeyIndexes]].compare("<=") == 0) {
                    if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) == 1) {
                        continue;
                    }
                }
                else if (operation[keyIndexes[itrOverKeyIndexes]].compare("!=") == 0) {
                    if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) == 0) {
                        continue;
                    }
                }
                else if (operation[keyIndexes[itrOverKeyIndexes]].compare("=") == 0) {
                    if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) != 0) {
                        continue;
                    }
                }
            }
            while (curr) {
                for (int j = 0;j < columnName.size();j++) {
                    int indxOfCol = indexOfColumn(tableInfo, columnName[j]);
                    if (operation[j].compare("<") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == -1) { // column j must be changed to real column 
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare(">") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 1) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare(">=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) >= 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare("<=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) <= 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare("=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else if (operation[j].compare("!=") == 0) {
                        if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) != 0) {
                            checkersForSpecOp.push_back(1);
                        }
                        else {
                            checkersForSpecOp.push_back(0);
                        }
                    }
                    else {
                        std::cout << "Error" << std::endl;
                        return;
                    }
                }
                int o = 0;
                int p = 0;
                // newly added
                try {
                    if (ifConditionIsMet(checkersForSpecOp, specOperation, o, p)) {
                        rowsToBeDeleted.push_back(curr->data);
                    }
                }
                catch (std::invalid_argument) {
                    std::cout << "Invalid arguments passed to WHERE clause!" << std::endl;
                    return;
                }
                curr = curr->next;
            }
        }
    }
    for (int i = 0;i < rowsToBeDeleted.size();i++) {
        removeElement(rowsToBeDeleted[i]);
    }

    std::cout << "Total " << rowsToBeDeleted.size() << " rows deleted!" << std::endl;
    // newly added to delete our vectors.
    rowsToBeDeleted.clear();
    specOperation.clear();
    operation.clear();
    columnName.clear();
    value.clear();
}

void HashListBase::deleteFunctionAll()
{
    // until its not empty  delete all the first elementss.. and their next so we clear all the rows without removing the info for the table.
    // also at this point we are saving all the changes into our file
    std::ofstream editFile;
    editFile.open(tableName + ".csv", editFile.trunc);
    if (editFile.is_open()) {
        editFile << tableInfo.substr(1,tableInfo.size()-2) << std::endl; // first row will be table info
        for (int i = 0;i < children.size();i++) {
            Row* curr = children[i].next;
            editFile << children[i].data.substr(1, children[i].data.size() - 2) <<std::endl;
            while (curr) {
                editFile << curr->data.substr(1,curr->data.size()-2) << std::endl; // we do it like this so it removes the ( and ) 
                curr = curr->next;
            }
        }
        editFile.close();
    }
 
    while(!children.empty()) {
        Row* curr = children[0].next;
        Row* toDelete = curr;
        while (curr) {
            toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        children.erase(children.begin());
    }
    rowCount = 0;
    types.clear();
}

void HashListBase::addElements(std::vector<std::string> rows)
{
    try {
        for (int i = 0;i < rows.size();i++) {
            addElement(rows[i]);
        }
        //rowCount += rows.size();
    }
    catch (std::invalid_argument) {
        for (int i = 0;i < rows.size();i++) {
            removeElement(rows[i]);
            
        }
        throw std::invalid_argument("invalid");
    }
}

void HashListBase::removeElement(std::string data) {

    // have to make a function to get the indexedAt;

    std::string testKey = getColumn(data, indexedAt);
    bool foundFlag = false; 
    for (int i = 0; i < children.size() && !foundFlag;i++) {
        if (testKey.compare(children[i].key) == 0) {
            if (data.compare(children[i].data) == 0) {
                if (children[i].next) {
                    Row* toDelete = children[i].next;
                    children[i].key = toDelete->key;
                    children[i].data = toDelete->data;
                    children[i].next = toDelete->next;
                    delete toDelete;
                    foundFlag = true;
                }
                else {
                    children.erase(std::find(children.begin(), children.end(), children[i]));
                    foundFlag = true;
                }
            }
            else {
                Row* prev = &children[i];
                Row* curr = children[i].next;
                while (curr) {
                    if (curr->data.compare(data) == 0) {
                        prev->next = curr->next;
                        delete curr;
                        foundFlag = true;
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
    if (foundFlag) {
        rowCount--;
    }
}

void HashListBase::orderByPrint(std::string columnName, std::vector<int> columnIndexesToBeShown, bool ifAll, std::vector<std::string>rowsToBeShown, bool typeOfSort)
{
    // sort bubble sort slow but works : D 
    int indexOfCol = indexOfColumn(tableInfo, columnName);
    std::string typeOfCol = types[indexOfCol];
    if (columnIndexesToBeShown.empty()) {
        for (int i = 0;i < types.size();i++) {
            if (i == types.size() - 1) {
                std::cout << getColumnFromTable(i) << std::endl << std::endl;
            }
            else {
                std::string toBePrinted = getColumnFromTable(i);
                std::cout << toBePrinted;
                printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
            }
        }
    }
    else {
        for (int i = 0;i < columnIndexesToBeShown.size();i++) {
            if (i == columnIndexesToBeShown.size() - 1) {
                std::cout << getColumnFromTable(columnIndexesToBeShown[i]) << std::endl<<std::endl;
            }
            else {
                std::string toBePrinted = getColumnFromTable(columnIndexesToBeShown[i]);
                std::cout << toBePrinted;
                printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
            }
        }
    }
   
    int res = 100;
    for (int i = 0;i < rowsToBeShown.size();i++) {
        for (int j = i+1;j < rowsToBeShown.size();j++) {
            res = compareData(getColumn(rowsToBeShown[i], indexOfCol), getColumn(rowsToBeShown[j], indexOfCol), typeOfCol);
            if(typeOfSort){
                if (res <= 0) {
                    if (res == 0) {
                        if (compareData(rowsToBeShown[i], rowsToBeShown[j], "String") >= 0)// we are doing this in case the column is same but the entire row not.
                            continue;
                    }
                    std::swap(rowsToBeShown[i], rowsToBeShown[j]);
                }
            }
            else {
                if (res >= 0) {
                    if (res == 0) {
                        if (compareData(rowsToBeShown[i], rowsToBeShown[j], "String") <= 0)
                            continue;
                    }
                    std::swap(rowsToBeShown[i], rowsToBeShown[j]);
                }
            }
            /*if (res >= 0) {
                if (res == 0) {
                    if (compareData(rowsToBeShown[i], rowsToBeShown[j], "String") <= 0)
                        continue;
                }
                std::swap(rowsToBeShown[i], rowsToBeShown[j]);
            }*/
        }
    }
    if (ifAll) {
        for (int itr = 0; itr < rowsToBeShown.size();itr++) {
            //std::cout << rowsToBeShown[itr] << std::endl;
            for (int itr2 = 0;itr2 < types.size();itr2++) {
                if (itr2 == types.size() - 1) {
                    std::cout << getColumn(rowsToBeShown[itr], itr2) << std::endl;
                }
                else {
                    std::string toBePrinted = getColumn(rowsToBeShown[itr], itr2);
                    std::cout << toBePrinted;
                    printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
                }
            }
        }
    }
    else {
        for (int itr = 0; itr < rowsToBeShown.size();itr++) {
            for (int itr2 = 0;itr2 < columnIndexesToBeShown.size();itr2++) {
                if (itr2 == columnIndexesToBeShown.size() - 1) {
                    std::cout << getColumn(rowsToBeShown[itr], columnIndexesToBeShown[itr2]) << std::endl;
                }
                else {
                    std::string toBePrinted = getColumn(rowsToBeShown[itr], columnIndexesToBeShown[itr2]);
                    std::cout << toBePrinted;
                    printSpaces(SIZE_FOR_INTERVALS - toBePrinted.size());
                }
            }
        }
    }
    //for (int i = 0;i < allElements.size();i++) {
     //   std::cout << allElements[i] << std::endl;
    //}
    std::cout << "Total " << rowsToBeShown.size() << " rows selected." << std::endl;
    
}

void HashListBase::selectFunction(std::string row)
{
    int i = 0;
    std::string tempWord = "";
    bool distinctFlag = false;
    bool allElements = false;
    bool whereFlag = false;
    bool toInsert = false;
    bool orderByFlag = false;
    std::vector<std::string> columnsToBeOrderedBy;
    int j = 0;
    std::vector<std::string> columnNamesForShowing;
    for (;row[j];j++) {
        if ((row[j] >= 65 && row[j] <= 90) || (row[j] >= 97 && row[j] <= 122)) { //adds only alphabet chars
            tempWord += row[j];
        }
        if (tempWord.compare("ORDER") == 0) {
            if (j + 3 > row.size()) {
                std::cout << "Invalid use of ORDER" << std::endl;
                return;
            }
            else if (row[j + 2] != 'B' || row[j + 3] != 'Y') {
                std::cout << "Invalid use of ORDER" << std::endl;
                return;
            }
            j += 3;
            orderByFlag = true;
            tempWord = "";
            continue;
        }
        if (tempWord.compare("Select") == 0) {
            toInsert = true;
            tempWord = "";
            continue;
        }
        if (tempWord.compare("FROM") == 0) {
            toInsert = false;
            tempWord = "";
            continue;
        }
        if (tempWord.compare("DISTINCT") == 0) {
            distinctFlag = true;
            tempWord = "";
            continue;
        }
        if (row[j] == '*' && toInsert) {
            allElements = true;
            tempWord = "";
            toInsert = false;
            continue;
        }
        if (toInsert && !allElements && row[j] == ' ' && tempWord.compare("") != 0) {
            if (!checkIfValidArg(tempWord, "", 0)) {
                std::cout << "Invalid parameter for column name." << std::endl;
                return;
            }
            columnNamesForShowing.push_back(tempWord);
        }
        if (tempWord.compare("WHERE") == 0) {
            tempWord = "";
            if (j + 2 > row.size()) {
                std::cout << "Invalid use of WHERE clause!" << std::endl;
                return;
            }
            j += 2;
            i = j;
            whereFlag = true;
            continue;
        }
        if (orderByFlag && (row[j] == ' ' || row[j + 1] == '\0') && tempWord.compare("") != 0) {
            if ((!checkIfValidArg(tempWord, "", 0) && tempWord.compare("DESC") != 0 && tempWord.compare("ASC") != 0) || ((tempWord.compare("ASC") == 0 || tempWord.compare("DESC") == 0) && columnsToBeOrderedBy.empty())) {
                // checking if the word is valid name, also if its DESC or ASC can be added only if the columnsTobeOrderedBy is not empty.
                std::cout << "Invalid parameter for column name." << std::endl;
                return;
            }
            columnsToBeOrderedBy.push_back(tempWord);
        }
        if (row[j] == ' ') {
            tempWord = "";
            continue;
        }
    }
    if (!whereFlag && !orderByFlag) {
        // all elements no where clause and no order
        std::vector<std::string> rowsToShow;
        for (int i = 0;i < children.size();i++) {
            Row* curr = &children[i];
            while (curr) {
                rowsToShow.push_back(curr->data);
                curr = curr->next;
            }
        }
        std::vector<int> indexesOfColumnsToBeShown;
        for (int itr = 0; itr < columnNamesForShowing.size();itr++) {
            indexesOfColumnsToBeShown.push_back(indexOfColumn(tableInfo, columnNamesForShowing[itr]));
        }
        // if allElements are required then indexesOfColumns will be filled if not then they will stay empty.
        print(indexesOfColumnsToBeShown,rowsToShow);
    }
    else if (!whereFlag && orderByFlag) {
        bool DESC = false;
        if (!columnsToBeOrderedBy.empty()) {
            if (columnsToBeOrderedBy[columnsToBeOrderedBy.size() - 1].compare("DESC") == 0) {
                DESC = true;
            }
        }
        std::vector<std::string> rowsToShow;
        for (int i = 0; i < children.size();i++) {
            Row* curr = &children[i];
            while (curr) {
                rowsToShow.push_back(curr->data);
                curr = curr->next;
            }
        }
        std::vector<int> indexesOfColumnsToBeShown;
        if (allElements) {
            if (columnsToBeOrderedBy.empty()) {
                std::cout << "Invalid use of order, column name must be provided! " << std::endl;
                return;
            }
            else
                orderByPrint(columnsToBeOrderedBy[0], indexesOfColumnsToBeShown, true, rowsToShow, DESC);
        }
        else {
            for (int itr = 0; itr < columnNamesForShowing.size();itr++) {
                indexesOfColumnsToBeShown.push_back(indexOfColumn(tableInfo, columnNamesForShowing[itr]));
            }
            if (columnsToBeOrderedBy.empty()) {
                std::cout << "Invalid use of order, column name must be provided! " << std::endl;
                return;
            }
            else
                orderByPrint(columnsToBeOrderedBy[0], indexesOfColumnsToBeShown, false, rowsToShow, DESC);

        }
    }
    else { 
        // this is in case there is a WHERE clause and here we are getting the entire logic which rows remain to be shown.
        tempWord = "";
        std::vector<std::string> columnName;
        std::vector<std::string> operation;
        std::vector<std::string> value;
        std::vector<std::string> specOperation;


        bool keyExists = false;
        std::string keyVal = getColumnFromTable(indexedAt);
        std::vector<int> keyIndexes;
        int keyIndex = 0;
        int separator = 0;
        bool toAddOppositeSingle = false;
        int insideNot = 0;
        bool toAddOppositeExpression = false;
        for (;row[i];i++) {
            if (row[i] == ' ') {
                tempWord = "";
                continue;
            }
            if (row[i] != ' ' && row[i] != '(' && row[i] != ')') {
                tempWord += row[i];
            }
            if (row[i] == '(') {
                specOperation.push_back("(");
            }
            if (tempWord.compare("NOT") == 0) {
                if (i + 2 > row.size()) {
                    std::cout << "Invalid use of special operation: NOT" << std::endl;
                    return;
                }
                if (row[i + 2] == '(') {
                    if (toAddOppositeExpression)
                        insideNot++;
                    else
                        toAddOppositeExpression = true;
                }
                else
                    toAddOppositeSingle = true;
                continue;
            }
            if (row[i] == ')') {
                specOperation.push_back(")");
                if (toAddOppositeExpression && insideNot == 0)
                    toAddOppositeExpression = false;
                if (insideNot > 0)
                    insideNot--;

            }

            if (tempWord.compare("ORDER") == 0) {
                break;
            }
            if ((row[i + 1] == ' ' || row[i + 1] == '\0') && tempWord.compare("") != 0) {
                //if (row[i] != ' ' || row[i] != '\0')
                if (separator % 4 == 0) {
                    if (!checkIfValidArg(tempWord, "", 0)) {
                        std::cout << "Invalid parameter for column name." << std::endl;
                        specOperation.clear();
                        operation.clear();
                        columnName.clear();
                        value.clear();
                        return;
                    }
                    columnName.push_back(tempWord);
                    if (tempWord.compare(keyVal) == 0) {
                        keyExists = true;
                        keyIndex = columnName.size() - 1;
                        keyIndexes.push_back(keyIndex);
                    }
                }
                else if (separator % 4 == 1) {
                    if ((toAddOppositeExpression && (insideNot % 2 == 0) && toAddOppositeSingle) || (!toAddOppositeExpression && !toAddOppositeSingle) ||
                        (toAddOppositeExpression && !toAddOppositeSingle && (insideNot % 2 != 0))) {
                        if (!checkIfValidArg(tempWord, "", 1)) {
                            std::cout << "Invalid parameter for operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        operation.push_back(tempWord);
                    }
                    else {
                        if (!checkIfValidArg(tempWord, "", 1)) {
                            std::cout << "Invalid parameter for operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        operation.push_back(returnOppositeOperation(tempWord));
                    }
                    if (toAddOppositeSingle)
                        toAddOppositeSingle = false;

                }
                else if (separator % 4 == 2) {
                    if (!checkIfValidArg(tempWord, types[indexOfColumn(tableInfo, columnName[columnName.size()-1])], 2)) {
                        // we are getting the type we need by using the function indexofcolumn using the tableInfo and as element taht we are searching, this is going to be the name of the column
                        // knowing we for sure added 2 elements before this one we know for sure that the column name last element is the one needed.
                        std::cout << "Invalid parameter for value." << std::endl;
                        specOperation.clear();
                        operation.clear();
                        columnName.clear();
                        value.clear();
                        return;
                    }
                    value.push_back(tempWord);
                }
                else if (separator % 4 == 3) {
                    if ((toAddOppositeExpression && (insideNot % 2 == 0) && toAddOppositeSingle) || (!toAddOppositeExpression && !toAddOppositeSingle) ||
                        (toAddOppositeExpression && !toAddOppositeSingle && (insideNot % 2 != 0))) {
                        if (!checkIfValidArg(tempWord, "", 3)) {
                            std::cout << "Invalid parameter for special operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        specOperation.push_back(tempWord);
                    }
                    else {
                        if (!checkIfValidArg(tempWord, "", 3)) {
                            std::cout << "Invalid parameter for special operation." << std::endl;
                            specOperation.clear();
                            operation.clear();
                            columnName.clear();
                            value.clear();
                            return;
                        }
                        specOperation.push_back(returnOppositeSpecialOperation(tempWord));
                    }
                    if (toAddOppositeSingle)
                        toAddOppositeSingle = false;
                    //specOperation.push_back(tempWord);
                }
                separator++;
                tempWord = "";
                
            }
        }

        std::vector<std::string> rowsToBeShown;
        // this is the logic in case none of the columns are part of the key!.
        if (!keyExists) {
            for (int k = 0;k < children.size();k++) {
                std::vector<bool> checkersForSpecOp;
                Row* curr = &children[k];
                while (curr) {
                    for (int j = 0;j < columnName.size();j++) {
                        int indxOfCol = indexOfColumn(tableInfo, columnName[j]);
                        if (operation[j].compare("<") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == -1) { // column j must be changed to real column 
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare(">") == 0) {
                            // if (asciiVal(getColumn(curr->data, indxOfCol)) > asciiVal(value[j])) { // all are the same but == and !=
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 1) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare(">=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) >= 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare("<=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) <= 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare("=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare("!=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) != 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else {
                            std::cout << "Error" << std::endl;
                            return;
                        }
                    }
                    int o = 0;
                    int p = 0;
                    // if (ifConditionIsMet(checkersForSpecOp, specOperation, o, p)) {
                     //    rowsToBeShown.push_back(curr->data);
                    // }
                    //newly added
                    try {
                        if (ifConditionIsMet(checkersForSpecOp, specOperation, o, p)) {
                            if (distinctFlag) {
                                if (std::find(rowsToBeShown.begin(), rowsToBeShown.end(), curr->data) == rowsToBeShown.end()) {
                                    rowsToBeShown.push_back(curr->data);
                                }
                            }
                            else {
                                rowsToBeShown.push_back(curr->data);
                            }
                        }
                    }
                    catch (std::invalid_argument) {
                        std::cout << "Invalid arguments passed to WHERE clause!" << std::endl;
                        return;
                    }
                    curr = curr->next;
                }
            }
        }
        else {
            for (int k = 0;k < children.size();k++) {
                std::vector<bool> checkersForSpecOp;
                Row* curr = &children[k];
                for (int itrOverKeyIndexes = 0;itrOverKeyIndexes < keyIndexes.size();itrOverKeyIndexes++) {
                    if (operation[keyIndexes[itrOverKeyIndexes]].compare("<") == 0) {
                        if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) != -1) {
                            continue;
                        }
                    }
                    else if (operation[keyIndexes[itrOverKeyIndexes]].compare(">") == 0) {
                        if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) != 1) {
                            continue;
                        }
                    }
                    else if (operation[keyIndexes[itrOverKeyIndexes]].compare(">=") == 0) {
                        if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) == -1) {
                            continue;
                        }
                    }
                    else if (operation[keyIndexes[itrOverKeyIndexes]].compare("<=") == 0) {
                        if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) == 1) {
                            continue;
                        }
                    }
                    else if (operation[keyIndexes[itrOverKeyIndexes]].compare("!=") == 0) {
                        if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) == 0) {
                            continue;
                        }
                    }
                    else if (operation[keyIndexes[itrOverKeyIndexes]].compare("=") == 0) {
                        if (compareData(getColumn(curr->data, indexedAt), value[keyIndexes[itrOverKeyIndexes]], types[keyIndex]) != 0) {
                            continue;
                        }
                    }
                }
                while (curr) {
                    for (int j = 0;j < columnName.size();j++) {
                        int indxOfCol = indexOfColumn(tableInfo, columnName[j]);
                        if (operation[j].compare("<") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == -1) { // column j must be changed to real column 
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare(">") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 1) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare(">=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) >= 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare("<=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) <= 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare("=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) == 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else if (operation[j].compare("!=") == 0) {
                            if (compareData(getColumn(curr->data, indxOfCol), value[j], types[indxOfCol]) != 0) {
                                checkersForSpecOp.push_back(1);
                            }
                            else {
                                checkersForSpecOp.push_back(0);
                            }
                        }
                        else {
                            std::cout << "Error" << std::endl;
                            return;
                        }
                    }
                    int o = 0;
                    int p = 0;
                    //newly added
                    try {
                        if (ifConditionIsMet(checkersForSpecOp, specOperation, o, p)) {
                            if (distinctFlag) {
                                if (std::find(rowsToBeShown.begin(), rowsToBeShown.end(), curr->data) == rowsToBeShown.end()) {
                                    rowsToBeShown.push_back(curr->data);
                                }
                            }
                            else {
                                rowsToBeShown.push_back(curr->data);
                            }
                        }
                    }
                    catch (std::invalid_argument) {
                        std::cout << "Invalid arguments passed to WHERE clause!" << std::endl;
                        return;
                    }
                    curr = curr->next;
                }
            }
        }
        // if we have to sort it in DESC the last element of the sorted by will be either DESC/ ASC or none/ if its DESC -- > desc else normal
        bool DESC = false;
        if (!columnsToBeOrderedBy.empty()) {
            if (columnsToBeOrderedBy[columnsToBeOrderedBy.size() - 1].compare("DESC") == 0) {
                DESC = true;
            }
        }
        if (!orderByFlag) {
            std::vector<int> indexesOfColumnsToBeShown;
            for (int itr = 0; itr < columnNamesForShowing.size();itr++) {
                indexesOfColumnsToBeShown.push_back(indexOfColumn(tableInfo, columnNamesForShowing[itr]));
            }
            // but columnNamesForShowing will be empty so it will show all.
            print(indexesOfColumnsToBeShown, rowsToBeShown);
            
        }
        else {
            std::vector<int> indexesOfColumnsToBeShown;
            if (allElements) {
                if (columnsToBeOrderedBy.empty()) {
                    std::cout << "Invalid use of order, column name must be provided! " << std::endl;
                    return;
                }
                else
                    orderByPrint(columnsToBeOrderedBy[0], indexesOfColumnsToBeShown, true, rowsToBeShown, DESC);
            }
            else {
                for (int itr = 0; itr < columnNamesForShowing.size();itr++) {
                    indexesOfColumnsToBeShown.push_back(indexOfColumn(tableInfo, columnNamesForShowing[itr]));
                }
                if (columnsToBeOrderedBy.empty()) {
                    std::cout << "Invalid use of order, column name must be provided! " << std::endl;
                    return;
                }
                else
                    orderByPrint(columnsToBeOrderedBy[0], indexesOfColumnsToBeShown, false, rowsToBeShown, DESC);

            }
        }


    }
}// newly added
int HashListBase::compareData(std::string lhs, std::string rhs, std::string type)
{
    if (type.compare("Int") == 0) {
        if (lhs.compare("") == 0 && rhs.compare("") == 0)
            return 0;
        if (lhs.compare("") != 0 && rhs.compare("") == 0)
            return 1;
        if (lhs.compare("") == 0 && rhs.compare("") != 0)
            return -1;
        if (stoi(lhs) == stoi(rhs))
            return 0;
        if (stoi(lhs) < stoi(rhs))
            return -1;
        if (stoi(lhs) > stoi(rhs))
            return 1;
    }
    else if (type.compare("String") == 0) {
        if (asciiVal(lhs) == asciiVal(rhs))
            return 0;
        if (asciiVal(lhs) < asciiVal(rhs))
            return -1;
        if (asciiVal(lhs) > asciiVal(rhs))
            return 1;
    }
    else {
        if (lhs.compare("") == 0 && rhs.compare("") == 0)
            return 0;
        if (lhs.compare("") != 0 && rhs.compare("") == 0)
            return 1;
        if (lhs.compare("") == 0 && rhs.compare("") != 0)
            return -1;
        std::vector<std::string> tempLhsData;
        std::vector<std::string>tempRhsData;
        std::string tempWordLhs = "";
        std::string tempWordRhs = "";
        for (int i = 0; i < lhs.size();i++) {
            if (lhs[i] >= 48 && lhs[i] <= 57 &&i != (lhs.size()-1)) { // digits
                tempWordLhs += lhs[i];
            }
            else {
                if (i == (lhs.size() - 1)) {
                    tempWordLhs += lhs[i];
                }
                tempLhsData.push_back(tempWordLhs);
                tempWordLhs = "";
            }
        }
        for (int i = 0; i < rhs.size();i++) {
            if (rhs[i] >= 48 && rhs[i] <= 57 && i != (rhs.size() - 1)) { // digits
                tempWordRhs += rhs[i];
            }
            else {
                if (i == (rhs.size() - 1)) {
                    tempWordRhs += rhs[i];
                }
                tempRhsData.push_back(tempWordRhs);
                tempWordRhs = "";
            }
        }
        for (int i = tempLhsData.size()-1 ;i >= 0;i--) {
            if (stoi(tempLhsData[i]) < stoi(tempRhsData[i]))
                return -1;
            if (stoi(tempLhsData[i]) > stoi(tempRhsData[i]))
                return 1;
        }
        return 0;
    }
}
const int HashListBase::getRowCount()const {
    return rowCount;
}
HashListBase::~HashListBase() {

    clean();

}


const std::string HashListBase::getTableName() const
{
    return tableName;
}

const std::string HashListBase::getTableInfo() const
{
    return tableInfo;
}

HashListBase::HashListBase() {

    tableName = "Sample"+std::to_string(objects++);
    tableInfo = "(ID:Int, Indexed; Name:String; Date:Date)";
    types.push_back("Int");
    types.push_back("String");
    types.push_back("Date");
    indexedAt = 0;
    rowCount = 0;

}

HashListBase::HashListBase(std::string fullData) {
   rowCount = 0;
   getAllStringInfo(fullData, tableName, tableInfo, indexedAt, types);
}


HashListBase::HashListBase(const HashListBase& other) {

    copy(other);

}

HashListBase& HashListBase::operator=(const HashListBase& rhs) {

    if (this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

