// TipsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "TipsDlg.h"


// TipsDlg 对话框

IMPLEMENT_DYNAMIC(TipsDlg, CDialog)

TipsDlg::TipsDlg(CWnd* pParent /*=NULL*/)
    : CDialog(TipsDlg::IDD, pParent)
{

}

TipsDlg::~TipsDlg()
{
}

void TipsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TipsDlg, CDialog)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// TipsDlg 消息处理程序
void TipsDlg::SetOutputInfo(CString szInfo)
{
    ((CEdit *)GetDlgItem(IDC_EDIT_RESULT_TXT_OUT))->SetWindowText(szInfo);
}

void TipsDlg::SetOutputFont(CFont* pFont)
{
    this->m_pFont = pFont;
    ((CEdit *)GetDlgItem(IDC_EDIT_RESULT_TXT_OUT))->SetFont(this->m_pFont);
}

void TipsDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    ::PostMessage(this->GetParent()->m_hWnd,UM_DELETE_OUTPUT_DIALOG,(WPARAM)this,(LPARAM)NULL);
    CDialog::OnClose();
}
