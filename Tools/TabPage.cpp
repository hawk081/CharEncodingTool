// TabPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "TabPage.h"


// CTabPage

IMPLEMENT_DYNAMIC(CTabPage, CTabCtrl)

CTabPage::CTabPage()
{
    m_nPageCount    = 0;
    hParentHandle   = NULL;
}

CTabPage::~CTabPage()
{
}

void CTabPage::AddPage(CWnd *pPageWnd, LPTSTR lpTitle)
{
    TCITEM    itemPage;

    itemPage.mask        = TCIF_TEXT|TCIF_PARAM;
    itemPage.lParam        = LPARAM(pPageWnd);
    itemPage.pszText    = lpTitle;

    InsertItem(m_nPageCount, &itemPage);
    m_nPageCount==0?pPageWnd->ShowWindow(SW_SHOW):pPageWnd->ShowWindow(SW_HIDE);
    m_nPageCount++;
}

void CTabPage::ShowCurPage(UINT nShowState)
{
    int        nCurItem;
    TCITEM    itemCur;

    nCurItem        = GetCurSel();
    itemCur.mask    = TCIF_PARAM;

    GetItem(nCurItem, &itemCur);
    ((CWnd*)itemCur.lParam)->ShowWindow(nShowState);
}

void CTabPage::SetParent(HWND parent)
{
    this->hParentHandle = parent;
}

BEGIN_MESSAGE_MAP(CTabPage, CTabCtrl)
    ON_NOTIFY_REFLECT(TCN_SELCHANGING, &CTabPage::OnTcnSelchanging)
    ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CTabPage::OnTcnSelchange)
    //}}AFX_MSG_MAP
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CTabPage 消息处理程序

void CTabPage::OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
    if(hParentHandle != NULL)
    {
        ::PostMessage(hParentHandle, UM_NOTIFY_SEL_CHANGING, GetCurSel(), NULL);
    }
    ShowCurPage(SW_HIDE);

    *pResult    = 0;
}

void CTabPage::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
    if(hParentHandle != NULL)
    {
        ::PostMessage(hParentHandle, UM_NOTIFY_SEL_CHANGE, GetCurSel(), NULL);
    }
    ShowCurPage(SW_SHOW);

    *pResult    = 0;
}

void CTabPage::OnSize(UINT nType, int cx, int cy)
{
    CTabCtrl::OnSize(nType, cx, cy);

    if( nType != SIZE_MINIMIZED)
    {
        int count =  this->GetItemCount();
        TCITEM    itemPage;
        for(int i = 0; i < count; i++)
        {
            memset(&itemPage, 0x00, sizeof(TCITEM));
            itemPage.mask    = TCIF_PARAM;
            this->GetItem(i, &itemPage);
            ((CWnd *)itemPage.lParam)->PostMessage(WM_SIZE);
        }
    }
}