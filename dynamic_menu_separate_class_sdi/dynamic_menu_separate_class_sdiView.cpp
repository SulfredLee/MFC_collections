
// dynamic_menu_separate_class_sdiView.cpp : implementation of the Cdynamic_menu_separate_class_sdiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dynamic_menu_separate_class_sdi.h"
#endif

#include "dynamic_menu_separate_class_sdiDoc.h"
#include "dynamic_menu_separate_class_sdiView.h"
#include "MainFrm.h"
#include "MenuXP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdynamic_menu_separate_class_sdiView

IMPLEMENT_DYNCREATE(Cdynamic_menu_separate_class_sdiView, CView)

BEGIN_MESSAGE_MAP(Cdynamic_menu_separate_class_sdiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cdynamic_menu_separate_class_sdiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

// Cdynamic_menu_separate_class_sdiView construction/destruction

Cdynamic_menu_separate_class_sdiView::Cdynamic_menu_separate_class_sdiView()
{
	// TODO: add construction code here

}

Cdynamic_menu_separate_class_sdiView::~Cdynamic_menu_separate_class_sdiView()
{
}

BOOL Cdynamic_menu_separate_class_sdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cdynamic_menu_separate_class_sdiView drawing

void Cdynamic_menu_separate_class_sdiView::OnDraw(CDC* /*pDC*/)
{
	Cdynamic_menu_separate_class_sdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cdynamic_menu_separate_class_sdiView printing


void Cdynamic_menu_separate_class_sdiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cdynamic_menu_separate_class_sdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cdynamic_menu_separate_class_sdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cdynamic_menu_separate_class_sdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cdynamic_menu_separate_class_sdiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cdynamic_menu_separate_class_sdiView::OnContextMenu(CWnd* pWnd, CPoint point)
{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif

	CMainFrame* pMain = (CMainFrame*)GetParentFrame();
	pMain->OnContextMenu(pWnd, point);		
}


// Cdynamic_menu_separate_class_sdiView diagnostics

#ifdef _DEBUG
void Cdynamic_menu_separate_class_sdiView::AssertValid() const
{
	CView::AssertValid();
}

void Cdynamic_menu_separate_class_sdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdynamic_menu_separate_class_sdiDoc* Cdynamic_menu_separate_class_sdiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdynamic_menu_separate_class_sdiDoc)));
	return (Cdynamic_menu_separate_class_sdiDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdynamic_menu_separate_class_sdiView message handlers


void Cdynamic_menu_separate_class_sdiView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	

	CView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

