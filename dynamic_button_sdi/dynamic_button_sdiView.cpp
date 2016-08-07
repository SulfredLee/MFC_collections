
// dynamic_button_sdiView.cpp : implementation of the Cdynamic_button_sdiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dynamic_button_sdi.h"
#endif

#include "dynamic_button_sdiDoc.h"
#include "dynamic_button_sdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdynamic_button_sdiView

IMPLEMENT_DYNCREATE(Cdynamic_button_sdiView, CView)

BEGIN_MESSAGE_MAP(Cdynamic_button_sdiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cdynamic_button_sdiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(MYBUTTONID, OnMyBN_Click)
END_MESSAGE_MAP()

// Cdynamic_button_sdiView construction/destruction

Cdynamic_button_sdiView::Cdynamic_button_sdiView()
{
	// TODO: add construction code here
}

Cdynamic_button_sdiView::~Cdynamic_button_sdiView()
{
}

BOOL Cdynamic_button_sdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cdynamic_button_sdiView drawing

void Cdynamic_button_sdiView::OnDraw(CDC* pDC)
{
	Cdynamic_button_sdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here	
	
}


// Cdynamic_button_sdiView printing

void Cdynamic_button_sdiView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_Button.Create(_T("Rearrange"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 128, 32), this, MYBUTTONID); // here will create a button
	RepositionButton(); // here will redraw a button and replace the button, this can be used for scrolling view application
}
void Cdynamic_button_sdiView::RepositionButton()
{
	//work out button position you need
	int x, y, width, height;
	x = 10;
	y = 10;
	width = 128;
	height = 32;
	m_Button.MoveWindow(x, y, width, height);
}
void Cdynamic_button_sdiView::OnMyBN_Click()
{
	m_Button.EnableWindow(FALSE);
}
void Cdynamic_button_sdiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cdynamic_button_sdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cdynamic_button_sdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cdynamic_button_sdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cdynamic_button_sdiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cdynamic_button_sdiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cdynamic_button_sdiView diagnostics

#ifdef _DEBUG
void Cdynamic_button_sdiView::AssertValid() const
{
	CView::AssertValid();
}

void Cdynamic_button_sdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdynamic_button_sdiDoc* Cdynamic_button_sdiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdynamic_button_sdiDoc)));
	return (Cdynamic_button_sdiDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdynamic_button_sdiView message handlers
