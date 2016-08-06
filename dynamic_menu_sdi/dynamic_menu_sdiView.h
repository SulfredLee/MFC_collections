
// dynamic_menu_sdiView.h : interface of the Cdynamic_menu_sdiView class
//

#pragma once

#include <map>
#include <utility>

class Cdynamic_menu_sdiView : public CView
{
protected: // create from serialization only
	Cdynamic_menu_sdiView();
	DECLARE_DYNCREATE(Cdynamic_menu_sdiView)

// Attributes
public:
	Cdynamic_menu_sdiDoc* GetDocument() const;
protected:
// Operations
public:
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cdynamic_menu_sdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewAlex();
	afx_msg void OnUpdateNewAlex(CCmdUI *pCmdUI);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};

#ifndef _DEBUG  // debug version in dynamic_menu_sdiView.cpp
inline Cdynamic_menu_sdiDoc* Cdynamic_menu_sdiView::GetDocument() const
   { return reinterpret_cast<Cdynamic_menu_sdiDoc*>(m_pDocument); }
#endif

