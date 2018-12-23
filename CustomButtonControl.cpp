#include "stdafx.h"
#include "CustomButtonControl.h"

//Normal
#define CLR_FORCEGROUND_DF_NORMAL   RGB(90,95,128)
#define CLR_BACKGROUNG_DF_NORMAL    RGB(213,216,225)
#define CLR_FRAMECOLOR_DF_NORMAL    RGB(90,95,128)
#define CLR_FORCEGROUND_SL_NORMAL   RGB(255,255,255)
#define CLR_BACKGROUNG_SL_NORMAL    RGB(90,95,128)
#define CLR_FRAMECOLOR_SL_NORMAL    RGB(90,95,128)
#define CLR_FORCEGROUND_DIS_NORMAL  RGB(192,192,192)
#define CLR_BACKGROUNG_DIS_NORMAL   RGB(243,243,243)
#define CLR_FRAMECOLOR_DIS_NORMAL   RGB(192,192,192)
#define CLR_BACKGROUNG_OVER_NORMAL  RGB(188,188,188)

//NoBorder
#define CLR_FORCEGROUND_DF_NOBORDER     RGB(255,255,255)
#define CLR_BACKGROUNG_DF_NOBORDER      RGB(118,122,146)
#define CLR_FORCEGROUND_SL_NOBORDER     RGB(255,255,255)
#define CLR_BACKGROUNG_SL_NOBORDER      RGB(97,100,122)
#define CLR_FORCEGROUND_DIS_NOBORDER    RGB(255,255,255)
#define CLR_BACKGROUNG_DIS_NOBORDER     RGB(221,222,228)
#define CLR_BACKGROUNG_OVER_NOBORDER    RGB(90,95,128)

//TextButton
#define CLR_FORCEGROUND_DF_TEXTBTN      RGB(118,122,146)
#define CLR_FORCEGROUND_SL_TEXTBTN      RGB(97,100,122)
#define CLR_FORCEGROUND_DIS_TEXTBTN     RGB(243,243,243)
#define CLR_FORCEGROUND_OVER_TEXTBTN    RGB(90,95,128)

//TabButton
#define COLOR_FORCEGROUND_DF_TABBTN     RGB(64,64,64)
#define COLOR_BACKGROUNG_DF_TABBTN      RGB(242,245,251)
#define COLOR_FRAMECOLOR_DF_TABBTN      RGB(64,64,64)
#define CLR_FORCEGROUND_SL_TABBTN    RGB(64,64,64)
#define CLR_BACKGROUNG_SL_TABBTN     RGB(213,216,225)
#define CLR_FRAMECOLOR_SL_TABBTN     RGB(64,64,64)
#define CLR_FORCEGROUND_DIS_TABBTN   RGB(192,192,192)
#define CLR_BACKGROUNG_DIS_TABBTN    RGB(243,243,243)
#define CLR_FRAMECOLOR_DIS_TABBTN    RGB(192,192,192)
#define CLR_BACKGROUNG_OVER_TABBTN   RGB(225,224,224)

#define CLR_FOREGROUND_NO_ACCTIVE   RGB(187, 187, 187)
#define CLR_FRAMECOLOR_NO_ACCTIVE   RGB(187, 187, 187)

IMPLEMENT_DYNAMIC(CCustomButtonControl, CButton)

CCustomButtonControl::CCustomButtonControl()
{
    m_btnStyle = StyleButton::Normal;
    m_bActive = FALSE;
}


CCustomButtonControl::~CCustomButtonControl()
{
}

void CCustomButtonControl::SetFGColorOver(COLORREF fgClr)
{
    m_foreground = fgClr;
    if (m_hWnd != NULL)
        InvalidateRect(NULL);
}

void CCustomButtonControl::SetBGColorOver(COLORREF bgClr)
{
    m_background = bgClr;
    if (m_hWnd != NULL)
        InvalidateRect(NULL);
}

BOOL CCustomButtonControl::Attach(const UINT nID, CWnd * pParent, StyleButton style, BOOL acctive)
{
    if (!SubclassDlgItem(nID, pParent))
        return FALSE;
    ModifyStyle(0, BS_OWNERDRAW);
    m_btnStyle = style;
    Init();
    SetActive(acctive);

    return TRUE;
}

