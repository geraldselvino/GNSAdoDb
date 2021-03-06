#include "GNSAdoDbFactory.h"
#include "SQLAdoDbFactory.h"
#include "MDBAdoDbFactory.h"

GNSAdoDb::IAdoDb* GNSAdoDb::GNSAdoDbFactory::getSqlAdoDb(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                                                         const std::string& pHost, const std::string& pPort)
{
    static AdoDbFactory* m_Factory;
    // Only one instance of the factory will run
    if(!m_Factory){
        m_Factory = new SQLAdoDbFactory();
    }
    return m_Factory->getInstance(pDatabase, pUserName, pPassword, pHost, pPort);
}

GNSAdoDb::IAdoDb* GNSAdoDb::GNSAdoDbFactory::getMdbAdoDb(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                                                         const std::string& pMDWPassword, const std::string& pMDBPassword)
{
    static AdoDbFactory* m_Factory; 
    // Only one instance of the factory will run
    if(!m_Factory){
        m_Factory = new MDBAdoDbFactory();
    }
    return m_Factory->getInstance(pDatabase, pMDW, pMDWUserID, pMDWPassword, pMDBPassword);
}