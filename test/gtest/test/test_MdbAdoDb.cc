#include "gtest/gtest.h"
#include "GNSAdoDbFactory.h"
#include "MDBAdoDbFactory.h"
#include "DbResult.h"

/**
 * Test for Microsoft Access (CMDBAdoDb)
 */

struct MdbAdoDbFixture: public ::testing::Test{
	virtual void SetUp(){
		f_AdoDb = GNSAdoDb::GNSAdoDbFactory::getMdbAdoDb("../TestAccessDb/test.mdb");
	}
	virtual void TearDown(){
		delete f_AdoDb;
	}
	GNSAdoDb::IAdoDb* f_AdoDb;
};

TEST_F(MdbAdoDbFixture, ConnectionMdb){
  bool ret = f_AdoDb->ConnectToDB();
  EXPECT_EQ(true, ret);
  ret = f_AdoDb->Disconnect();
  EXPECT_EQ(true, ret);
}

TEST_F(MdbAdoDbFixture, QueryMdb){
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

TEST_F(MdbAdoDbFixture, SchemaMdb){
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

TEST_F(MdbAdoDbFixture, ErrorMdb){
  bool ret = f_AdoDb->ConnectToDB();
  EXPECT_EQ(true, ret);
  std::string err = f_AdoDb->GetErrorMsg();
  EXPECT_EQ("", err);
  ret = f_AdoDb->Disconnect();
  EXPECT_EQ(true, ret);
}