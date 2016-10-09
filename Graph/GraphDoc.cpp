
// GraphDoc.cpp : implementation of the CGraphDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Graph.h"
#endif

#include "GraphDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphDoc

IMPLEMENT_DYNCREATE(CGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphDoc, CDocument)
	ON_COMMAND(ID_GRAPH_DATA1, &CGraphDoc::OnGraphData1)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DATA1, &CGraphDoc::OnUpdateGraphData1)
	ON_COMMAND(ID_GRAPH_DATA2, &CGraphDoc::OnGraphData2)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DATA2, &CGraphDoc::OnUpdateGraphData2)
	ON_COMMAND(ID_GRAPH_DATA3, &CGraphDoc::OnGraphData3)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DATA3, &CGraphDoc::OnUpdateGraphData3)
END_MESSAGE_MAP()


// CGraphDoc construction/destruction

CGraphDoc::CGraphDoc()
{
	// TODO: add one-time construction code here
	SetValue(5, 10, 15, 20, 25, 78, 64, 38, 29, 9);
}

CGraphDoc::~CGraphDoc()
{
}

BOOL CGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


void CGraphDoc::SetValue(int i0, int i1, int i2, int i3, int i4,
	int i5, int i6, int i7, int i8, int i9)
{
	m_intArray.SetSize(DATANUM, 0);
	m_intArray[0] = i0;
	m_intArray[1] = i1;
	m_intArray[2] = i2;
	m_intArray[3] = i3;
	m_intArray[4] = i4;
	m_intArray[5] = i5;
	m_intArray[6] = i6;
	m_intArray[7] = i7;
	m_intArray[8] = i8;
	m_intArray[9] = i9;
}

// CGraphDoc serialization

void CGraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CGraphDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CGraphDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGraphDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphDoc diagnostics

#ifdef _DEBUG
void CGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphDoc commands


void CGraphDoc::OnGraphData1()
{
	// TODO: Add your command handler code here
	SetValue(5, 10, 15, 20, 25, 78, 64, 38, 29, 9);
	UpdateAllViews(NULL);
}


void CGraphDoc::OnUpdateGraphData1(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_intArray[0] == 5);
}


void CGraphDoc::OnGraphData2()
{
	// TODO: Add your command handler code here
	SetValue(50, 60, 70, 80, 90, 23, 68, 39, 73, 58);
	UpdateAllViews(NULL);
}


void CGraphDoc::OnUpdateGraphData2(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_intArray[0] == 50);
}


void CGraphDoc::OnGraphData3()
{
	// TODO: Add your command handler code here
	SetValue(12, 20, 8, 17, 28, 37, 93, 45, 78, 29);
	UpdateAllViews(NULL);
}


void CGraphDoc::OnUpdateGraphData3(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_intArray[0] == 12);
}
