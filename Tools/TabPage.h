#pragma once


// CTabPage
#define UM_NOTIFY_SEL_CHANGING (WM_USER + 0x1000)
#define UM_NOTIFY_SEL_CHANGE   (WM_USER + 0x1001)

class CTabPage : public CTabCtrl
{
    DECLARE_DYNAMIC(CTabPage)

    int        m_nPageCount;    //页数

public:
    CTabPage();
    virtual ~CTabPage();

    void    AddPage(CWnd* pPageWnd, LPTSTR lpTitle);    //添加选项卡
    void    ShowCurPage(UINT nShowState);                //显示当前页面
    void    SetParent(HWND parent);

public:
    afx_msg void OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()

    HWND hParentHandle;
};