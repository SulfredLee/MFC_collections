
// ScribbleDoc.cpp : implementation of the CScribbleDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Scribble.h"
#endif

#include "ScribbleDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, &CScribbleDoc::OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, &CScribbleDoc::OnUpdatePenThickOrThin)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CScribbleDoc::OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CScribbleDoc::OnUpdateEditClearAll)
	ON_COMMAND(ID_PEN_WIDTHS, &CScribbleDoc::OnPenWidths)
END_MESSAGE_MAP()


// CScribbleDoc construction/destruction

CScribbleDoc::CScribbleDoc()
{
	// TODO: add one-time construction code here

}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	InitDocument();
	return TRUE;
}

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}

void CScribbleDoc::DeleteContents()
{
	while (!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}
	CDocument::DeleteContents();
}

void CScribbleDoc::InitDocument()
{
	m_bThickPen = FALSE;
	m_nThinWidth = 2;   // default thin pen is 2 pixels wide
	m_nThickWidth = 5;  // default thick pen is 5 pixels wide
	ReplacePen();       // initialize pen according to current width
	// default document size
	m_sizeDoc = CSize(800, 900);
}

// CScribbleDoc serialization

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_sizeDoc;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_sizeDoc;
	}
	m_strokeList.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CScribbleDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CScribbleDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CScribbleDoc::SetSearchContent(const CString& value)
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

// CScribbleDoc diagnostics

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CScribbleDoc commands

CStroke* CScribbleDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();  // Mark the document as having been modified, for
	// purposes of confirming File Close.
	return pStrokeItem;
}


/////////////////////////////////////////////////////////////////////////////
// CStroke

IMPLEMENT_SERIAL(CStroke, CObject, 2) // we change the value to 2, so that when app read old data file, it knows the file is too old
CStroke::CStroke()
{
	// This empty constructor should be used by serialization only
}

CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

void CStroke::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_rectBounding;
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	}
	else
	{
		ar >> m_rectBounding;
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize(ar);
	}
}

void CStroke::FinishStroke()
{
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.

	if (m_pointArray.GetSize() == 0)
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = m_pointArray[0];
	m_rectBounding = CRect(pt.x, pt.y, pt.x, pt.y);

	for (int i = 1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = m_pointArray[i];
		m_rectBounding.left = min(m_rectBounding.left, pt.x);
		m_rectBounding.right = max(m_rectBounding.right, pt.x);
		m_rectBounding.top = min(m_rectBounding.top, pt.y);
		m_rectBounding.bottom = max(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, m_nPenWidth));
	return;
}

BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0, 0, 0)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(m_pointArray[0]);
	for (int i = 1; i < m_pointArray.GetSize(); i++)
	{
		pDC->LineTo(m_pointArray[i]);
	}

	pDC->SelectObject(pOldPen);
	return TRUE;
}

void CScribbleDoc::OnPenThickOrThin()
{
	// TODO: Add your command handler code here
	// Toggle the state of the pen between thin or thick.
	m_bThickPen = !m_bThickPen;

	// Change the current pen to reflect the new user-specified width.
	ReplacePen();
}

void CScribbleDoc::ReplacePen()
{
	m_nPenWidth = m_bThickPen ? m_nThickWidth : m_nThinWidth;

	// Change the current pen to reflect the new user-specified width.
	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0, 0, 0)); // solid black
}

void CScribbleDoc::OnUpdatePenThickOrThin(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Add check mark to Draw Thick Line menu item, if the current
	// pen width is "thick".
	pCmdUI->SetCheck(m_bThickPen);
}


void CScribbleDoc::OnEditClearAll()
{
	// TODO: Add your command handler code here
	DeleteContents();
	SetModifiedFlag();  // Mark the document as having been modified, for
	// purposes of confirming File Close.
	UpdateAllViews(NULL);
}


void CScribbleDoc::OnUpdateEditClearAll(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Enable the command user interface object (menu item or tool bar
	// button) if the document is non-empty, i.e., has at least one stroke.
	pCmdUI->Enable(!m_strokeList.IsEmpty());
}


void CScribbleDoc::OnPenWidths()
{
	// TODO: Add your command handler code here
	CPenWidthsDlg dlg;
	// Initialize dialog data
	dlg.m_nThinWidth = m_nThinWidth;
	dlg.m_nThickWidth = m_nThickWidth;
	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		m_nThinWidth = dlg.m_nThinWidth;
		m_nThickWidth = dlg.m_nThickWidth;
		// Update the pen that is used by views when drawing new strokes,
		// to reflect the new pen width definitions for "thick" and "thin"
		ReplacePen();
	}
}

