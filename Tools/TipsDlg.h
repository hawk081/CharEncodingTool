#pragma once


// TipsDlg �Ի���

class TipsDlg : public CDialog
{
    DECLARE_DYNAMIC(TipsDlg)

public:
    TipsDlg(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~TipsDlg();

// �Ի�������
    enum { IDD = IDD_TIPSDLG };

public:
    void SetOutputInfo(CString szInfo);
    void SetOutputFont(CFont* pFont);
private:
    CFont* m_pFont;
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
};
