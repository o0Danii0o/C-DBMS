
#include "DataBases.h"
#include <chrono>
/*
int main() {
	/*DataBaseLL obj;
	DataBaseLL obj2("1, pesho, 3","ID:Int, Indexed; Name:String, Value:Int, Whatever:Data");
	obj2.push_end("1, pesho, 3");
	obj2.push_front("0, ivan, 4"); // not supposed to e possible!
	obj2.push_at("2, george, 5", 2);
	DataBaseLL obj3 = obj2;
	obj3.print();
	//obj2.pop_front();
	obj2.print();
	std::cout << obj2.getIndexed() << std::endl;
	std::cout << obj2.getWord(2, 2);
	
	auto start = std::chrono::high_resolution_clock::now();
	DatabaseHash obj;
	DatabaseHash obj2("Table1", "ID:Int, Indexed; Name:String; Value:Int");
	obj2.insertItem("1, gosho, 100");
	obj2.insertItem("2, ivan, 101");
	obj2.insertItem("3, petko, 101");
	obj2.insertItem("4, spas, 103");
	obj2.insertItem("5, gosho, 104");
	obj2.insertItem("6, dada, 105");
	obj2.insertItem("7, ne, 106");
	obj2.insertItem("8, asdasd, 107");
	obj2.insertItem("9, fffff, 108");
	obj2.insertItem("10, aaaaa, 101");
	//obj2.deleteItem("5, gosho, 104");
	//obj2.findAll("gosho");
	obj2.showUsed();
	//obj2.findByNonKeyValue("101");
	//obj2.findAll("101");
	//obj2.findByNonKeyValueWithOperation("3", ">",0);
	std::vector<std::string> valsWithKeyFirst = { "gosho","6","100" };
	std::vector<std::string> operWithKeyFirst = { "!=","<","!=" };
	std::vector<int> rowsWithKeyFirst = { 1,0,2 };
	//std::vector<std::string> vals = { "5","a","100" };
	//std::vector<std::string> oper = { "<",">","!=" };
	//std::vector<int> rows = { 0,1,2 };
	//obj2.findByNonKeyValueWithOperationList(vals, oper, rows);
	obj2.findByKeyValueWithOperationList(valsWithKeyFirst,operWithKeyFirst,rowsWithKeyFirst);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Time taken by functions: " << duration.count() << " microseconds" << std::endl;
	//std::cout<<obj2.getColData("gosho e idiot", 1);
	obj2.findAllWithOperations("Select Name FROM Sample WHERE ID != 5 AND Name < 50 ORDER BY Name");
	return 0;
	
}
/// Have to make a new data structure to work with all the implementation // I need a tree in which I will add the indexation just below root, 
// meaning if the data we need to index is string we will have vector<Nodes> for the root, and each Node will have only next, so it will be a root, with many children
// however each children will be a list. 
*/
void readFromConsole() {
	DataBase tester;
	std::string line;
	while (getline(std::cin, line)) {
		//std::cout << line << std::endl;
		if (line.compare("Quit") == 0) {
			std::cout << "Good Bye" << std::endl;
			return;
		}
		else {
			tester.DetermineFunction(line);
		}
	}
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();


	/*TreeBase obj1("CreateTable Sample (ID:Int, Name:String, Value:Date) Index ON Value");
	std::vector<std::string> elements{ "(1, Ivan, 01.10.2016)" ,"(2, Iva, 01.10.2017)" ,"(3, Pesho, 01.10.2018)" ,
		"(4, Gosho, 01.11.2015)" ,"(5, Spas, 01.10.2022)" ,"(4, Atanas, 01.10.2050)" ,"(7, Pesho, 11.11.2015)" ,"(2, Ivan, 21.10.2018)"
	,"(1, Georgi, 01.10.2010)" ,"(9, Georgi, 01.10.2013)", "(1, Georgi, 01.10.2010)" };
	*/
	readFromConsole();
	/*
	obj1.addElement("1, Ivan, 12");
	obj1.addElement("2, Iva, 13");
	obj1.addElement("3, Pesho, 14");
	obj1.addElement("4, Gosho, 15");
	obj1.addElement("5, Spas, 14");
	obj1.addElement("4, Atanas, 15");
	obj1.addElement("7, Pesho, 12");
	obj1.addElement("2, Ivan, 17");
	obj1.addElement("1, Georgi, 22");
	obj1.addElement("9, Georgi, 19");*/
	//TreeBase* obj2 = new TreeBase(obj1);
	//obj1.addElements(elements);
	//TreeBase* obj2 = new TreeBase(obj1);
	//obj1.insertFunction("{(1, \"TEST\", 11.12.2043), (2, \"something else\", 10.15.3443)}");
	//obj1.removeElement("1, Ivan, 12");
	//obj1.print();
	//obj2->print();
	//std::cout << "Result is : " << obj1.compareData("12.12.2018", "12.05.2018", "Date") << std::endl;
	//std::cout << "--------------------------------------------------------------------" << std::endl;
	//obj1.rowsDeletion("Delete FROM Sample WHERE ID < 3 AND Name != Ivan");
	//obj1.print();
	//obj1.orderByPrint("Name");
	//obj1.rowsDeletion("DELETE A FROM B WHERE NOT ID < 3 AND NOT (NOT (Name != Ivan AND Name != Pesho))");
	//obj1.print();
	//obj1.selectFunction("SELECT DISTINCT ID, Name, Date FROM ROW WHERE ID >= 1 AND  Name != Pesho ORDER BY Date DESC");
	/*DataBase tester;
	//tester.DetermineFunction("CreateTable Gosho");
	
	tester.DetermineFunction("CreateTable Sample (ID:Int, Name:String, Value:Date) Index ON Value");
	tester.DetermineFunction("Insert INTO Sample {(1, \"TEST\", 11.12.2043), (2, \"something else\", 10.15.3443)}");
	tester.DetermineFunction("Select * FROM Sample");
	tester.DetermineFunction("Insert INTO Sample0 {(1, Ivan, 01.10.2015), (2, Iva, 01.10.2015), (3, Pesho, 01.10.2018), (4, Gosho, 01.11.2015), (5, Spas, 01.10.2022), (4, Atanas, 01.10.2050), (7, Pesho, 11.11.2015), (2, Ivan, 21.10.2018), (1, Georgi, 01.10.2010), (9, Georgi, 01.10.2013), (1, Georgi, 01.10.2010)}");
	tester.DetermineFunction("Delete FROM Sample0 WHERE ID < 3 AND Name != Ivan");
	tester.DetermineFunction("TableInfo Gosho");
	tester.DetermineFunction("TableInfo Sample0");
	tester.DetermineFunction("ListTables");
	tester.DetermineFunction("DropTable Sample");
	tester.DetermineFunction("ListTables");
	tester.DetermineFunction("Select * FROM Sample0");
	tester.DetermineFunction("Select DISTINCT ID, Name, Date FROM Sample0 WHERE ID >= 1 AND  Name != Pesho ORDER BY Date DESC");
	tester.DetermineFunction("Select * FROM Sample0");
	tester.DetermineFunction("Delete FROM Sample0");
	tester.DetermineFunction("Select * FROM Sample0");
	tester.DetermineFunction("CreateTable Sample2 (ID:Int, Name:String)");
	tester.DetermineFunction("TableInfo Sample2");
	tester.DetermineFunction("CreateTable Sample222 (ID:Int, Name:String, Value:Date) Index ON Value");
	tester.DetermineFunction("TableInfo Sample222");
	tester.DetermineFunction("Select * FROM Sample222");
	tester.DetermineFunction("Insert INTO Sample222 {(1, tester, 10.10.10)}");
	tester.DetermineFunction("Select * FROM Sample222");
	tester.DetermineFunction("Select * FROM Sample0");
	*/
	//readFromConsole();
	//tester.CreateTable("CreateTable Sample (ID:Int, Name:String, Value:Date) Index ON Value");
	//tester.InsertInTable("Sample", "{(1, \"TEST\", 11.12.2043), (2, \"something else\", 10.15.3443)}");
	//tester.InsertInTable("Sample", "{(1, (Ivan, 01.10.2015), (2, Iva, 01.10.2015), (3, Pesho, 01.10.2018), (4, Gosho, 01.11.2015), (5, Spas, 01.10.2022), (4, Atanas, 01.10.2050), (7, Pesho, 11.11.2015), (2, Ivan, 21.10.2018), (1, Georgi, 01.10.2010), (9, Georgi, 01.10.2013), (1, Georgi, 01.10.2010)}");
	//tester.ListTables();
	//tester.TableInfo("Sample");
	//tester.SelectFromTable("Sample","SELECT DISTINCT ID, Name, Date FROM Sample WHERE ID >= 1 AND  Name != Pesho ORDER BY Date DESC");
	//tester.CreateTable("CreateTable NotSample (ID:Int, Name:String, Value:Date) Index ON ID");
	//tester.InsertInTable("NotSample", "{ (1, (Ivan, 01.10.2016), (2, Iva, 01.10.2017), (3, Pesho, 01.10.2018), (4, Gosho, 01.11.2015)}");
	
	//DataBase tester2(tester);
	//tester2.RemoveFromTable("Sample", "Delete FROM Sample WHERE ID < 3 AND Name != Ivan");
	//tester2.SelectFromTable("Sample", "SELECT DISTINCT ID, Name, Date FROM Sample WHERE ID >= 1 AND  Name != Pesho ORDER BY Date DESC");
	//tester.SelectFromTable("Sample", "SELECT DISTINCT ID, Name, Date FROM Sample WHERE ID >= 1 AND  Name != Pesho ORDER BY Date DESC");


	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Time taken by functions: " << duration.count() << " microseconds" << std::endl;

	//int* temp = new int[10];
	//delete temp;
	return 0;
}