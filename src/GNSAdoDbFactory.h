/**********************************************************
* Copyright (c) 2009, Gerald Selvino
* <gerald.selvino@protonmail.com> All rights reserved.
*
* The main factory, use to obtain an instance of 
* the AdoDb classes
***********************************************************/
#pragma once

#include <string>

namespace GNSAdoDb{

    class IAdoDb;
    class AdoDbFactory;

    class GNSAdoDbFactory
    {
    public:
        /**
         * The factory methods, which returns
         * a pointer to the instance of an
         * AdoDb class.
         */

        /**Factory method for SQL server*/
        static IAdoDb* getSqlAdoDb(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                                   const std::string& pHost, const std::string& pPort="");
        /**Factory method for Microsoft Access*/
        static IAdoDb* getMdbAdoDb(const std::string& pDatabase, const std::string& pMDW="", const std::string& pMDWUserID="", 
                                   const std::string& pMDWPassword="", const std::string& pMDBPassword=""); 

    private:
        /**
         * Make the default constructor, destructor, copy constructor,
         * assignment operator private, so that this factory
         * class cannot be instantiated, copied or assigned (null object pattern)
         */
        GNSAdoDbFactory();
        ~GNSAdoDbFactory();
        GNSAdoDbFactory(const GNSAdoDbFactory& other);
        GNSAdoDbFactory& operator=(const GNSAdoDbFactory& other);
    };
}