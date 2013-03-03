/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This is a factory class implementation for CSQLAdoDb
***********************************************************/
#pragma once

#include "AdoDbFactory.h"
#include "SQLAdoDb.h"

namespace GNSAdoDb{

    class SQLAdoDbFactory: public AdoDbFactory
    {
    public:
        /**
         * Virtual, so that inheriter can destroy it 
         * using this class' pointer
         */
        virtual ~SQLAdoDbFactory(){
			delete m_AdoDb;
		}

    private:
        /**
         * Implements the Instance() pure virtual
         * method from AdoDbFactory, which returns
         * a pointer to an instance of CSQLAdoDb
         */
        virtual IAdoDb* Instance(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                                 const std::string& pHost, const std::string& pPort)
        {
            m_AdoDb = new CSQLAdoDb(pDatabase, pUserName, pPassword, pHost, pPort);
			return m_AdoDb;
        }

	private:
		IAdoDb* m_AdoDb;

    };
}