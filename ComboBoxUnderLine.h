#pragma once
#include "afxwin.h"

class CComboBoxUnderLine :
    public CComboBox
{
    DECLARE_DYNAMIC(CComboBoxUnderLine)

private:
    COLORREF m_ColorFocus;
    COLORREF m_ColorBorder;
    BOOL    IsUnderLine;
    BOOL    IsActive;

public:
    CComboBoxUnderLine();
    ~CComboBoxUnderLine();
    void        SetColorBorder(COLORREF clr) { m_ColorBorder = clr; };
    COLORREF    GetColorBorder() { return m_ColorBorder; };
    void        SetColorUnderLine(COLORREF clr) { m_ColorFocus = clr; };
    COLORREF    GetColorUnderLine() { return m_ColorFocus; };
    void        SetUnderline(BOOL bLine) { IsUnderLine = bLine; };
    BOOL        GetUnderline() { return IsUnderLine; };

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg void OnCbnKillfocus();
    afx_msg void OnCbnSetfocus();
};