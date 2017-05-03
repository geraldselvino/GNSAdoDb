GNSAdoDb [C++ ActiveX Data Object wrapper]
==========================================
Library that abstracts and simplify ADO programming in native C++,
making it as easy as ADO programming in Visual Basic.

Requirement
===============================
Visual Studio  
MSADO type library (included in type_library folder)  
Windows  

Sample Usage
===============================
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

License
===============================
Copyright (c) 2009, Gerald Selvino <gerald.selvino@protonmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
