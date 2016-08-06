
// dynamic_menu_sdiView.cpp : implementation of the Cdynamic_menu_sdiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dynamic_menu_sdi.h"
#endif

#include "dynamic_menu_sdiDoc.h"
#include "dynamic_menu_sdiView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdynamic_menu_sdiView

IMPLEMENT_DYNCREATE(Cdynamic_menu_sdiView, CView)

BEGIN_MESSAGE_MAP(Cdynamic_menu_sdiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cdynamic_menu_sdiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_NEW_ALEX, &Cdynamic_menu_sdiView::OnNewAlex)
	ON_UPDATE_COMMAND_UI(ID_NEW_ALEX, &Cdynamic_menu_sdiView::OnUpdateNewAlex)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

// Cdynamic_menu_sdiView construction/destruction

Cdynamic_menu_sdiView::Cdynamic_menu_sdiView()
{
	// TODO: add construction code here

	
}

Cdynamic_menu_sdiView::~Cdynamic_menu_sdiView()
{
}

BOOL Cdynamic_menu_sdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cdynamic_menu_sdiView drawing

void Cdynamic_menu_sdiView::OnDraw(CDC* /*pDC*/)
{
	Cdynamic_menu_sdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cdynamic_menu_sdiView printing


void Cdynamic_menu_sdiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cdynamic_menu_sdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cdynamic_menu_sdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cdynamic_menu_sdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cdynamic_menu_sdiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cdynamic_menu_sdiView::OnContextMenu(CWnd* pWnd, CPoint point)
{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
	
	CMainFrame* pMain = (CMainFrame*)GetParentFrame();
	pMain->OnContextMenu(pWnd, point);
}

// Cdynamic_menu_sdiView diagnostics

#ifdef _DEBUG
void Cdynamic_menu_sdiView::AssertValid() const
{
	CView::AssertValid();
}

void Cdynamic_menu_sdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdynamic_menu_sdiDoc* Cdynamic_menu_sdiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdynamic_menu_sdiDoc)));
	return (Cdynamic_menu_sdiDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdynamic_menu_sdiView message handlers


void Cdynamic_menu_sdiView::OnNewAlex()
{
	// TODO: Add your command handler code here
}


void Cdynamic_menu_sdiView::OnUpdateNewAlex(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void Cdynamic_menu_sdiView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	CView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
