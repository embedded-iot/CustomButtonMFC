#include "stdafx.h"
#include "ComboBoxUnderLine.h"

IMPLEMENT_DYNAMIC(CComboBoxUnderLine, CComboBox)

CComboBoxUnderLine::CComboBoxUnderLine()
{
    IsActive = FALSE;
    IsUnderLine = TRUE;
    m_ColorBorder = ::GetSysColor(COLOR_WINDOW);
    m_ColorFocus = ::GetSysColor(COLOR_HIGHLIGHT);
}


CComboBoxUnderLine::~CComboBoxUnderLine()
{
}

BEGIN_MESSAGE_MAP(CComboBoxUnderLine, CComboBox)
    ON_WM_PAINT()
    ON_CONTROL_REFLECT(CBN_KILLFOCUS, &CComboBoxUnderLine::OnCbnKillfocus)
    ON_CONTROL_REFLECT(CBN_SETFOCUS, &CComboBoxUnderLine::OnCbnSetfocus)
END_MESSAGE_MAP()

void CComboBoxUnderLine::OnPaint()
{
    CPaintDC dc(this);
    CRect rect;
    GetClientRect(rect);

    // draw borders combobox
    dc.Draw3dRect(rect, m_ColorBorder, m_ColorBorder);
    rect.DeflateRect(1, 1);

    /// Draw line bottom rect
    if (IsUnderLine == TRUE)
    {
        rect.DeflateRect(1, 1);
        CPen newPen;
        newPen.CreatePen(PS_SOLID, 1, (IsActive == TRUE ? m_ColorFocus : ::GetSysColor(CTLCOLOR_BTN)));
        CPen *oldPen = dc.SelectObject(&newPen);
        dc.MoveTo(rect.left, rect.bottom);
        dc.LineTo(rect.right, rect.bottom);
        dc.SelectObject(oldPen);
        newPen.DeleteObject();
    }

    // draw dropdown button only if CBS_DROPDOWN or CBS_DROPDOWNLIST style set 
    if ((GetStyle() & 0x0000000f) > CBS_SIMPLE)
    {
        CRect rectBtn = rect;
        rectBtn.left = rectBtn.right - ::GetSystemMetrics(SM_CXHTHUMB);
        BOOL bPressed = FALSE;
        if (GetKeyState(VK_LBUTTON) < 0)
        {
            CPoint point;
            ::GetCursorPos(&point);
            ScreenToClient(&point);
            if (rectBtn.PtInRect(point))
                bPressed = TRUE;
        }

        // draw button combobox
        dc.DrawFrameControl(rectBtn, DFC_MENU, DFCS_MENUARROW | (bPressed ? DFCS_FLAT | DFCS_PUSHED : 0));
        rect.right = rectBtn.left;
    }
    if ((GetStyle() & 0x0000000f) == CBS_DROPDOWNLIST)
    {
        CString sText;
        GetWindowText(sText);
        // fill rect if none text is displayed 
        if (sText.IsEmpty())
            dc.FillSolidRect(rect, m_ColorBorder);
        else
            dc.DrawText(sText, -1, &rect, DT_SINGLELINE | DT_LEFT);
    }
}


void CComboBoxUnderLine::OnCbnKillfocus()
{
    // TODO: Add your control notification handler code here
    CString sText;
    GetWindowText(sText);
    if (sText.IsEmpty())
        IsActive = FALSE;
}

void CComboBoxUnderLine::OnCbnSetfocus()
{
    // TODO: Add your control notification handler code here
    IsActive = TRUE;
}