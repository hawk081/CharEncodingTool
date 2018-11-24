#pragma once
#include "TipsDlg.h"
#include "EditEx.h"

// CUnicodeConvertDlg �Ի���

class CUnicodeConvertDlg : public CDialog
{
    DECLARE_DYNAMIC(CUnicodeConvertDlg)

public:
    CUnicodeConvertDlg(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CUnicodeConvertDlg();

// �Ի�������
    enum { IDD = IDD_UNICODECONVERT_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
protected:
    CFont *m_pFont;
    TipsDlg *m_pInfoOutDlg;
    NumberType m_Vnumber;
    CEditEx  m_editInput;
    CEditEx  m_editOutput;
protected:
    CString Unicode2Number(CString szInput, BOOL bUse10);
    void OutputInfo(CString szInfo);
    BOOL InputCheck(CString szInput, BOOL bUse10);
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonTonumber();
    afx_msg void OnBnClickedButtonTounicode();
    afx_msg void OnRadioClicked(UINT nID);
    afx_msg LRESULT OnOutputDlgClose(WPARAM wParam, LPARAM lParam);
    afx_msg void OnEnChangeEditInput();
};
