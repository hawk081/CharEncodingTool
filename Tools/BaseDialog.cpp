// BaseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Tools.h"
#include "BaseDialog.h"


// CBaseDialog dialog

IMPLEMENT_DYNAMIC(CBaseDialog, CDialog)

CBaseDialog::CBaseDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CBaseDialog::IDD, pParent)
    , m_pParser(NULL)
    , m_pFormatter(NULL)
    , m_EncodingType(ENC_UTF8)
    , m_LastFormatRadio( IIDC_RADIO_FORMAT_X )
    , m_SelectedMethod( IIDC_RADIO_TOCHAR )
    , m_ToCharString( _T("") )
    , m_ToNumberString( _T("") )
    , m_MainWnd(NULL)
    , m_bInited(FALSE)
{

}

CBaseDialog::~CBaseDialog()
{
    SAFE_DELETE(m_pFont);
    SAFE_DELETE(m_pParser);
}

void CBaseDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseDialog, CDialog)
    ON_EN_CHANGE(IIDC_EDIT_INPUT, &CBaseDialog::OnInputTextChanged)
    ON_CONTROL_RANGE(BN_CLICKED, IIDC_RADIO_TOCHAR, IIDC_RADIO_FORMAT_OCT, &CBaseDialog::OnRadioClicked)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CBaseDialog message handlers
BOOL CBaseDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    OnRadioClicked(m_SelectedMethod);

    SetDlgItemText(IIDC_STATIC_METHOD, _T("\x8f6c\x6362\x65b9\x5f0f"));
    SetDlgItemText(IIDC_STATIC_FORMAT, _T("\x76ee\x6807\x683c\x5f0f"));

    SetDlgItemText(IIDC_RADIO_TOCHAR, _T("\x8f6c\x6362\x4e3a\x5b57\x7b26"));
    SetDlgItemText(IIDC_RADIO_TONUMBER, _T("\x8f6c\x6362\x4e3a\x6570\x5b57"));
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
    ((CEdit *)GetDlgItem(IIDC_EDIT_INPUT))->SetFont(m_pFont);
    ((CEdit *)GetDlgItem(IIDC_EDIT_OUTPUT))->SetFont(m_pFont);
    ((CEdit *)GetDlgItem(IIDC_EDIT_OUTPUT))->SetReadOnly();

    m_editInput.SubclassDlgItem(IIDC_EDIT_INPUT, this);
    m_editOutput.SubclassDlgItem(IIDC_EDIT_OUTPUT, this);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBaseDialog::OnInputTextChanged()
{
    Perform();
}

void CBaseDialog::Perform()
{
    if ( m_SelectedMethod == IIDC_RADIO_TOCHAR )
    {
        SAFE_DELETE(m_pParser);
        GetDlgItemText(IIDC_EDIT_INPUT, m_ToCharString);
        m_pParser = new Parser(std::wstring(m_ToCharString.GetBuffer(0)), m_EncodingType);
        std::wstring pas = m_pParser->getParsedString();
        SetDlgItemText(IIDC_EDIT_OUTPUT, pas.c_str());
    }
    else if( m_SelectedMethod == IIDC_RADIO_TONUMBER )
    {
        SAFE_DELETE(m_pFormatter);
        GetDlgItemText(IIDC_EDIT_INPUT, m_ToNumberString);
        m_pFormatter = new Formatter(std::wstring(m_ToNumberString.GetBuffer(0)), m_FormatType, m_EncodingType);
        std::wstring pas = Utils::ASCIICopy<std::wstring>(m_pFormatter->getFormattedString());
        SetDlgItemText(IIDC_EDIT_OUTPUT, pas.c_str());
    }
}

void CBaseDialog::GetSettings()
{
    this->m_bConverToNumber = BST_CHECKED == ((CButton *)GetDlgItem(IDC_RADIO_TONUMBER))->GetCheck();
}

void CBaseDialog::setOriginalEncoding( EncodingType encType)
{
    this->m_EncodingType = encType;
}

void CBaseDialog::setDestFormat( FormatType fmtType)
{
    this->m_FormatType = fmtType;
}

