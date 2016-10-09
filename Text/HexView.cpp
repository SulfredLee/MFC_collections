// HexView.cpp : implementation file
//

#include "stdafx.h"
#include "Text.h"
#include "TextDoc.h"
#include "HexView.h"


// CHexView

IMPLEMENT_DYNCREATE(CHexView, CView)

CHexView::CHexView()
{

}

CHexView::~CHexView()
{
}

BEGIN_MESSAGE_MAP(CHexView, CView)
END_MESSAGE_MAP()


// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CTextDoc* pDoc = (CTextDoc*)GetDocument();

	int        i, j, k, l, nHeight;
	long       n;
	char       temp[10];
	CString    Line;
	TEXTMETRIC tm;

	pDC->GetTextMetrics(&tm);
	nHeight = tm.tmHeight + tm.tmExternalLeading;

	j = pDoc->m_stringArray.GetSize();
	for (i = 0; i < j; i++) {
		wsprintf(temp, "%02x     ", i);
		Line = temp;
		l = pDoc->m_stringArray[i].GetLength();
		for (k = 0; k < l; k++) {
			n = pDoc->m_stringArray[i][k] & 0x00FF;
			wsprintf(temp, "%02lx ", n);
			Line += temp;
		}
		pDC->TextOut(10, i*nHeight, Line);
	}
}


// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHexView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHexView message handlers
