
// dynamic_button_sdiView.h : interface of the Cdynamic_button_sdiView class
//

#pragma once


class Cdynamic_button_sdiView : public CView
{
protected: // create from serialization only
	Cdynamic_button_sdiView();
	DECLARE_DYNCREATE(Cdynamic_button_sdiView)

// Attributes
public:
	Cdynamic_button_sdiDoc* GetDocument() const;

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
	virtual ~Cdynamic_button_sdiView();
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
};

#ifndef _DEBUG  // debug version in dynamic_button_sdiView.cpp
inline Cdynamic_button_sdiDoc* Cdynamic_button_sdiView::GetDocument() const
   { return reinterpret_cast<Cdynamic_button_sdiDoc*>(m_pDocument); }
#endif

