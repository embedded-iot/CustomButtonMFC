
// CustomButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomButton.h"
#include "CustomButtonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomButtonDlg dialog



CCustomButtonDlg::CCustomButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CUSTOMBUTTON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBB_ID, m_CtrlID);
	DDX_Control(pDX, IDC_ED_PW, m_CtrlPW);
}

BEGIN_MESSAGE_MAP(CCustomButtonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BTN_CHECK, &CCustomButtonDlg::OnBnClickedBtnCheck)
    ON_BN_CLICKED(IDC_BTN_SETCL, &CCustomButtonDlg::OnBnClickedBtnSetcl)
    ON_BN_CLICKED(IDC_BTN_1, &CCustomButtonDlg::OnBnClickedBtn1)
    ON_BN_CLICKED(IDC_BTN_2, &CCustomButtonDlg::OnBnClickedBtn2)
    ON_BN_CLICKED(IDC_BTN_LOGIN, &CCustomButtonDlg::OnBnClickedBtnLogin)
END_MESSAGE_MAP()


// CCustomButtonDlg message handlers

BOOL CCustomButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

    m_brush.CreateSolidBrush(RGB(255, 255, 255));
    m_CtrlLogin.Attach(IDC_BTN_LOGIN, this, CCustomButtonControl::StyleButton::Normal);
    m_btn1.Attach(IDC_BTN_1, this, CCustomButtonControl::StyleButton::TabButton,TRUE);
    m_btn2.Attach(IDC_BTN_2, this, CCustomButtonControl::StyleButton::TabButton);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCustomButtonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomButtonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CCustomButtonDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    //HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here

    // TODO:  Return a different brush if the default is not desired
    return m_brush;
}


void CCustomButtonDlg::OnBnClickedBtnCheck()
{
    // TODO: Add your control notification handler code here
    CString strCheck;
    GetDlgItemText(IDC_BTN_CHECK, strCheck);
    if (strCheck == L"Enable")
    {
        GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
        SetDlgItemText(IDC_BTN_CHECK, L"Disable");
    }
    else
    {
        GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
        SetDlgItemText(IDC_BTN_CHECK, L"Enable");
    }
}


void CCustomButtonDlg::OnBnClickedBtnSetcl()
{
    // TODO: Add your control notification handler code here
    if (m_btn1.GetActive() == TRUE)
        AfxMessageBox(L"1 acc");
    else
        AfxMessageBox(L"1 No acc");
    if (m_btn2.GetActive() == TRUE)
        AfxMessageBox(L"2 acc");
    else
        AfxMessageBox(L"2 No acc");

}


void CCustomButtonDlg::OnBnClickedBtn1()
{
    // TODO: Add your control notification handler code here
    m_btn1.SetActive(1);
    m_btn2.SetActive(0);
}


void CCustomButtonDlg::OnBnClickedBtn2()
{
    // TODO: Add your control notification handler code here
    m_btn1.SetActive(0);
    m_btn2.SetActive(1);
}


void CCustomButtonDlg::OnBnClickedBtnLogin()
{
    // TODO: Add your control notification handler code here
    if (m_CtrlLogin.GetActive() == TRUE)
        m_CtrlLogin.SetActive(0);
    else
        m_CtrlLogin.SetActive(1);
}
