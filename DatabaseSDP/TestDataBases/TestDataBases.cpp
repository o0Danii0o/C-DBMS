#include "pch.h"
#include "CppUnitTest.h"
#include "../DatabaseSDP/DataBases.h"
#include <string>  
#include <iostream> 
#include <sstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDataBases
{
	TEST_CLASS(TestDataBases)
	{
	public:
		
		TEST_METHOD(TestHashListBaseCreation)
		{
			// testing creating an object if it works properly.
			// each time we create empty object it creates a new table with the expectedtableinfo but with different name
			HashListBase obj1;
			HashListBase obj2("CreateTable Sample2 (ID:Int, Name:String, Value:Int, Age:Int, Birthdate:Date) Index ON Name");
			std::string expectedName = "Sample0";
			std::string expectedTableInfo = "(ID:Int, Indexed; Name:String; Date:Date)";
			// tests for default constructor
			Assert::AreEqual(expectedName, obj1.getTableName());
			Assert::AreEqual(expectedTableInfo, obj1.getTableInfo());
			Assert::AreEqual(0, obj1.getRowCount());
			
			//tests for creating by string (a.k.a if we use CreateTable) 
			expectedName = "Sample2";
			expectedTableInfo = "(ID:Int; Name:String, Indexed; Value:Int; Age:Int; Birthdate:Date)";
			Assert::AreEqual(expectedName, obj2.getTableName());
			Assert::AreEqual(expectedTableInfo, obj2.getTableInfo());
			Assert::AreEqual(0, obj2.getRowCount());

			// we are not testing random data to be inserted here, because our upper class logic is making sure only valid data is being sent here.
			
		}

		TEST_METHOD(TestListBaseInsertion) {
			// testing insertion
			HashListBase obj1;
			obj1.insertFunction("Nothing");
			obj1.insertFunction("{(1, invaliddate, 32.12.2022)}");
			obj1.insertFunction("{(da, invalidID, 12.12.2022)}");
			obj1.insertFunction("{(1, invalidDate, 10.10)}");
			obj1.insertFunction("{()}");
			obj1.insertFunction("");
			Assert::AreEqual(0, obj1.getRowCount());

			obj1.insertFunction("{(1, success, 20.12.2022)}");
			Assert::AreEqual(1, obj1.getRowCount());
			obj1.insertFunction("{(2, success, 20.12.2022), (3, success, 20.12.2022), (4, success, 20.12.2022), (5, success, 20.12.2022)}");
			Assert::AreEqual(5, obj1.getRowCount());

		}

		TEST_METHOD(TestListBaseDeletion) {
			//testing deletion
			HashListBase obj1;
			obj1.insertFunction("{(1, success, 20.12.2022)}");
			obj1.insertFunction("{(2, success, 20.12.2022), (3, success, 20.12.2022), (4, success, 20.12.2022), (5, success, 20.12.2022)}");
			// testing if we try to delete an element that does not exist
			obj1.deleteFunction("Delete FROM Sample0 WHERE ID >= 6");
			obj1.deleteFunction("Delete FROM Sample0 WHERE"); 
			obj1.deleteFunction("Delete FROM Sample0 WHERE ID 13243");
			obj1.deleteFunction("Delete FROM Sample0 WHERE (ID >= 5 AND Name != success) OR Date >= 21.12.2022");
			Assert::AreEqual(5, obj1.getRowCount());
			// testing when there is an element to be deleted
			obj1.deleteFunctionAll(); // that must delete all elements // this is called in case the string inside is just "Delete FROM TableName" // also clears all the data
			Assert::AreEqual(0, obj1.getRowCount());


			HashListBase obj2;
			obj2.insertFunction("{(1, success1, 20.12.2022)}");
			obj2.insertFunction("{(2, success2, 20.12.2022), (3, success3, 20.12.2022), (4, success4, 20.12.2022), (5, success5, 21.12.2022)}");
			obj2.deleteFunction("Delete FROM Sample0 WHERE ID >= 4 AND Date != 20.12.2022"); // must delete only the last element
			Assert::AreEqual(4, obj2.getRowCount());
			obj2.insertFunction("{(5, success, 20.12.2022)}");
			// they are again 5 elements however the following line should delete all but 1
			obj2.deleteFunction("Delete FROM Sample0 WHERE (ID >= 1 AND Name != success2) OR (ID >= 3 AND Name = success5)");
			Assert::AreEqual(1, obj2.getRowCount());
			obj2.insertFunction("{(1, success1, 20.12.2022), (3, success3, 20.12.2022), (4, success4, 20.12.2022), (5, success5, 21.12.2022)}");
			obj2.deleteFunction("Delete FROM Sample0 WHERE (((((ID >= 3)))) AND (Name != success5))"); // must delete only 2 elements
			Assert::AreEqual(3, obj2.getRowCount());
			// the logic in where clause is the same for the select so we are currently testing not only the deletion but also the WHERE -> functionality

		}
		
		TEST_METHOD(TestFunctionality) {
			DataBase obj1;
			obj1.DetermineFunction("Creatasd");
		}
	};
}
