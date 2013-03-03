/**********************************************************
* Copyright (c) 2013, Gerald Selvino <geraldsv@outlook.com>
* All rights reserved.
*
* This class encapsulates the COM Recordset, used to contain
* the return value of the ExecuteQuery in AdoDb. It exposed
* standard functions supported by COM Recordset, it also adds
* a function to put all the contents of the Recordset
* into an STL vector.
***********************************************************/
#pragma once

#include <vector>
#include <string>

#import "../type_library/msado27.tlb" auto_rename auto_search

namespace GNSAdoDb{

    class CDbResult
    {
    public:
        CDbResult();
        virtual ~CDbResult();
        CDbResult& operator=(const int& pResultSet);
        CDbResult(const int& pResultSet);

    public:
        bool Get(const std::string& FieldName, int& FieldValue);
        bool Get(const std::string& FieldName, double& FieldValue);
        std::string Get(const std::string& FieldName);
        int IsEof();
        HRESULT MoveFirst();
        HRESULT MoveLast();
        HRESULT MoveNext();
        HRESULT MovePrevious();
        int GetRecordCount();
        int GetFieldCount();
        bool TransformToVector(std::vector<std::vector<std::string> >& pTransformed);

    public:
        ADODB::_RecordsetPtr GetRecordset();
        void SetRecordset(ADODB::_RecordsetPtr pRecordSet);
        std::string GetErrorMsg();

    private:
        ADODB::_RecordsetPtr m_RecordSet;
        std::string m_ErrorMessage;
    };
}