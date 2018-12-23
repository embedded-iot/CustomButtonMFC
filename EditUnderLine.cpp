#include "stdafx.h"
#include "EditUnderLine.h"

IMPLEMENT_DYNAMIC(CEditUnderLine, CEdit)

CEditUnderLine::CEditUnderLine()
{
    IsActive = FALSE;
    IsUnderLine = TRUE;
    m_ColorBorder = ::GetSysColor(COLOR_WINDOW);
    m_ColorFocus = ::GetSysColor(COLOR_HIGHLIGHT);
}


CEditUnderLine::~CEditUnderLine()
{
}

BEGIN_MESSAGE_MAP(CEditUnderLine, CEdit)
    ON_WM_NCPAINT()
    ON_WM_KILLFOCUS()
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()

void CEditUnderLine::OnNcPaint()
{
    // TODO: Add your message handler code here
    // Do not call CEdit::OnNcPaint() for painting messages
    CDC *pDC = GetWindowDC();

    //work out the coordinates of the window rectangle,
    CRect rect;
    GetWindowRect(&rect);
    rect.OffsetRect(-rect.left, -rect.top);

    //Draw a single line around the outside
    CBrush brush(m_ColorBorder);
    pDC->FrameRect(&rect, &brush);

    // Draw line bottom rect
    if (IsUnderLine == TRUE)
    {
        rect.DeflateRect(1, 1);
        CPen newPen;
        newPen.CreatePen(PS_SOLID, 1, (IsActive == TRUE ? m_ColorFocus : (::GetSysColor(CTLCOLOR_BTN))));
        CPen *oldPen = pDC->SelectObject(&newPen);
        pDC->MoveTo(rect.left, rect.bottom);
        pDC->LineTo(rect.right, rect.bottom);
        pDC->SelectObject(oldPen);
        newPen.DeleteObject();
    }
    ReleaseDC(pDC);
}

void CEditUnderLine::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);

    // TODO: Add your message handler code here
    CString sText;
    GetWindowText(sText);
    if (sText.IsEmpty())
        IsActive = FALSE;
}

void CEditUnderLine::OnSetFocus(CWnd* pOldWnd)
{
    CEdit::OnSetFocus(pOldWnd);

    // TODO: Add your message handler code here
    IsActive = TRUE;
}