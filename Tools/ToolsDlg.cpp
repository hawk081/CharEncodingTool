// TabDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "ToolsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TabItem itemList[CNVT_COUNT] =
{
    {
        IDD_BASE_DIALOG, ENC_UNICODE, L"Unicode\x8f6c\x6362"
    },
    {
        IDD_BASE_DIALOG, ENC_UTF8, L"UTF8\x8f6c\x6362"
    },
    {
        IDD_BASE_DIALOG, ENC_GBK, L"GBK\x8f6c\x6362"
    },
    {
        IDD_BASE_DIALOG, ENC_BIG5, L"BIG5\x8f6c\x6362"
    },
    {
        IDD_BASE_DIALOG, ENC_JPN, L"JPN\x8f6c\x6362"
    },
    {
        IDD_BASE_DIALOG, ENC_KOR, L"KOR\x8f6c\x6362"
    },
    {
        IDD_BASE_DIALOG, ENC_THAI, L"Thai\x8f6c\x6362"
    }
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //}}AFX_MSG_MAP
    ON_WM_SIZE()
END_MESSAGE_MAP()

void CAboutDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    CRect rect;
    this->GetParent()->GetWindowRect(&rect);
    this->GetParent()->ScreenToClient(&rect);
    rect.top   += 22; /* skip parent's header */
    rect.left  += 2;
    rect.right -= 2;
    this->MoveWindow(rect);
}

// CToolsDlg 对话框

CToolsDlg::CToolsDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CToolsDlg::IDD, pParent)
{
    for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
    {
        m_pDlgPages[i] = NULL;
    }
    m_pAboutPage = NULL;
    m_bInit = FALSE;

    m_hIcon        = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CToolsDlg::~CToolsDlg()
{
    for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
    {
        SAFE_DELETE(m_pDlgPages[i]);
    }
    SAFE_DELETE(m_pAboutPage);
}

void CToolsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_DEMO, m_tabDemo);
}

BEGIN_MESSAGE_MAP(CToolsDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SYSCOMMAND()
    ON_MESSAGE(UM_FUNC_KEYS_MESSAGE, &CToolsDlg::OnFuncKeys)
    ON_MESSAGE(UM_NOTIFY_SEL_CHANGING, &CToolsDlg::OnTcnSelchanging)
    ON_MESSAGE(UM_NOTIFY_SEL_CHANGE, &CToolsDlg::OnTcnSelchange)
    //}}AFX_MSG_MAP
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CToolsDlg 消息处理程序

BOOL CToolsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);            // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    GetClientRect(&m_rect);
    GetWindowRect(&m_minRect);

    m_tabDemo.SetParent(this->m_hWnd);

    CRect    rectPage;

    m_tabDemo.GetWindowRect(&rectPage);
    m_tabDemo.ScreenToClient(&rectPage);

    rectPage.top     = m_rect.top + OUTLINE_MARGIN;
    rectPage.bottom  = m_rect.bottom - OUTLINE_MARGIN;
    rectPage.left    = m_rect.left + OUTLINE_MARGIN;
    rectPage.right   = m_rect.right - OUTLINE_MARGIN;
    m_tabDemo.MoveWindow(rectPage);

    for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
    {
        m_pDlgPages[i] = new CBaseDialog;
        m_pDlgPages[i]->Create(itemList[i].IDD, &m_tabDemo);
        m_pDlgPages[i]->setOriginalEncoding(itemList[i].encType);
        m_pDlgPages[i]->MoveWindow(rectPage);
        m_pDlgPages[i]->setMainWnd(this->m_hWnd);
        m_tabDemo.AddPage(m_pDlgPages[i], itemList[i].title.GetBuffer(0));
    }
    m_pAboutPage = new CAboutDlg;
    m_pAboutPage->Create(IDD_ABOUTBOX_EX, &m_tabDemo);
    m_pAboutPage->MoveWindow(rectPage);
    m_tabDemo.AddPage(m_pAboutPage, L"\x5173\x4E8E");
    
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        //CAboutDlg dlgAbout;
        //dlgAbout.DoModal();
        for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
        {
            m_pDlgPages[i]->ShowWindow(SW_HIDE);
        }
        m_tabDemo.SetCurSel( CNVT_COUNT );
        m_tabDemo.ShowCurPage(SW_SHOW);
        this->SetWindowText(L"\x5173\x4E8E");
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CToolsDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CToolsDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CToolsDlg::OnDestroy()
{
    for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
    {
        m_pDlgPages[i]->DestroyWindow();
    }
    m_pAboutPage->DestroyWindow();

    CDialog::OnDestroy();
}