void CCustomButtonControl::SetBackground(COLORREF bgClr, BOOL reDraw)
{
    m_bgOldOver = bgClr;
    m_background = bgClr;
    if (reDraw == TRUE && m_hWnd != NULL)
        InvalidateRect(NULL);
}

void CCustomButtonControl::SetForeground(COLORREF bgClr, BOOL reDraw)
{
    m_fgOldOver = bgClr;
    m_foreground = bgClr;
    if (reDraw == TRUE && m_hWnd != NULL)
        InvalidateRect(NULL);
}

void CCustomButtonControl::SetColorButton(COLORREF foreground, COLORREF background, BOOL reDraw)
{
    SetBackground(background);
    SetForeground(foreground);
    if (reDraw == TRUE && m_hWnd != NULL)
        InvalidateRect(NULL);
}

void CCustomButtonControl::SetFrameColor(COLORREF frClr, BOOL reDraw)
{
    m_frameColor = frClr;
    if (reDraw == TRUE && m_hWnd != NULL)
        InvalidateRect(NULL);
}

void CCustomButtonControl::SetActive(BOOL active)
{
    if (m_btnStyle == StyleButton::TabButton)
    {
        if (active == TRUE)
        {
            m_bActive = TRUE;
            SetForeground(COLOR_FRAMECOLOR_DF_TABBTN);
            SetFrameColor(COLOR_FRAMECOLOR_DF_TABBTN, 1);
        }
        else
        {
            m_bActive = FALSE;
            SetForeground(CLR_FOREGROUND_NO_ACCTIVE);
            SetFrameColor(CLR_FRAMECOLOR_NO_ACCTIVE, 1);
        }
    }
}

BOOL CCustomButtonControl::GetActive()
{
    return m_btnStyle == StyleButton::TabButton && m_bActive;
}

void CCustomButtonControl::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    UINT state = lpDIS->itemState;
    CRect btnRect;
    btnRect.CopyRect(&lpDIS->rcItem);
    const int bufSize = 512;
    TCHAR buffer[bufSize];
    GetWindowText(buffer, bufSize);

    DrawFilledRect(pDC, btnRect, m_background);
    DrawFrameRect(pDC, btnRect, m_frameColor);
    DrawButtonText(pDC, btnRect, buffer, m_foreground);

    if (state & ODS_FOCUS)
    {
        if (state & ODS_SELECTED)
        {
            DrawFilledRect(pDC, btnRect, m_bgSelect);
            DrawFrameRect(pDC, btnRect, m_frSelect);
            DrawButtonText(pDC, btnRect, buffer, m_fgSelect);
        }
    }
    else if (state & ODS_DISABLED)
    {
        DrawFilledRect(pDC, btnRect, m_bgDisable);
        DrawFrameRect(pDC, btnRect, m_frDisable);
        DrawButtonText(pDC, btnRect, buffer, m_fgDisable);
    }
}


void CCustomButtonControl::DrawFilledRect(CDC *dC, CRect rect, COLORREF bgClr)
{
    if (m_bTransparent == FALSE)
    {
        CBrush bgBrush;
        bgBrush.CreateSolidBrush(bgClr);
        dC->FillRect(rect, &bgBrush);
    }
}

void CCustomButtonControl::DrawFrameRect(CDC * dC, CRect rect, COLORREF frClr)
{
    if (m_bDrawFrame == TRUE)
    {
        CBrush frameBrush;
        frameBrush.CreateSolidBrush(frClr);
        dC->FrameRect(rect, &frameBrush);
    }
}

