// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "Graph.h"
#include "TextView.h"
#include "GraphDoc.h"


// CTextView

IMPLEMENT_DYNCREATE(CTextView, CView)

CTextView::CTextView()
{

}

CTextView::~CTextView()
{
}

BEGIN_MESSAGE_MAP(CTextView, CView)
END_MESSAGE_MAP()


// CTextView drawing

void CTextView::OnDraw(CDC* pDC)
{
	CGraphDoc* pDoc = (CGraphDoc*)GetDocument();
	// TODO: add draw code here
	TEXTMETRIC   tm;
	int          x, y, cy, i;
	char         sz[20];
	pDC->GetTextMetrics(&tm);
	cy = tm.tmHeight;
	pDC->SetTextColor(RGB(255, 0, 0));  // red text
	for (x = 5, y = 5, i = 0; i<DATANUM; i++, y += cy)
	{
		wsprintf(sz, "%d", pDoc->m_intArray[i]);
		pDC->TextOut(x, y, sz, lstrlen(sz));
	}
}


// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTextView message handlers
