/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* Interface for DbConnection class implementations
***********************************************************/
#pragma once

#include <string>

namespace GNSAdoDb{

    class IDbConnection
    {
    public:
        virtual ~IDbConnection(){}

    public:
        virtual std::string MakeConnStr() = 0;
        virtual std::string GetPass() = 0;
        virtual std::string GetUser() = 0;
    };
}