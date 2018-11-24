#pragma once


// TipsDlg 对话框

class TipsDlg : public CDialog
{
    DECLARE_DYNAMIC(TipsDlg)

public:
    TipsDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~TipsDlg();

// 对话框数据
    enum { IDD = IDD_TIPSDLG };

public:
    void SetOutputInfo(CString szInfo);
    void SetOutputFont(CFont* pFont);
private:
    CFont* m_pFont;
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
};
