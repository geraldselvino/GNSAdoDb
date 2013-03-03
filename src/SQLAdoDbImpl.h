/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the implementation class of CSQLAdoDb, use to
* interface with Microsoft SQL Server
***********************************************************/
#pragma once

#include <string>
#include "IAdoDb.h"

#import "../type_library/msado27.tlb" auto_rename auto_search

namespace GNSAdoDb{

    class CDbResult;
    class IDbConnection;

    class CSQLAdoDbImpl : public IAdoDb
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
        CSQLAdoDbImpl(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                  const std::string& pHost, const std::string& pPort);

        virtual ~CSQLAdoDbImpl();

    public:
        bool ConnectToDB();
        bool Disconnect();
        CDbResult ExecuteQuery(const std::string& pQuery);
        CDbResult OpenSchema(ADODB::SchemaEnum pSchema);
        std::string GetErrorMsg();

    protected:
        ADODB::_ConnectionPtr m_Connection;

    private:
        IDbConnection* m_ConnectionInfo;
        std::string m_ErrorMessage;

    };
}