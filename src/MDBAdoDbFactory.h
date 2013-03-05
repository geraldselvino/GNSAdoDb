/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is a factory class implementation for CMDBAdoDb
***********************************************************/
#pragma once

#include "AdoDbFactory.h"
#include "MDBAdoDb.h"

namespace GNSAdoDb{

    class MDBAdoDbFactory: public AdoDbFactory
    {
    public:
        /**
         * Virtual, so that inheriter can destroy it 
         * using this class' pointer
         */
        virtual ~MDBAdoDbFactory(){}

    private:
        /**
         * Implements the Instance() pure virtual
         * method from AdoDbFactory, which returns
         * a pointer to an instance of CMDBAdoDb
         */
        virtual IAdoDb* Instance(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                                 const std::string& pMDWPassword, const std::string& pMDBPassword)
        {
            return new CMDBAdoDb(pDatabase, pMDW, pMDWUserID, pMDWPassword, pMDBPassword);
        }
    };
}