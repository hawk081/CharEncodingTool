// UnicodeConvertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "UnicodeConvertDlg.h"

#include "ToolsDlg.h"


// CUnicodeConvertDlg 对话框

IMPLEMENT_DYNAMIC(CUnicodeConvertDlg, CDialog)

CUnicodeConvertDlg::CUnicodeConvertDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CUnicodeConvertDlg::IDD, pParent)
{

}

CUnicodeConvertDlg::~CUnicodeConvertDlg()
{
}

void CUnicodeConvertDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUnicodeConvertDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CUnicodeConvertDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_TONUMBER, &CUnicodeConvertDlg::OnBnClickedButtonTonumber)
    ON_BN_CLICKED(IDC_BUTTON_TOUNICODE, &CUnicodeConvertDlg::OnBnClickedButtonTounicode)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_DECLI10, IDC_RADIO_TOCHAR, &CUnicodeConvertDlg::OnRadioClicked)
    ON_MESSAGE(UM_DELETE_OUTPUT_DIALOG, &CUnicodeConvertDlg::OnOutputDlgClose)
    ON_EN_CHANGE(IDC_EDIT_INPUT, &CUnicodeConvertDlg::OnEnChangeEditInput)
END_MESSAGE_MAP()

// CUnicodeConvertDlg message handlers

BOOL CUnicodeConvertDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ((CButton *)GetDlgItem(IDC_RADIO_DECLI10))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_HEX16))->SetCheck(TRUE);

    ((CButton *)GetDlgItem(IDC_RADIO_TOCHAR))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_RADIO_TONUMBER))->SetCheck(FALSE);

    OnRadioClicked(0);
    if ( USE_CHINESE )
    {
        SetWindowText(CString(_T("Unicode\x8f6c\x6362")));
        ((CStatic *)GetDlgItem(IDC_STATIC_METHOD))->SetWindowText(_T("\x8f6c\x6362\x65b9\x5f0f"));
        ((CStatic *)GetDlgItem(IDC_RADIO_TOCHAR))->SetWindowText(_T("\x8f6c\x6362\x4e3a\x5b57\x7b26"));
        ((CStatic *)GetDlgItem(IDC_RADIO_TONUMBER))->SetWindowText(_T("\x8f6c\x6362\x4e3a\x6570\x5b57"));
        ((CStatic *)GetDlgItem(IDC_STATIC_NUMBER))->SetWindowText(_T("\x6570\x5236"));
        ((CStatic *)GetDlgItem(IDC_RADIO_DECLI10))->SetWindowText(_T("\x5341\x8fdb\x5236"));
        ((CStatic *)GetDlgItem(IDC_RADIO_HEX16))->SetWindowText(_T("\x5341\x516d\x8fdb\x5236"));
        ((CButton *)GetDlgItem(IDOK))->SetWindowText(_T("\x8f6c   \x6362(Enter)"));
    }

    m_pFont = new CFont();
    m_pFont->CreateFont(
        30,
        0,
        0,
        0,
        FW_BOLD,
        FALSE,
        FALSE,
        0,
        ANSI_CHARSET,
        OUT_SCREEN_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        USE_FONT_NAME );
    ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->SetFont(m_pFont);
    ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetFont(m_pFont);
    ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetReadOnly();

    m_editInput.SubclassDlgItem(IDC_EDIT_INPUT, this);
    m_editOutput.SubclassDlgItem(IDC_EDIT_OUTPUT, this);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUnicodeConvertDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    if ( BST_CHECKED == ((CButton *)GetDlgItem(IDC_RADIO_TONUMBER))->GetCheck() )
    {
        OnBnClickedButtonTonumber();
    }
    else
    {
        OnBnClickedButtonTounicode();
    }
    ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->SetFocus();
}

CString CUnicodeConvertDlg::Unicode2Number(CString szInput, BOOL bUse10)
{
    CString szReturn(_T(""));
    TCHAR Uni_char = szInput.GetAt(0);
    for(int i = 0; i < szInput.GetLength(); i++ )
    {
        Uni_char = szInput.GetAt(i);
        if( bUse10 )
        {
            i == szInput.GetLength() - 1 ? szReturn.AppendFormat(_T("%d"),Uni_char) : szReturn.AppendFormat(_T("%d,"),Uni_char);
        }
        else
        {
            szReturn.AppendFormat(_T("\\x%x"),Uni_char);
        }
    }
    return szReturn;
}

