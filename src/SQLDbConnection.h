/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the handle class to the body (CSQLDbConnectionImpl)
***********************************************************/
#pragma once

#include <string>
#include "IDbConnection.h"

namespace GNSAdoDb{

    class CSQLDbConnectionImpl;

    class CSQLDbConnection: public IDbConnection
    {
    public:
        CSQLDbConnection(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                         const std::string& pHost, const std::string& pPort);
        virtual ~CSQLDbConnection();

    public:
        std::string MakeConnStr();
        std::string GetPass();
        std::string GetUser();

    private:
        CSQLDbConnectionImpl* pImplSQLDbConnection;
    };
}