/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the implementation class of CMDBAdoDb, use to
* interface with Microsoft Access database
***********************************************************/
#pragma once

#include <string>
#include "IAdoDb.h"

#import "../type_library/msado27.tlb" auto_rename auto_search

namespace GNSAdoDb{

    class CDbResult;
    class IDbConnection;

    class CMDBAdoDbImpl : public IAdoDb
    {
    public:
        /**
         * This is the ADO DB class for connecting to MS Access
         *
         * Instantiate this, and use AdoDb methods to connect, and execute query
         * Use ConnectToDB(); to establish connection, then use ExecuteQuery(string);
         * to issue an SQL command, return will be as CDbResult.
         *
         * @param pDatabase : database name
         * @param pMDW : MDW file
         * @param pMDWUserID : Workgroup User Id
         * @param pMDWPassword : Workgroup password
         * @param pMDBPassword : MS Access password
         */
        CMDBAdoDbImpl(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                      const std::string& pMDWPassword, const std::string& pMDBPassword);

        virtual ~CMDBAdoDbImpl();

    public:
        bool ConnectToDB();
        bool Disconnect();
        CDbResult* ExecuteQuery(const std::string& pQuery);
        CDbResult* OpenSchema(ADODB::SchemaEnum pSchema);
        std::string GetErrorMsg();

    protected:
        ADODB::_ConnectionPtr m_Connection;

    private:
        IDbConnection* m_ConnectionInfo;
        std::string m_ErrorMessage;

    };
}