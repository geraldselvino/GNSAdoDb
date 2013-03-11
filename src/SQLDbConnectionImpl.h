/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is the implementation class of CSQLDbConnection, used
* by CSQLAdoDb(Impl) to connect to Microsof SQL Server
***********************************************************/
#pragma once

#include <string>
#include "IDbConnection.h"

namespace GNSAdoDb{

    class CSQLDbConnectionImpl: public IDbConnection
    {
    public:
        CSQLDbConnectionImpl(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                             const std::string& pHost, const std::string& pPort);
        virtual ~CSQLDbConnectionImpl();

    public:
        std::string MakeConnStr();
        std::string GetPass();
        std::string GetUser();

    private:
        std::string m_ConnectionString;
        std::string m_Database;
        std::string m_Host;
        std::string m_UserName;
        std::string m_Password;
        std::string m_Port;
    };
}