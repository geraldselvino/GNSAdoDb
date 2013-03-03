#include <stdafx.h> //include to allow precompiled header in Visual Studio
#include "DbResult.h"

GNSAdoDb::CDbResult::CDbResult()
: m_RecordSet(NULL)
{
}

GNSAdoDb::CDbResult::~CDbResult()
{
}

GNSAdoDb::CDbResult::CDbResult(const int& pResultSet)
{
    *this = pResultSet;
}

GNSAdoDb::CDbResult& GNSAdoDb::CDbResult::operator=(const int& pResultSet)
{
    m_RecordSet = pResultSet;
    return *this;
}

bool GNSAdoDb::CDbResult::Get(const std::string& FieldName, int& FieldValue)
{
    try{
        _variant_t  l_Value;
        l_Value = m_RecordSet->Fields->GetItem(FieldName.c_str())->GetValue();
        FieldValue = l_Value.intVal;
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return false;
    }

    return true;
}

bool GNSAdoDb::CDbResult::Get(const std::string& FieldName, double& FieldValue)
{
    try{
        _variant_t  l_Value;
        l_Value = m_RecordSet->Fields->GetItem(FieldName.c_str())->GetValue();
        FieldValue = l_Value.dblVal;
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return false;
    }

    return true;
}

std::string GNSAdoDb::CDbResult::Get(const std::string& FieldName)
{
    try {
        _variant_t  l_Value;
        l_Value = m_RecordSet->Fields->GetItem(FieldName.c_str())->GetValue();
        _bstr_t l_bstr = static_cast<_bstr_t>(l_Value.GetVARIANT());

        std::string l_return(static_cast<const char*>(l_bstr));
        //l_return.Format("%s", (LPCTSTR)l_bstr);
        return l_return;
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return NULL;
    }
}

int GNSAdoDb::CDbResult::IsEof()
{
    int l_rseof;
    if(!m_RecordSet){
        return -1;
    }
    try{
        l_rseof = m_RecordSet->Get__EOF()/*->EndOfFile*/;
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        return NULL;
    }

    return l_rseof;
}

HRESULT GNSAdoDb::CDbResult::MoveFirst()
{
    HRESULT l_hresult;
    try{
        l_hresult = m_RecordSet->MoveFirst();
    }
    catch(_com_error &e)
    {
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        m_RecordSet = NULL;
        return -2;
    }

    return l_hresult;
}

HRESULT GNSAdoDb::CDbResult::MoveLast()
{
    HRESULT l_hresult;
    try{
        l_hresult = m_RecordSet->MoveLast();
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        m_RecordSet = NULL;
        return -2;
    }

    return l_hresult;
}

HRESULT GNSAdoDb::CDbResult::MoveNext()
{
    HRESULT l_hresult;
    try{
        l_hresult = m_RecordSet->MoveNext();
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        m_RecordSet = NULL;
        return -2;
    }

    return l_hresult;
}

HRESULT GNSAdoDb::CDbResult::MovePrevious()
{
    HRESULT l_hresult;
    try{
        l_hresult = m_RecordSet->MovePrevious();
    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        m_RecordSet = NULL;
        return -2;
    }

    return l_hresult;
}

std::string GNSAdoDb::CDbResult::GetErrorMsg()
{
    return m_ErrorMessage;
}

bool GNSAdoDb::CDbResult::TransformToVector(std::vector<std::vector<std::string> >& pTransformed)
{
    _variant_t l_collection;
    try{
        MoveFirst();
        l_collection = m_RecordSet->GetRows(GetRecordCount());

        long l_Ubound;
        HRESULT hr = SafeArrayGetUBound(l_collection.parray, 2, &l_Ubound); 

        if (hr == S_OK){
            if ((GetRecordCount()>l_Ubound + 1) && (!(m_RecordSet->Get__EOF()/*->EndOfFile*/))){
                return false;
            }
            else{
                SAFEARRAY *pSafeArray = l_collection.parray;
                long l_StartIndex = 0;
                long l_EndIndex = 0;
                long l_idx = 0;
                HRESULT l_hr;

                if((l_hr = SafeArrayGetLBound(pSafeArray, 2, &l_StartIndex)) != S_OK)return false;

                if((l_hr = SafeArrayGetUBound(pSafeArray, 2, &l_EndIndex)) != S_OK)return false;

                VARIANT l_variant;
                long l_ColumnCount = GetFieldCount();
                std::vector<std::string> m_Data;

                for(int idx = l_StartIndex; idx <= l_EndIndex; idx++){    
                    for(int i = 0; i < l_ColumnCount; i++){
                        long t_index[2] = {i, idx};
                        l_hr = SafeArrayGetElement(pSafeArray, t_index, &l_variant);

                        if(SUCCEEDED(l_hr)){
                            _bstr_t l_bstr = static_cast<_bstr_t>(l_variant);        
                            m_Data.push_back(static_cast<const char*>(l_bstr));
                        }
                        else{
                            return false;
                        }
                    }
                    pTransformed.push_back(m_Data);
                    m_Data.clear();
                }
                return true;   
            }
        }
        else{
            m_ErrorMessage = "Unable to Get the Array's Upper Bound";
            return false;
        }

    }
    catch(_com_error &e){
        m_ErrorMessage = reinterpret_cast<const char*>(e.ErrorMessage());
        m_RecordSet = NULL;
        return false;
    }
}

int GNSAdoDb::CDbResult::GetRecordCount()
{
    return (m_RecordSet->RecordCount);
}

int GNSAdoDb::CDbResult::GetFieldCount()
{
    return (m_RecordSet->Fields->Count);
}

ADODB::_RecordsetPtr GNSAdoDb::CDbResult::GetRecordset()
{
    return m_RecordSet;
}

void GNSAdoDb::CDbResult::SetRecordset(ADODB::_RecordsetPtr pRecordSet)
{
    m_RecordSet = pRecordSet;
}