void CCustomButtonControl::DrawButtonText(CDC * DC, CRect Rect, TCHAR *Buf, COLORREF textColor)
{
    COLORREF prevColor = DC->SetTextColor(textColor);
    DC->SetBkMode(TRANSPARENT);
    DC->DrawText(Buf, _tcslen(Buf), Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    DC->SetTextColor(prevColor);
}

void CCustomButtonControl::Init()
{
    switch (m_btnStyle)
    {
    case CCustomButtonControl::StyleButton::Normal:
        m_bTransparent = FALSE;
        m_bDrawFrame = TRUE;
        m_foreground = CLR_FORCEGROUND_DF_NORMAL;
        m_background = CLR_BACKGROUNG_DF_NORMAL;
        m_frameColor = CLR_FRAMECOLOR_DF_NORMAL;
        m_fgSelect = CLR_FORCEGROUND_SL_NORMAL;
        m_bgSelect = CLR_BACKGROUNG_SL_NORMAL;
        m_frSelect = CLR_FRAMECOLOR_SL_NORMAL;
        m_fgDisable = CLR_FORCEGROUND_DIS_NORMAL;
        m_bgDisable = CLR_BACKGROUNG_DIS_NORMAL;
        m_frDisable = CLR_FRAMECOLOR_DIS_NORMAL;
        m_bgOldOver = m_background;
        m_fgOldOver = m_foreground;
        m_bgOver = CLR_BACKGROUNG_OVER_NORMAL;
        m_fgOver = m_foreground;
        break;
    case CCustomButtonControl::StyleButton::NoBorder:
        m_bTransparent = FALSE;
        m_bDrawFrame = FALSE;
        m_foreground = CLR_FORCEGROUND_DF_NOBORDER;
        m_background = CLR_BACKGROUNG_DF_NOBORDER;
        m_fgSelect = CLR_FORCEGROUND_SL_NOBORDER;
        m_bgSelect = CLR_BACKGROUNG_SL_NOBORDER;
        m_fgDisable = CLR_FORCEGROUND_DIS_NOBORDER;
        m_bgDisable = CLR_BACKGROUNG_DIS_NOBORDER;
        m_bgOldOver = m_background;
        m_fgOldOver = m_foreground;
        m_bgOver = CLR_BACKGROUNG_OVER_NOBORDER;
        m_fgOver = m_foreground;
        break;
    case CCustomButtonControl::StyleButton::TextButton:
        m_bTransparent = TRUE;
        m_bDrawFrame = FALSE;
        m_foreground = CLR_FORCEGROUND_DF_TEXTBTN;
        m_fgSelect = CLR_FORCEGROUND_SL_TEXTBTN;
        m_fgDisable = CLR_FORCEGROUND_DIS_TEXTBTN;
        m_fgOldOver = m_foreground;
        m_fgOver = CLR_FORCEGROUND_OVER_TEXTBTN;
        break;
    case CCustomButtonControl::StyleButton::TabButton:
        m_bTransparent = FALSE;
        m_bDrawFrame = TRUE;
        m_foreground = COLOR_FORCEGROUND_DF_TABBTN;
        m_background = COLOR_BACKGROUNG_DF_TABBTN;
        m_frameColor = COLOR_FRAMECOLOR_DF_TABBTN;
        m_fgSelect = CLR_FORCEGROUND_SL_TABBTN;
        m_bgSelect = CLR_BACKGROUNG_SL_TABBTN;
        m_frSelect = CLR_FRAMECOLOR_SL_TABBTN;
        m_fgDisable = CLR_FORCEGROUND_DIS_TABBTN;
        m_bgDisable = CLR_BACKGROUNG_DIS_TABBTN;
        m_frDisable = CLR_FRAMECOLOR_DIS_TABBTN;
        m_bgOldOver = m_background;
        m_fgOldOver = m_foreground;
        m_bgOver = CLR_BACKGROUNG_OVER_TABBTN;
        m_fgOver = CLR_FOREGROUND_NO_ACCTIVE;
        break;
    default:
        break;
    }
}


BEGIN_MESSAGE_MAP(CCustomButtonControl, CButton)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEHOVER()
    ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CCustomButtonControl::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    TRACKMOUSEEVENT tme = { 0 };
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_HOVER | TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    tme.dwHoverTime = 10;  // HOVER_DEFAULT, or the hover timeout in milliseconds.
    ::TrackMouseEvent(&tme);

    CButton::OnMouseMove(nFlags, point);
}


void CCustomButtonControl::OnMouseHover(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (m_btnStyle == StyleButton::TextButton)
    {
        SetFGColorOver(m_fgOver);
    }
    SetBGColorOver(m_bgOver);
    CButton::OnMouseHover(nFlags, point);
}


void CCustomButtonControl::OnMouseLeave()
{
    // TODO: Add your message handler code here and/or call default
    SetColorButton(m_fgOldOver, m_bgOldOver);
    CButton::OnMouseLeave();
}
