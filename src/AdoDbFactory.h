/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* Abstract Factory class, use as a base class for the 
* implementation factories.
***********************************************************/
#pragma once

#include <string>

namespace GNSAdoDb{
    /**
     * Return type of the factory method,
     * forward declared since we don't need
	 * to know its layout, we just use a pointer
	 * of its type
     */   
    class IAdoDb;

    class AdoDbFactory
    {
    public:
        /**
         * Virtual, so that inheriter can destroy it 
         * using this class' pointer
         */
        virtual ~AdoDbFactory(){}

    public:
        /**
         * Non-Virtual Interface/Template method
         * which calls the Instance() method from
         * the implementation factories
         */
        IAdoDb* getInstance(const std::string& pParam1, const std::string& pParam2, const std::string& pParam3,
                            const std::string& pParam4, const std::string& pParam5)
        {
            return Instance(pParam1, pParam2, pParam3, pParam4, pParam5);
        }

    private:
        /**
         * Pure virtual method to be implemented
         * by the implementation factories, this is
         * to simulate a virtual constructor(idiom)
         */
        virtual IAdoDb* Instance(const std::string&, const std::string&, const std::string&,
                                 const std::string&, const std::string&) = 0;
    };
}
