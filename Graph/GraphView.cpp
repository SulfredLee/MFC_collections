
// GraphView.cpp : implementation of the CGraphView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Graph.h"
#endif

#include "GraphDoc.h"
#include "GraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CView)

BEGIN_MESSAGE_MAP(CGraphView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphView construction/destruction

CGraphView::CGraphView()
{
	// TODO: add construction code here

}

CGraphView::~CGraphView()
{
}

BOOL CGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGraphView drawing

void CGraphView::OnDraw(CDC* pDC)
{
	CGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int          cxDot, cxDotSpacing, cyDot, cxGraph, cyGraph, x, y, i;
	RECT         rc;

	CPen   pen(PS_SOLID, 1, RGB(255, 0, 0)); // red pen
	CBrush brush(RGB(255, 0, 0));             // red brush
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	CPen*   pOldPen = pDC->SelectObject(&pen);

	cxGraph = 100;
	cyGraph = DATAMAX;  // defined in resource.h

	this->GetClientRect(&rc);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0, 0);
	pDC->SetViewportOrg(10, rc.bottom - 10);
	pDC->SetWindowExt(cxGraph, cyGraph);
	pDC->SetViewportExt(rc.right - 20, -(rc.bottom - 20));

	// 我們希望圖形佔滿視窗的整個可用空間（以水平方向為準）
	// 並希望曲線點的寬度是點間距寬度的 1.2，
	// 所以 (dot_spacing + dot_width) * num_datapoints = graph_width
	// 亦即 dot_spacing * 3/2  * num_datapoints = graph_width
	// 亦即 dot_spacing = graph_width / num_datapoints * 2/3

	cxDotSpacing = (2 * cxGraph) / (3 * DATANUM);
	cxDot = cxDotSpacing / 2;
	if (cxDot<3)  cxDot = 3;
	cyDot = cxDot;

	// 座標軸
	pDC->MoveTo(0, 0);
	pDC->LineTo(0, cyGraph);
	pDC->MoveTo(0, 0);
	pDC->LineTo(cxGraph, 0);

	// 畫出資料點
	pDC->SelectObject(::GetStockObject(NULL_PEN));
	for (x = 0 + cxDotSpacing, y = 0, i = 0; i<DATANUM; i++, x += cxDot + cxDotSpacing)
		pDC->Rectangle(x, y + pDoc->m_intArray[i],
		x + cxDot, y + pDoc->m_intArray[i] - cyDot);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


// CGraphView printing


void CGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphView diagnostics

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphDoc* CGraphView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphDoc)));
	return (CGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphView message handlers
