#include <stdafx.h> //include to allow precompiled header in Visual Studio
#include "SQLAdoDb.h"
#include "SQLAdoDbImpl.h"
#include "SQLDbConnection.h"
#include "DbResult.h"

/**
 * Definition of the Handle class(CSQLAdoDb)
 */

GNSAdoDb::CSQLAdoDb::CSQLAdoDb(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                               const std::string& pHost, const std::string& pPort)
: pImplSQLAdoDb(new CSQLAdoDbImpl(pDatabase, pUserName, pPassword, pHost, pPort))
{
}

GNSAdoDb::CSQLAdoDb::~CSQLAdoDb()
{
    delete pImplSQLAdoDb;
}

bool GNSAdoDb::CSQLAdoDb::ConnectToDB()
{
    return pImplSQLAdoDb->ConnectToDB();
}

bool GNSAdoDb::CSQLAdoDb::Disconnect()
{
    return pImplSQLAdoDb->Disconnect();
}

GNSAdoDb::CDbResult GNSAdoDb::CSQLAdoDb::ExecuteQuery(const std::string& pQuery)
{
    return pImplSQLAdoDb->ExecuteQuery(pQuery);
}

GNSAdoDb::CDbResult GNSAdoDb::CSQLAdoDb::OpenSchema(ADODB::SchemaEnum pSchema)
{
    return pImplSQLAdoDb->OpenSchema(pSchema);
}

std::string GNSAdoDb::CSQLAdoDb::GetErrorMsg()
{
    return pImplSQLAdoDb->GetErrorMsg();
}

/**
 * Definition of the Body class(CSQLAdoDbImpl)
 */

GNSAdoDb::CSQLAdoDbImpl::CSQLAdoDbImpl(const std::string& pDatabase, const std::string& pUserName, const std::string& pPassword, 
                             const std::string& pHost, const std::string& pPort)
: m_Connection(NULL),
  m_ConnectionInfo(new CSQLDbConnection(pDatabase, pUserName, pPassword, pHost, pPort))
{
    ::CoInitialize(NULL);
}

GNSAdoDb::CSQLAdoDbImpl::~CSQLAdoDbImpl()
{
    delete m_ConnectionInfo;
    ::CoUninitialize();
}

bool GNSAdoDb::CSQLAdoDbImpl::ConnectToDB()
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

bool GNSAdoDb::CSQLAdoDbImpl::Disconnect()
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

GNSAdoDb::CDbResult GNSAdoDb::CSQLAdoDbImpl::ExecuteQuery(const std::string& pQuery)
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

GNSAdoDb::CDbResult GNSAdoDb::CSQLAdoDbImpl::OpenSchema(ADODB::SchemaEnum pSchema)
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

std::string GNSAdoDb::CSQLAdoDbImpl::GetErrorMsg()
{
    return m_ErrorMessage;
}
