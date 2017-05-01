/**********************************************************
* Copyright (c) 2009, Gerald Selvino
* <gerald.selvino@protonmail.com> All rights reserved.
*
* This is the implementation class of CMDBDbConnection, used
* by CMDBAdoDb(Impl) to connect to Microsof Access database
***********************************************************/
#pragma once

#include <string>
#include "IDbConnection.h"

namespace GNSAdoDb{

    class CMDBDbConnectionImpl: public IDbConnection
    {
    public:
        CMDBDbConnectionImpl(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                             const std::string& pMDWPassword, const std::string& pMDBPassword);
        virtual ~CMDBDbConnectionImpl();

    public:
        std::string MakeConnStr();
        std::string GetPass();
        std::string GetUser();

    private:
        std::string m_ConnectionString;
        std::string m_Database;
        std::string m_MDW;
        std::string m_MDWUserID;
        std::string m_MDWPassword;
        std::string m_MDBPassword;
    };
}