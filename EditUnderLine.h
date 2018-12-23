#pragma once
#include "afxwin.h"

class CEditUnderLine :
    public CEdit
{
    DECLARE_DYNAMIC(CEditUnderLine)

private:
    COLORREF m_ColorFocus;
    COLORREF m_ColorBorder;
    BOOL    IsUnderLine;
    BOOL    IsActive;

public:
    CEditUnderLine();
    ~CEditUnderLine();
    void        SetColorBorder(COLORREF clr) { m_ColorBorder = clr; };
    COLORREF    GetColorBorder() { return m_ColorBorder; };
    void        SetColorUnderLine(COLORREF clr) { m_ColorFocus = clr; };
    COLORREF    GetColorUnderLine() { return m_ColorFocus; };
    void        SetUnderline(BOOL bLine) { IsUnderLine = bLine; };
    BOOL        GetUnderline() { return IsUnderLine; };
    
protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
};