void CBaseDialog::OnRadioClicked(UINT nID)
{
    setChecked(nID, TRUE);
    switch(nID)
    {
    case IIDC_RADIO_TOCHAR:
        /* disable all format radio */
        setEnable(IIDC_RADIO_FORMAT_X, FALSE);
        setEnable(IIDC_RADIO_FORMAT_U, FALSE);
        setEnable(IIDC_RADIO_FORMAT_P, FALSE);
        setEnable(IIDC_RADIO_FORMAT_OCT, FALSE);
        m_SelectedMethod = nID;
        SetDlgItemText(IIDC_EDIT_INPUT, m_ToCharString);
        break;
    case IIDC_RADIO_TONUMBER:
        /* enable all format radio */
        setEnable(IIDC_RADIO_FORMAT_X, TRUE);
        setEnable(IIDC_RADIO_FORMAT_U, TRUE);
        setEnable(IIDC_RADIO_FORMAT_P, TRUE);
        setEnable(IIDC_RADIO_FORMAT_OCT, TRUE);

        /* clear all */
        setChecked(IIDC_RADIO_FORMAT_X, FALSE);
        setChecked(IIDC_RADIO_FORMAT_U, FALSE);
        setChecked(IIDC_RADIO_FORMAT_P, FALSE);
        setChecked(IIDC_RADIO_FORMAT_OCT, FALSE);

        /* set saved as default */
        setChecked(m_LastFormatRadio, TRUE);

        m_SelectedMethod = nID;
        SetDlgItemText(IIDC_EDIT_INPUT, m_ToNumberString);
        break;
    case IIDC_RADIO_FORMAT_X:
        m_LastFormatRadio = nID;
        m_FormatType = FMT_X;
        break;
    case IIDC_RADIO_FORMAT_U:
        m_LastFormatRadio = nID;
        m_FormatType = FMT_U;
        break;
    case IIDC_RADIO_FORMAT_P:
        m_LastFormatRadio = nID;
        m_FormatType = FMT_PERCENT;
        break;
    case IIDC_RADIO_FORMAT_OCT:
        m_LastFormatRadio = nID;
        m_FormatType = FMT_OCT;
        break;
    default:
        break;
    }
    Perform();
}

void CBaseDialog::setEnable(UINT nID, BOOL enable)
{
    GetDlgItem(nID)->EnableWindow(enable);
}

void CBaseDialog::setChecked(UINT nID, BOOL checked)
{
    ((CButton *)GetDlgItem(nID))->SetCheck(checked);
}

void CBaseDialog::setMainWnd(HWND mainwnd)
{
    m_MainWnd = mainwnd;
}

BOOL CBaseDialog::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        switch (pMsg->wParam)
        {
        case VK_ESCAPE:
        case VK_F1:
        case VK_F2:
        case VK_F3:
        case VK_F4:
        case VK_F5:
        case VK_F6:
        case VK_F7:
        case VK_F8:
            {
                if(m_MainWnd != NULL)
                {
                    ::PostMessage(m_MainWnd, UM_FUNC_KEYS_MESSAGE, pMsg->wParam, NULL);
                }
            }
            return TRUE;
        default:
            break;
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CBaseDialog::OnSize(UINT nType, int cx, int cy)
{
    if(!m_bInited)
    {
        m_bInited = TRUE;
        return;
    }
    CRect rect;
    this->GetParent()->GetWindowRect(&rect);
    this->GetParent()->ScreenToClient(&rect);
    rect.top   += 22; /* skip parent's header */
    rect.left  += 2;
    rect.right -= 2;
    this->MoveWindow(rect);

    int windowWidth  = rect.right  - rect.left;
    int windowHeight = rect.bottom - rect.top;
    int margin       = 5;
    int rect_top     = 0;
    int input_height = 0;

    CRect childRect;
    GetDlgItem(IIDC_EDIT_INPUT)->GetWindowRect(&childRect);
    ScreenToClient(&childRect);

    rect_top     = childRect.top;
    input_height = (windowHeight - rect_top) / 2 - margin;

    rect.left    = childRect.left;
    rect.top     = childRect.top;
    rect.bottom  = rect.top + input_height;
    ChangeSize(IIDC_EDIT_INPUT, rect.left, rect.top, rect.bottom, rect.right - 7);

    rect_top = rect.bottom + margin;

    rect.left   = childRect.left;
    rect.top    = rect_top;
    rect.bottom = rect.top + input_height;
    ChangeSize(IIDC_EDIT_OUTPUT, rect.left, rect.top, rect.bottom, rect.right - 7);
}

void CBaseDialog::ChangeSize(UINT nID, int left, int top, int bottom, int right)
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
        pWnd->MoveWindow(rec);   //ÉìËõ¿Ø¼þ
    }
}
