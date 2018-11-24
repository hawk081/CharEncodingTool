#pragma once

#include "Parser.h"
#include "Formatter.h"
#include "EditEx.h"

// CBaseDialog dialog
#define SAFE_DELETE(_PTR)\
if( _PTR != NULL )\
{\
delete _PTR;\
_PTR = NULL;\
}

class CBaseDialog : public CDialog
{
    DECLARE_DYNAMIC(CBaseDialog)

public:
    CBaseDialog(CWnd* pParent = NULL);   // standard constructor
    virtual ~CBaseDialog();

// Dialog Data
    enum { IDD = IDD_BASE_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()


protected:
    afx_msg void OnInputTextChanged();
    afx_msg void OnRadioClicked(UINT nID);

protected:
    virtual void Perform();
    virtual void GetSettings();

protected:
    Parser* m_pParser;
    Formatter* m_pFormatter;
    EncodingType m_EncodingType;
    FormatType m_FormatType;
    BOOL m_bConverToNumber;
    UINT m_LastFormatRadio;
    UINT m_SelectedMethod;
    CFont *m_pFont;
    CEditEx  m_editInput;
    CEditEx  m_editOutput;
    CString m_ToCharString;
    CString m_ToNumberString;
    HWND m_MainWnd;
    BOOL m_bInited;

public:
    void setMainWnd(HWND mainwnd);
    void setOriginalEncoding( EncodingType encType);
    void setDestFormat( FormatType fmtType);
    void setEnable(UINT nID, BOOL enable = TRUE);
    void setChecked(UINT nID, BOOL checked = TRUE);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    void ChangeSize(UINT nID, int left, int top, int bottom, int right);
};
