
// dynamic_controls_within_list_controlView.h : interface of the Cdynamic_controls_within_list_controlView class
//

#pragma once

#include "resource.h"


class Cdynamic_controls_within_list_controlView : public CFormView
{
protected: // create from serialization only
	Cdynamic_controls_within_list_controlView();
	DECLARE_DYNCREATE(Cdynamic_controls_within_list_controlView)

public:
	enum{ IDD = IDD_DYNAMIC_CONTROLS_WITHIN_LIST_CONTROL_FORM };

// Attributes
public:
	Cdynamic_controls_within_list_controlDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~Cdynamic_controls_within_list_controlView();
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

#ifndef _DEBUG  // debug version in dynamic_controls_within_list_controlView.cpp
inline Cdynamic_controls_within_list_controlDoc* Cdynamic_controls_within_list_controlView::GetDocument() const
   { return reinterpret_cast<Cdynamic_controls_within_list_controlDoc*>(m_pDocument); }
#endif

