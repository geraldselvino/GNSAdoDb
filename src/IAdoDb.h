/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* Interface for AdoDb class implementations
***********************************************************/
#pragma once

#include <string>

#import "../type_library/msado27.tlb" auto_rename auto_search

namespace GNSAdoDb{

    class CDbResult;

    class IAdoDb
    {
    public:
        virtual ~IAdoDb(){}

    public:
        virtual bool ConnectToDB() = 0;
        virtual bool Disconnect() = 0;
        virtual CDbResult* ExecuteQuery(const std::string& pQuery) = 0;
        virtual CDbResult* OpenSchema(ADODB::SchemaEnum pSchema) = 0;
        virtual std::string GetErrorMsg() = 0;
    };
}