// Tools.h : 头文件
//

#pragma once

#include "tabpage.h"
#include "UnicodeConvertDlg.h"
#include "Utf8ConvertDlg.h"
#include "BaseDialog.h"
#include "afxwin.h"

const int OUTLINE_MARGIN = 7;

#define WM_SHOWINFOR_MESSAGE    WM_USER+140 

enum
{
    UNICODE_CNVT,
    UTF8_CNVT,
    GBK_CNVT,
    BIG5_CNVT,
    JPN_CNVT,
    KOR_CNVT,
    THAI_CNVT,

    CNVT_COUNT
};

typedef struct _tagTabItem {
    UINT IDD;
    EncodingType encType;
    CString title;
} TabItem;

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

// CToolsDlg 对话框
class CToolsDlg : public CDialog
{
// 构造
public:
    CToolsDlg(CWnd* pParent = NULL);    // 标准构造函数
    ~CToolsDlg();    // 标准构造函数

// 对话框数据
    enum { IDD = IDD_DIALOG_MAIN };

    CTabPage        m_tabDemo;
    CBaseDialog*    m_pDlgPages[CNVT_COUNT];
    CAboutDlg*      m_pAboutPage;
    CRect           m_rect;
    CRect           m_minRect;
    BOOL            m_bInit;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();


// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    afx_msg void    OnPaint();
    afx_msg HCURSOR    OnQueryDragIcon();
    afx_msg void    OnDestroy();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg LRESULT OnFuncKeys(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnTcnSelchanging(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnTcnSelchange(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    void ChangeSize(UINT nID, int left, int top, int bottom, int right);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
