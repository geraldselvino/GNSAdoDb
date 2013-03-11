#include "gtest/gtest.h"
#include "GNSAdoDbFactory.h"
#include "SQLAdoDbFactory.h"
#include "DbResult.h"

/**
 * Test for Microsoft SQL Server (CSQLAdoDb)
 */

struct SqlAdoDbFixture: public ::testing::Test{
	virtual void SetUp(){
		f_AdoDb = GNSAdoDb::GNSAdoDbFactory::getSqlAdoDb("testdb", "sa", "12345", "GERALD-F1B7F084\\SQLEXPRESS");
	}
	virtual void TearDown(){
		delete f_AdoDb;
	}
	GNSAdoDb::IAdoDb* f_AdoDb;
};

TEST_F(SqlAdoDbFixture, ConnectionSql){
  bool ret = f_AdoDb->ConnectToDB();
  EXPECT_EQ(true, ret);
  ret = f_AdoDb->Disconnect();
  EXPECT_EQ(true, ret);
}

TEST_F(SqlAdoDbFixture, QuerySql){
  bool ret = f_AdoDb->ConnectToDB();
  EXPECT_EQ(true, ret);
  GNSAdoDb::CDbResult* f_DbResult = NULL;
  f_DbResult = f_AdoDb->ExecuteQuery("select * from testtable");
  EXPECT_TRUE(f_DbResult != NULL);
  int recCount = f_DbResult->GetRecordCount();
  EXPECT_GT(recCount, 0);
  //std::cout<<f_DbResult->Get("fname");
  ret = f_AdoDb->Disconnect();
  EXPECT_EQ(true, ret);
  delete f_DbResult;
}

TEST_F(SqlAdoDbFixture, SchemaSql){
  bool ret = f_AdoDb->ConnectToDB();
  EXPECT_EQ(true, ret);
  GNSAdoDb::CDbResult* f_DbResult = NULL;
  f_DbResult = f_AdoDb->OpenSchema(ADODB::adSchemaColumns);
  EXPECT_TRUE(f_DbResult != NULL);
  int recCount = f_DbResult->GetRecordCount();
  EXPECT_GT(recCount, 0);
  ret = f_AdoDb->Disconnect();
  EXPECT_EQ(true, ret);
  delete f_DbResult;
}

TEST_F(SqlAdoDbFixture, ErrorSql){
  bool ret = f_AdoDb->ConnectToDB();
  EXPECT_EQ(true, ret);
  std::string err = f_AdoDb->GetErrorMsg();
  EXPECT_EQ("", err);
  ret = f_AdoDb->Disconnect();
  EXPECT_EQ(true, ret);
}