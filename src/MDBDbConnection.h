/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the handle class to the body (CMDBDbConnectionImpl)
***********************************************************/
#pragma once

#include <string>
#include "IDbConnection.h"

namespace GNSAdoDb{

    class CMDBDbConnectionImpl;

    class CMDBDbConnection: public IDbConnection
    {
    public:
        CMDBDbConnection(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, const std::string& pMDWPassword, const std::string& pMDBPassword);
        virtual ~CMDBDbConnection();

    public:
        std::string MakeConnStr();
        std::string GetPass();
        std::string GetUser();

    private:
        CMDBDbConnectionImpl* pImplMDBDbConnection;
    };
}