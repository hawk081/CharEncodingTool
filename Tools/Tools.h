// Tools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
    #error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"        // ������


// CTabDemoApp:
// �йش����ʵ�֣������ TabDemo.cpp
//

class CToolsApp : public CWinApp
{
public:
    CToolsApp();

// ��д
    public:
    virtual BOOL InitInstance();
    virtual void CToolsApp::OnHelp();

// ʵ��

    DECLARE_MESSAGE_MAP()
};

extern CToolsApp theApp;
extern CString strTemp;