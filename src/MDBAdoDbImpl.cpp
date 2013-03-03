#include <stdafx.h> //include to allow precompiled header in Visual Studio
#include "MDBAdoDb.h"
#include "MDBAdoDbImpl.h"
#include "MDBDbConnection.h"
#include "DbResult.h"

/**
 * Definition of the Handle class(CMDBAdoDb)
 */

GNSAdoDb::CMDBAdoDb::CMDBAdoDb(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                               const std::string& pMDWPassword, const std::string& pMDBPassword)
: pImplMDBAdoDb(new CMDBAdoDbImpl(pDatabase, pMDW, pMDWUserID, pMDWPassword, pMDBPassword))
{
}

GNSAdoDb::CMDBAdoDb::~CMDBAdoDb()
{
    delete pImplMDBAdoDb;
}

bool GNSAdoDb::CMDBAdoDb::ConnectToDB()
{
    return pImplMDBAdoDb->ConnectToDB();
}

bool GNSAdoDb::CMDBAdoDb::Disconnect()
{
    return pImplMDBAdoDb->Disconnect();
}

GNSAdoDb::CDbResult GNSAdoDb::CMDBAdoDb::ExecuteQuery(const std::string& pQuery)
{
    return pImplMDBAdoDb->ExecuteQuery(pQuery);
}

GNSAdoDb::CDbResult GNSAdoDb::CMDBAdoDb::OpenSchema(ADODB::SchemaEnum pSchema)
{
    return pImplMDBAdoDb->OpenSchema(pSchema);
}

std::string GNSAdoDb::CMDBAdoDb::GetErrorMsg()
{
    return pImplMDBAdoDb->GetErrorMsg();
}

/**
 * Definition of the Body class(CMDBAdoDbImpl)
 */

GNSAdoDb::CMDBAdoDbImpl::CMDBAdoDbImpl(const std::string& pDatabase, const std::string& pMDW, const std::string& pMDWUserID, 
                             const std::string& pMDWPassword, const std::string& pMDBPassword)
: m_Connection(NULL),
  m_ConnectionInfo(new CMDBDbConnection(pDatabase, pMDW, pMDWUserID, pMDWPassword, pMDBPassword))
{
    ::CoInitialize(NULL);
}

GNSAdoDb::CMDBAdoDbImpl::~CMDBAdoDbImpl()
{
    delete m_ConnectionInfo;
    ::CoUninitialize();
}

bool GNSAdoDb::CMDBAdoDbImpl::ConnectToDB()
{
    try{
        HRESULT l_hresult;
        l_hresult = m_Connection.CreateInstance( __uuidof( ADODB::Connection ) );
        m_Connection->CursorLocation = ADODB::adUseClient;
        m_Connection->Open(m_ConnectionInfo->MakeConnStr().c_str(), m_ConnectionInfo->GetUser().c_str(), m_ConnectionInfo->GetPass().c_str(), NULL);
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return false;
    }

    return true;
}

bool GNSAdoDb::CMDBAdoDbImpl::Disconnect()
{
    try{
        m_Connection->Close();
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return false;
    }

    return true;
}

GNSAdoDb::CDbResult GNSAdoDb::CMDBAdoDbImpl::ExecuteQuery(const std::string& pQuery)
{
    CDbResult t_resultset;
    try{
        t_resultset.SetRecordset(m_Connection->Execute(pQuery.c_str(),NULL,1));
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return NULL;
    }

    return t_resultset;
}

GNSAdoDb::CDbResult GNSAdoDb::CMDBAdoDbImpl::OpenSchema(ADODB::SchemaEnum pSchema)
{
    CDbResult t_resultset;
    try{
        t_resultset.SetRecordset(m_Connection->OpenSchema(pSchema));
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return NULL;
    }

    return t_resultset;
}

std::string GNSAdoDb::CMDBAdoDbImpl::GetErrorMsg()
{
    return m_ErrorMessage;
}
