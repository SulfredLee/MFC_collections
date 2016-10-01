
// dynamic_controls_within_list_controlView.cpp : implementation of the Cdynamic_controls_within_list_controlView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dynamic_controls_within_list_control.h"
#endif

#include "dynamic_controls_within_list_controlDoc.h"
#include "dynamic_controls_within_list_controlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdynamic_controls_within_list_controlView

IMPLEMENT_DYNCREATE(Cdynamic_controls_within_list_controlView, CFormView)

BEGIN_MESSAGE_MAP(Cdynamic_controls_within_list_controlView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cdynamic_controls_within_list_controlView construction/destruction

Cdynamic_controls_within_list_controlView::Cdynamic_controls_within_list_controlView()
	: CFormView(Cdynamic_controls_within_list_controlView::IDD)
{
	// TODO: add construction code here

}

Cdynamic_controls_within_list_controlView::~Cdynamic_controls_within_list_controlView()
{
}

void Cdynamic_controls_within_list_controlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL Cdynamic_controls_within_list_controlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void Cdynamic_controls_within_list_controlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void Cdynamic_controls_within_list_controlView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cdynamic_controls_within_list_controlView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cdynamic_controls_within_list_controlView diagnostics

#ifdef _DEBUG
void Cdynamic_controls_within_list_controlView::AssertValid() const
{
	CFormView::AssertValid();
}

void Cdynamic_controls_within_list_controlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

Cdynamic_controls_within_list_controlDoc* Cdynamic_controls_within_list_controlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdynamic_controls_within_list_controlDoc)));
	return (Cdynamic_controls_within_list_controlDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdynamic_controls_within_list_controlView message handlers
