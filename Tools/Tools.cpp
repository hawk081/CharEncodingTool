// Tools.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Tools.h"
#include "ToolsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString strTemp=_T("��ʼ�����ַ���");

// CToolsApp

BEGIN_MESSAGE_MAP(CToolsApp, CWinApp)
    ON_COMMAND(ID_HELP, &CToolsApp::OnHelp)
END_MESSAGE_MAP()


// CToolsApp ����

CToolsApp::CToolsApp()
{
    // TODO: �ڴ˴����ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

void CToolsApp::OnHelp()  // use context to derive help context
{
}


// Ψһ��һ�� CToolsApp ����

CToolsApp theApp;


// CToolsApp ��ʼ��

BOOL CToolsApp::InitInstance()
{
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
    // �����ؼ��ࡣ
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    AfxEnableControlContainer();

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������
    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

    CToolsDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: �ڴ˴����ô�����ʱ�á�ȷ�������ر�
        //  �Ի���Ĵ���
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: �ڴ˷��ô�����ʱ�á�ȡ�������ر�
        //  �Ի���Ĵ���
    }

    // ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
    //  ����������Ӧ�ó������Ϣ�á�
    return FALSE;
}