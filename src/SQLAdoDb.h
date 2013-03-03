/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the handle class to the body (CSQLDbAdoDbImpl)
***********************************************************/
#pragma once

#include <string>
#include "IAdoDb.h"

#import "../type_library/msado27.tlb" auto_rename auto_search

namespace GNSAdoDb{

    class CDbResult;
    class CSQLAdoDbImpl;

    class CSQLAdoDb : public IAdoDb
    {
    public:
        /**
         * This is the ADO DB class for connecting to SQL Server
         *
         * Instantiate this, and use AdoDb methods to connect, and execute query
         * Use ConnectToDB(); to establish connection, then use ExecuteQuery(string);
         * to issue an SQL command, return will be as CDbResult.
         *
         * @param pDatabase : database name
         * @param pUserName : Sql Server user name
         * @param pPassword : Sql Server password
         * @param pHost : hostname
         * @param pPort : Sql Server port
         */
        CSQLAdoDb(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                  const std::string& pHost, const std::string& pPort);

        virtual ~CSQLAdoDb();

    public:
        bool ConnectToDB();
        bool Disconnect();
        CDbResult ExecuteQuery(const std::string& pQuery);
        CDbResult OpenSchema(ADODB::SchemaEnum pSchema);
        std::string GetErrorMsg();

    private:
        CSQLAdoDbImpl* pImplSQLAdoDb;

    };
}