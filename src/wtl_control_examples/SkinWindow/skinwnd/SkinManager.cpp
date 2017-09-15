// SkinManager.cpp: implementation of the CSkinManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinManager.h"

CSkinManager* CSkinManager::m_pInstance;
CIni CSkinManager::m_skinINI;
CString CSkinManager::m_pszCurrentSkin;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinManager::CSkinManager()
{
}

CSkinManager::~CSkinManager()
{
}
//////////////////////////////////////////////////////////////////////////
//
//  Init : ��ʼ��ʵ���������֤Ψһ��
//
//  ���� :
//      lpctSkinName - Ϊ��ʱ������Ĭ��Ƥ����\\Skin\\Default\\theme.ini��
//                   - ��Ϊ��ʱ������ָ����Ƥ��
//
//  ����ֵ : ʵ��ָ��
//
//////////////////////////////////////////////////////////////////////////
CSkinManager* CSkinManager::Init(LPCTSTR lpctSkinName/* = NULL*/)
{
    if (m_pInstance == NULL) {
        CString pszSkinFilePath(_T("Default"));
        m_pInstance = new CSkinManager;

        if (lpctSkinName != NULL && _tcslen(lpctSkinName) != 0)
            pszSkinFilePath = lpctSkinName;

        m_pszCurrentSkin = pszSkinFilePath;
        pszSkinFilePath = g_pszModulePath + _T("Skin\\") + pszSkinFilePath + _T("\\theme.ini");
        m_skinINI.SetPathName(pszSkinFilePath);
    }

    return m_pInstance;
}
//////////////////////////////////////////////////////////////////////////
//
//  ChangeSkin : ����Ƥ������
//
//  ���� :
//      lpctSkinName - Ƥ�����ƣ���Ƥ���ļ�������
//
//  ����ֵ :
//      ����ֵ��TRUE��ʾ�ɹ���FALSE��ʾʧ��
//
//////////////////////////////////////////////////////////////////////////
BOOL CSkinManager::ChangeSkin(LPCTSTR lpctSkinName)
{
    if (_tcslen(lpctSkinName) == 0) return FALSE;

    CString pszSkinFilePath = lpctSkinName;
    m_pszCurrentSkin = lpctSkinName;
    pszSkinFilePath = g_pszModulePath + _T("Skin\\") + pszSkinFilePath + _T("\\theme.ini");
    m_skinINI.SetPathName(pszSkinFilePath);
    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//
//  GetCurrentSkinName : ��õ�ǰƤ������
//
//  ���� : ��
//
//  ����ֵ : ��ǰƤ�����ƣ��ļ�������
//
//////////////////////////////////////////////////////////////////////////
LPCTSTR CSkinManager::GetCurrentSkinName()
{
    return m_pszCurrentSkin;
}
//////////////////////////////////////////////////////////////////////////
//
//  GetColor : ����Ƥ�����������ļ���ȡһ����ɫֵ
//
//  ���� :
//      lpctSection - INI�ļ��Ľ�(Section)��
//      lpctKey - lpctSection�µ�ĳ����ֵ(Key)��
//      clrDefault - �����ȡ����Ϊ�գ��򷵻�Ĭ�ϵ���ɫֵ
//
//  ����ֵ : ��ȡ����ɫֵ
//
//////////////////////////////////////////////////////////////////////////
COLORREF CSkinManager::GetColor(LPCTSTR lpctSection, LPCTSTR lpctKey, COLORREF clrDefault)
{
    return m_skinINI.GetColor(lpctSection, lpctKey, clrDefault);
}
//////////////////////////////////////////////////////////////////////////
//
//  GetBool : ����Ƥ�����������ļ���ȡһ������ֵ
//
//  ���� :
//      lpctSection - INI�ļ��Ľ�(Section)��
//      lpctKey - lpctSection�µ�ĳ����ֵ(Key)��
//      bDefault - �����ȡ����Ϊ�գ��򷵻�Ĭ�ϵĲ���ֵ
//
//  ����ֵ : ��ȡ�Ĳ���ֵ
//
//////////////////////////////////////////////////////////////////////////
BOOL CSkinManager::GetBool(LPCTSTR lpctSection, LPCTSTR lpctKey, BOOL bDefault/* =TRUE */)
{
    return m_skinINI.GetBool(lpctSection, lpctKey, bDefault);
}
//////////////////////////////////////////////////////////////////////////
//
//  GetInt : ����Ƥ�����������ļ���ȡһ������ֵ
//
//  ���� :
//      lpctSection - INI�ļ��Ľ�(Section)��
//      lpctKey - lpctSection�µ�ĳ����ֵ(Key)��
//      iDefault - �����ȡ����Ϊ�գ��򷵻�Ĭ�ϵ�����ֵ
//
//  ����ֵ : ��ȡ������ֵ
//
//////////////////////////////////////////////////////////////////////////
int CSkinManager::GetInt(LPCTSTR lpctSection, LPCTSTR lpctKey, int iDefault)
{
    return m_skinINI.GetInt(lpctSection, lpctKey, iDefault);
}
//////////////////////////////////////////////////////////////////////////
//
//  GetPicturePath : ����Ƥ�����������ļ���ȡһ��ͼƬ�ļ�������·��
//
//  ���� :
//      lpctSection - INI�ļ��Ľ�(Section)��
//      lpctKey - lpctSection�µ�ĳ����ֵ(Key)��
//      lptValue - ���ڴ��·�����ַ�������
//      iValueLen - lptValue���ڴ�ռ䳤��
//      lpctDefault - �����ȡ����Ϊ�գ��򷵻ظ�Ĭ��ֵ
//
//  ����ֵ : ��ȡ���ַ�������
//
//////////////////////////////////////////////////////////////////////////
DWORD CSkinManager::GetPicturePath(LPCTSTR lpctSection, LPCTSTR lpctKey, LPTSTR lptValue, int iValueLen, LPCTSTR lpctDefault/* =NULL */)
{
    TCHAR* tszTemp = new TCHAR[_MAX_PATH];
    memset(tszTemp, 0, _MAX_PATH);
    m_skinINI.GetString(lpctSection, lpctKey, tszTemp, _MAX_PATH, lpctDefault);
    CString pszValue = tszTemp;
    delete[] tszTemp;
    pszValue = g_pszModulePath + _T("Skin\\") + m_pszCurrentSkin + _T("\\") + pszValue;

    if (pszValue.GetLength() > iValueLen)
        return 0;

    _tcscpy(lptValue, pszValue);
    return (DWORD)_tcslen(lptValue);
}
