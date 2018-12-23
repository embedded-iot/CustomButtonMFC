#pragma once
#include "afxwin.h"

class CCustomButtonControl :
    public CButton
{
    DECLARE_DYNAMIC(CCustomButtonControl)

    enum StyleButton
    {
        Normal,
        NoBorder,
        TextButton,
        TabButton
    };

public:
    CCustomButtonControl();
    virtual ~CCustomButtonControl();
     
private:
    StyleButton m_btnStyle;
    BOOL        m_bTransparent;
    BOOL        m_bDrawFrame;
    COLORREF    m_foreground, m_background, m_frameColor;
    COLORREF    m_fgSelect, m_bgSelect, m_frSelect;
    COLORREF    m_fgDisable, m_bgDisable, m_frDisable;
    COLORREF    m_fgOver, m_bgOver;
    COLORREF    m_fgOldOver, m_bgOldOver;
    void        SetFGColorOver(COLORREF fgClr);
    void        SetBGColorOver(COLORREF bgClr);
    BOOL        m_bActive;

public:
    BOOL        Attach(const UINT nID, CWnd * pParent, StyleButton style = StyleButton::Normal, BOOL acctive = FALSE);
    void        SetBackground(COLORREF bgClr, BOOL reDraw = FALSE);
    void        SetForeground(COLORREF bgClr, BOOL reDraw = FALSE);
    void        SetFrameColor(COLORREF frClr, BOOL reDraw = FALSE);
    void        SetColorButton(COLORREF foreground, COLORREF background, BOOL reDraw = TRUE);
    void        SetActive(BOOL active = TRUE);
    BOOL        GetActive();

protected:
    virtual void    DrawItem(LPDRAWITEMSTRUCT lpDIS);
    void            DrawFilledRect(CDC *dC, CRect rect, COLORREF bgClr);
    void            DrawFrameRect(CDC *dC, CRect rect, COLORREF frClr);
    void            DrawButtonText(CDC *DC, CRect Rect, TCHAR *Buf, COLORREF textColor);
    void            Init();

public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMouseHover(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
};