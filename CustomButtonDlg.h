
// CustomButtonDlg.h : header file
//

#pragma once
#include "EditUnderLine.h"
#include "ComboBoxUnderLine.h"
#include "CustomButtonControl.h"
#include "afxwin.h"

// CCustomButtonDlg dialog
class CCustomButtonDlg : public CDialogEx
{
// Construction
public:
	CCustomButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOMBUTTON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBoxUnderLine m_CtrlID;
	CEditUnderLine m_CtrlPW;
	CCustomButtonControl m_CtrlLogin;
    CCustomButtonControl m_btn1;
    CCustomButtonControl m_btn2;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    CBrush m_brush;
    afx_msg void OnBnClickedBtnCheck();
    afx_msg void OnBnClickedBtnSetcl();
    afx_msg void OnBnClickedBtn1();
    afx_msg void OnBnClickedBtn2();
    afx_msg void OnBnClickedBtnLogin();
};