void CUnicodeConvertDlg::OnBnClickedButtonTonumber()
{
    CString strInput(_T(""));
    CString strOutput(_T(""));
    ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->GetWindowText(strInput);
    if ( BST_CHECKED == ((CButton *)GetDlgItem(IDC_RADIO_DECLI10))->GetCheck() )
    {
        strOutput = Unicode2Number(strInput, TRUE );
    }
    else
    {
        strOutput = Unicode2Number(strInput, FALSE );
    }
    ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetWindowText(strOutput);
}

void CUnicodeConvertDlg::OnBnClickedButtonTounicode()
{
    CString strInput(_T(""));
    CString strTemp(_T(""));
    CString strOutput(_T(""));
    TCHAR value = 0;
    ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->GetWindowText(strInput);
    if ( strInput.IsEmpty() )
    {
        //return;
    }
    InputCheck(strInput, BST_CHECKED == ((CButton *)GetDlgItem(IDC_RADIO_DECLI10))->GetCheck());
    for( NumberType::const_iterator it = m_Vnumber.begin();it != m_Vnumber.end();++it)
    {
        strOutput += (TCHAR)*it;
    }
    ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetWindowText(strOutput);
}

void CUnicodeConvertDlg::OnRadioClicked(UINT nID)
{
    TRACE("nID:%d\n",nID);
    if ( BST_CHECKED == ((CButton *)GetDlgItem(IDC_RADIO_TOCHAR))->GetCheck())
    {
        if ( BST_CHECKED == ((CButton *)GetDlgItem(IDC_RADIO_HEX16))->GetCheck() )
        {
            ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->SetWindowText(CString(_T("\\x")));
        }
        else
        {
            ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->SetWindowText(CString(_T("")));
        }
        ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetWindowText(CString(_T("")));
    }
    else
    {
        ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->SetWindowText(CString(_T("")));
        ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetWindowText(CString(_T("")));
    }
}

void CUnicodeConvertDlg::OutputInfo(CString szInfo)
{
    CRect rect;
    GetWindowRect(&rect);
    if(m_pInfoOutDlg == NULL)
    {
        m_pInfoOutDlg = new TipsDlg;
        m_pInfoOutDlg->Create(IDD_TIPSDLG,this);
        m_pInfoOutDlg->SetOutputFont(m_pFont);
        if(USE_CHINESE)
        {
            m_pInfoOutDlg->SetWindowText(_T("\x7ed3\x679c"));
        }
        m_pInfoOutDlg->SetWindowPos(NULL, rect.right + 10,rect.top, 2 * ( rect.right - rect.left ), rect.bottom - rect.top, SWP_SHOWWINDOW);
        m_pInfoOutDlg->ShowWindow(SW_NORMAL);
    }
    m_pInfoOutDlg->SetOutputInfo(szInfo);
}

LRESULT CUnicodeConvertDlg::OnOutputDlgClose(WPARAM wParam, LPARAM lParam)
{
    if(m_pInfoOutDlg != NULL)
    {
        delete m_pInfoOutDlg;
        m_pInfoOutDlg = NULL;
    }    

    return 0;
}
void CUnicodeConvertDlg::OnEnChangeEditInput()
{
    OnBnClickedOk();
}

BOOL CUnicodeConvertDlg::InputCheck(CString szInput, BOOL bUse10)
{
    std::wstring szInputString(szInput.GetBuffer(0));
    m_Vnumber.clear();
    try
    {
        boost::wregex reg_re(L"(\\\\u)",boost::regex::icase); 
        szInputString = boost::regex_replace(szInputString,reg_re, "\\\\x");

        std::wstring::const_iterator itor = szInputString.begin();
        std::wstring::const_iterator end_itor = szInputString.end();
        boost::wregex reg(L"\\\\x([0-9a-fA-F]+)",boost::regex::icase); 
        boost::wsmatch m;

        while( boost::regex_search(itor, end_itor, m, reg) )
        {
            for (unsigned int i = 1; i < m.size(); ++i)
            {
                std::wstring str = m[i];
                m_Vnumber.push_back(Util::String2Integer(m[i],bUse10 ? 10 : 16 ));
                TRACE("%d\n", Util::String2Integer(m[i],bUse10 ? 10 : 16 ));
            }
            itor = m[0].second;
        }
    }
    catch (std::exception &e)
    {
        TRACE("%s\n",e.what());
    }

    return TRUE;
}