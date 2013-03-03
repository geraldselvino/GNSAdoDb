/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the handle class to the body (CMDBAdoDbImpl)
***********************************************************/
#pragma once

#include <string>
#include "IAdoDb.h"

#import "../type_library/msado27.tlb" auto_rename auto_search

namespace GNSAdoDb{

    class CDbResult;
    class CMDBAdoDbImpl;

    class CMDBAdoDb : public IAdoDb
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
        CMDBAdoDb(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                  const std::string& pMDWPassword, const std::string& pMDBPassword);

        virtual ~CMDBAdoDb();

    public:
        bool ConnectToDB();
        bool Disconnect();
        CDbResult ExecuteQuery(const std::string& pQuery);
        CDbResult OpenSchema(ADODB::SchemaEnum pSchema);
        std::string GetErrorMsg();

    private:
        CMDBAdoDbImpl* pImplMDBAdoDb;

    };
}