LRESULT CToolsDlg::OnFuncKeys(WPARAM wParam, LPARAM lParam)
{
    UINT key = (UINT)wParam;
    switch(key)
    {
    case VK_F1:
    case VK_F2:
    case VK_F3:
    case VK_F4:
    case VK_F5:
    case VK_F6:
    case VK_F7:
    case VK_F8:
    case VK_F9:
        {
            UINT selected = key - VK_F1;

            for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
            {
                m_pDlgPages[i]->ShowWindow(SW_HIDE);
            }
            m_tabDemo.SetCurSel( selected % CNVT_COUNT );
            m_tabDemo.ShowCurPage(SW_SHOW);
            this->SetWindowText(itemList[selected % CNVT_COUNT].title);
        }
        break;
    case VK_ESCAPE:
        CDialog::OnCancel();
        break;
    }
    return 0;
}

LRESULT CToolsDlg::OnTcnSelchanging(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

LRESULT CToolsDlg::OnTcnSelchange(WPARAM wParam, LPARAM lParam)
{
    UINT CurSel = (UINT)wParam;
    CString str;
    str.Format(_T("%s - Hawk"), itemList[CurSel % CNVT_COUNT].title);
    this->SetWindowText(str);
    return 0;
}

BOOL CToolsDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        switch (pMsg->wParam)
        {
        case VK_F1:
        case VK_F2:
        case VK_F3:
        case VK_F4:
        case VK_F5:
        case VK_F6:
        case VK_F7:
        case VK_F8:
        case VK_F9:
            {
                ::PostMessage(m_hWnd, UM_FUNC_KEYS_MESSAGE, pMsg->wParam, NULL);
            }
            break;
        default:
            break;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CToolsDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if(!m_bInit)
    {
        m_bInit = TRUE;
        return;
    }

    if( nType != SIZE_MINIMIZED)
    {
        GetDlgItem(IDC_TAB_DEMO)->GetWindowRect(&m_rect);
        ScreenToClient(&m_rect);
        GetClientRect(&m_rect);
        ChangeSize(IDC_TAB_DEMO, m_rect.left + 7, m_rect.top + 7, m_rect.bottom - 7, m_rect.right - 7);
        for(int i = UNICODE_CNVT; i < CNVT_COUNT; i++)
        {
            //::PostMessage(m_pDlgPages[i]->m_hWnd, WM_SIZE, NULL, NULL);
        }
    }
}

void CToolsDlg::ChangeSize(UINT nID, int left, int top, int bottom, int right)
{
    CWnd *pWnd;
    pWnd = GetDlgItem(nID); 
    if(pWnd != NULL)
    {
        CRect rec; 
        pWnd->GetWindowRect(&rec);
        ScreenToClient(&rec);
        rec.left   = left;
        rec.top    = top;
        rec.bottom = bottom;
        rec.right  = right;
        pWnd->MoveWindow(rec);
    }
}

void CToolsDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    if( m_bInit )
    {
        CPoint pt(m_minRect.right - m_minRect.left, m_minRect.bottom - m_minRect.top);
        lpMMI->ptMinTrackSize = pt;
    }
    CDialog::OnGetMinMaxInfo(lpMMI);
}
