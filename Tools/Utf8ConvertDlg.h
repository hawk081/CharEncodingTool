#pragma once
#include "TipsDlg.h"
#include "EditEx.h"
#include "Util.h"

// CUtf8ConvertDlg 对话框

class CUtf8ConvertDlg : public CDialog
{
    DECLARE_DYNAMIC(CUtf8ConvertDlg)

public:
    CUtf8ConvertDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CUtf8ConvertDlg();

// 对话框数据
    enum { IDD = IDD_Utf8CONVERT_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
protected:
    CFont *m_pFont;
    TipsDlg *m_pInfoOutDlg;
    NumberType m_Vnumber;
    CString  m_OutputBuffer;
    CEditEx  m_editInput;
    CEditEx  m_editOutput;
protected:
    CString Unicode2Number(CString szInput, BOOL bUse10);
    void OutputInfo(CString szInfo);
    BOOL InputCheck(CString szInput, BOOL bUse10);
    std::wstring ReplaceString(boost::match_results<std::wstring::const_iterator> match) const;
    std::wstring ReplaceNumberWithChar(boost::match_results<std::wstring::const_iterator> match) const;
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonTonumber();
    afx_msg void OnBnClickedButtonTounicode();
    afx_msg void OnRadioClicked(UINT nID);
    afx_msg LRESULT OnOutputDlgClose(WPARAM wParam, LPARAM lParam);
    afx_msg void OnEnChangeEditInput();
};
