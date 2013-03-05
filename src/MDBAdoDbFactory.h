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
    : m_AdoDb(NULL)
    {
    public:
        /**
         * Virtual, so that inheriter can destroy it 
         * using this class' pointer
         */
        virtual ~MDBAdoDbFactory(){
            delete m_AdoDb;
        }

    private:
        /**
         * Implements the Instance() pure virtual
         * method from AdoDbFactory, which returns
         * a pointer to an instance of CMDBAdoDb
         */
        virtual IAdoDb* Instance(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                                 const std::string& pMDWPassword, const std::string& pMDBPassword)
        {
            m_AdoDb = new CMDBAdoDb(pDatabase, pMDW, pMDWUserID, pMDWPassword, pMDBPassword);
            return m_AdoDb;
        }

    private:
        IAdoDb* m_AdoDb;

    };
}