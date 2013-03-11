#include "SQLDbConnection.h"
#include "SQLDbConnectionImpl.h"

/**
 * Definition of the Handle class(CSQLDbConnection)
 */

GNSAdoDb::CSQLDbConnection::CSQLDbConnection(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                                             const std::string& pHost, const std::string& pPort)
: pImplSQLDbConnection(new CSQLDbConnectionImpl(pDatabase, pUserName, pPassword, pHost, pPort))
{
}

GNSAdoDb::CSQLDbConnection::~CSQLDbConnection()
{
    delete pImplSQLDbConnection;
}

std::string GNSAdoDb::CSQLDbConnection::MakeConnStr()
{
    return pImplSQLDbConnection->MakeConnStr();
}

std::string GNSAdoDb::CSQLDbConnection::GetPass()
{
    return pImplSQLDbConnection->GetPass();
}


std::string GNSAdoDb::CSQLDbConnection::GetUser()
{
    return pImplSQLDbConnection->GetUser();
}

/**
 * Definition of the Body class(CSQLDbConnectionImpl)
 */

GNSAdoDb::CSQLDbConnectionImpl::CSQLDbConnectionImpl(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                                                     const std::string& pHost, const std::string& pPort)
: m_Database(pDatabase),
  m_UserName(pUserName),
  m_Password(pPassword),
  m_Host(pHost),
  m_Port(pPort)
{
}

GNSAdoDb::CSQLDbConnectionImpl::~CSQLDbConnectionImpl()
{
}

std::string GNSAdoDb::CSQLDbConnectionImpl::MakeConnStr()
{
    m_ConnectionString = "Provider=sqloledb;Persist Security Info=true;Initial Catalog=" + m_Database + 
                         ";User ID=" + m_UserName + ";Password=" + m_Password + ";Data Source=" + m_Host;
    if(m_Port.length()>0){ m_ConnectionString += "," + m_Port; }

    return m_ConnectionString;
}

std::string GNSAdoDb::CSQLDbConnectionImpl::GetPass()
{
    return  m_Password;
}


std::string GNSAdoDb::CSQLDbConnectionImpl::GetUser()
{
    return  m_UserName;
}