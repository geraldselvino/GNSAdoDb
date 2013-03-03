#include <stdafx.h> //include to allow precompiled header in Visual Studio
#include "MDBDbConnection.h"
#include "MDBDbConnectionImpl.h"

/**
 * Definition of the Handle class(CMDBDbConnection)
 */

GNSAdoDb::CMDBDbConnection::CMDBDbConnection(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                                             const std::string& pMDWPassword, const std::string& pMDBPassword)
: pImplMDBDbConnection(new CMDBDbConnectionImpl(pDatabase, pMDW, pMDWUserID, pMDWPassword, pMDBPassword))
{
}

GNSAdoDb::CMDBDbConnection::~CMDBDbConnection()
{
    delete pImplMDBDbConnection;
}

std::string GNSAdoDb::CMDBDbConnection::MakeConnStr()
{
    return pImplMDBDbConnection->MakeConnStr();
}

std::string GNSAdoDb::CMDBDbConnection::GetPass()
{
    return pImplMDBDbConnection->GetPass();
}

std::string GNSAdoDb::CMDBDbConnection::GetUser()
{
    return pImplMDBDbConnection->GetUser();
}

/**
 * Definition of the Body class(CMDBDbConnectionImpl)
 */

GNSAdoDb::CMDBDbConnectionImpl::CMDBDbConnectionImpl(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                                           const std::string& pMDWPassword, const std::string& pMDBPassword)
: m_Database(pDatabase),
  m_MDW(pMDW),
  m_MDWUserID(pMDWUserID),
  m_MDWPassword(pMDWPassword),
  m_MDBPassword(pMDBPassword)
{
}

GNSAdoDb::CMDBDbConnectionImpl::~CMDBDbConnectionImpl()
{
}

std::string GNSAdoDb::CMDBDbConnectionImpl::MakeConnStr()
{
    m_ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + m_Database;
    if(m_MDW.length()>0){m_ConnectionString+=";Jet OLEDB: System Database=" + m_MDW;}
    if(m_MDWUserID.length()>0){m_ConnectionString+=";User Id=" + m_MDWUserID;}
    if(m_MDWPassword.length()>0){m_ConnectionString+=";Password=" + m_MDWPassword;}
    if(m_MDBPassword.length()>0){m_ConnectionString+=";Jet OLEDB: Database Password=" + m_MDBPassword;}

    return m_ConnectionString;
}

std::string GNSAdoDb::CMDBDbConnectionImpl::GetPass()
{
    return  m_MDWUserID;
}


std::string GNSAdoDb::CMDBDbConnectionImpl::GetUser()
{
    return  m_MDWPassword;
}