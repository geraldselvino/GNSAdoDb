GNSAdoDb [C++ ActiveX Data Object wrapper]
==========================================
Library that abstracts and simplify ADO programming in native C++,
making it as easy as ADO programming in Visual Basic.

Requirement
===========
Visual Studio  
MSADO type library (included in type_library folder)  
Windows  

Sample Usage
============
**Note:** Check the unit test solution(test/gtest/msvc/gtest.sln) to see more usage coverage
```c++
//[SQL server]
//initialize  
GNSAdoDb::IAdoDb* adodb = GNSAdoDb::GNSAdoDbFactory::getSqlAdoDb("dbname", "user", "pass", "host", "port");
//connect
adodb->ConnectToDB();
//standard query
GNSAdoDb::CDbResult* dbresult = NULL;
dbresult = adodb->ExecuteQuery("select * from testtable");
int recCount = dbresult->GetRecordCount();
std::cout << dbresult->Get("fname");
//schema info query
GNSAdoDb::CDbResult* dbresultschema = NULL;
dbresultschema = adodb->OpenSchema(ADODB::adSchemaColumns);
int recCount = dbresultschema->GetRecordCount();
//close connection
bool ret = adodb->Disconnect();
  
//[MS Access]
//initialize
GNSAdoDb::IAdoDb* adodb = GNSAdoDb::GNSAdoDbFactory::getMdbAdoDb("../test/test.mdb");
//connect
adodb->ConnectToDB();
//standard query
GNSAdoDb::CDbResult* dbresult = NULL;
dbresult = adodb->ExecuteQuery("select * from testtable");
int recCount = dbresult->GetRecordCount();
std::cout << dbresult->Get("fname");
//schema info query
GNSAdoDb::CDbResult* dbresultschema = NULL;
dbresultschema = adodb->OpenSchema(ADODB::adSchemaColumns);
int recCount = dbresultschema->GetRecordCount();
//close connection
bool = adodb->Disconnect();
```
