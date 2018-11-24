// Utf8ConvertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "Utf8ConvertDlg.h"

#include "ToolsDlg.h"
#include "Parser.h"
#include "Formatter.h"
// CPage2Dlg 对话框

IMPLEMENT_DYNAMIC(CUtf8ConvertDlg, CDialog)

CUtf8ConvertDlg::CUtf8ConvertDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CUtf8ConvertDlg::IDD, pParent)
{

}

CUtf8ConvertDlg::~CUtf8ConvertDlg()
{
}

void CUtf8ConvertDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUtf8ConvertDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CUtf8ConvertDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_TONUMBER, &CUtf8ConvertDlg::OnBnClickedButtonTonumber)
    ON_BN_CLICKED(IDC_BUTTON_TOUNICODE, &CUtf8ConvertDlg::OnBnClickedButtonTounicode)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_DECLI10, IDC_RADIO_TOCHAR, &CUtf8ConvertDlg::OnRadioClicked)
    ON_MESSAGE(UM_DELETE_OUTPUT_DIALOG, &CUtf8ConvertDlg::OnOutputDlgClose)
    ON_EN_CHANGE(IDC_EDIT_INPUT, &CUtf8ConvertDlg::OnEnChangeEditInput)
END_MESSAGE_MAP()


// CUtf8ConvertDlg message handlers

BOOL CUtf8ConvertDlg::OnInitDialog()
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

    Parser parser_utf8(L"1%E6%88%91\x963f", ENC_UTF8);
    std::wstring s = parser_utf8.getParsedString();
    Parser parser_gbk(L"%CE%D2", ENC_GBK);
    std::wstring s1 = parser_gbk.getParsedString();
    Parser parser_big5(L"%B6%48", ENC_BIG5);
    std::wstring s2 = parser_big5.getParsedString();
    Parser parser_unicode(L"\x963f\u9640", ENC_UNICODE);
    std::wstring s3 = parser_unicode.getParsedString();
    Parser parser_ori(L"963f", ENC_UNICODE);
    std::wstring s4 = parser_ori.getParsedString();
    std::string s5 = Utils::ASCIICopy<std::string>(std::wstring(L"9891"));
    std::wstring s6 = Utils::ASCIICopy<std::wstring>(std::string("\xfe\xaa"));
    Formatter fmter("qq360", FMT_PERCENT, ENC_UTF8);
    std::wstring s7 = fmter.getFormattedWString();
    std::string s8 = fmter.getFormattedString();
    Formatter fmter_oct(L"\x963f", FMT_OCT, ENC_UTF8);
    std::wstring s9 = fmter_oct.getFormattedWString();
    std::string s10 = fmter_oct.getFormattedString();
    Parser parser_utf89(s9, ENC_UTF8);
    std::wstring fmt_utf8 = parser_utf89.getParsedString();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUtf8ConvertDlg::OnBnClickedOk()
{
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

CString CUtf8ConvertDlg::Unicode2Number(CString szInput, BOOL bUse10)
{
    CString szReturn(_T(""));
    std::wstring wstrIn = Util::Unicode2UTF8(szInput);
    szInput.Empty();
    szInput.Append(wstrIn.c_str());
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

void CUtf8ConvertDlg::OnBnClickedButtonTonumber()
{
    CString strInput(_T(""));
    CString strOutput(_T(""));
    ((CEdit *)GetDlgItem(IDC_EDIT_INPUT))->GetWindowText(strInput);
    if ( strInput.IsEmpty() )
    {
        //return;
    }
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

void CUtf8ConvertDlg::OnBnClickedButtonTounicode()
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
    strOutput += Util::UTF82UnicodeStr(m_OutputBuffer.GetBuffer(0));
    for( NumberType::const_iterator it = m_Vnumber.begin();it != m_Vnumber.end();++it)
    {
        //strOutput += (TCHAR)*it;
    }
    ((CEdit *)GetDlgItem(IDC_EDIT_OUTPUT))->SetWindowText(strOutput);
}

void CUtf8ConvertDlg::OnRadioClicked(UINT nID)
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

void CUtf8ConvertDlg::OutputInfo(CString szInfo)
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

LRESULT CUtf8ConvertDlg::OnOutputDlgClose(WPARAM wParam, LPARAM lParam)
{
    if(m_pInfoOutDlg != NULL)
    {
        delete m_pInfoOutDlg;
        m_pInfoOutDlg = NULL;
    }    

    return 0;
}
void CUtf8ConvertDlg::OnEnChangeEditInput()
{
    OnBnClickedOk();
}

std::wstring CUtf8ConvertDlg::ReplaceString(boost::match_results<std::wstring::const_iterator> match) const
{
    int x = 1;
    std::wstring _1 = match[1];
    long number = Util::String2Integer( _1, 8 );
    wchar_t szNumber[20] = L"";
    swprintf_s(szNumber, 20, L"\\x%x", number);
    std::wstring retn(szNumber);
    return retn;
}

std::wstring CUtf8ConvertDlg::ReplaceNumberWithChar(boost::match_results<std::wstring::const_iterator> match) const
{
    int x = 1;
    std::wstring _1 = match[1];
    long number = Util::String2Integer( _1, 16 );
    CString temp(L"");
    temp.AppendChar((wchar_t)number);
    
    return Util::CString2string(temp);
}

BOOL CUtf8ConvertDlg::InputCheck(CString szInput, BOOL bUse10)
{
    std::wstring szInputString(szInput.GetBuffer(0));
    m_Vnumber.clear();
    m_OutputBuffer.Empty();
    try
    {
        boost::wregex reg_re0(L"\\\\([0-7][0-7][0-7])",boost::regex::icase);
        boost::function<std::wstring (boost::match_results<std::wstring::const_iterator>)> function1 =
            boost::bind(&CUtf8ConvertDlg::ReplaceString, this, _1);
        szInputString = regex_replace(szInputString, reg_re0, function1);

        //boost::wregex reg_re1(L"(\\\\u)",boost::regex::icase);
        //szInputString = boost::regex_replace(szInputString,reg_re1, "\\\\x");

        boost::wregex reg_re2(L"(?:\\\\x|%|\\\\u)([0-9a-fA-F]{0,2})",boost::regex::icase);
        boost::function<std::wstring (boost::match_results<std::wstring::const_iterator>)> function2 =
            boost::bind(&CUtf8ConvertDlg::ReplaceNumberWithChar, this, _1);
        szInputString = regex_replace(szInputString, reg_re2, function2);
        m_OutputBuffer = szInputString.c_str();
    }
    catch (std::exception &e)
    {
        TRACE("%s\n",e.what());
    }

    return TRUE;
}