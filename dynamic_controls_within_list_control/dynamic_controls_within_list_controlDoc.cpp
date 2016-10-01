
// dynamic_controls_within_list_controlDoc.cpp : implementation of the Cdynamic_controls_within_list_controlDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dynamic_controls_within_list_control.h"
#endif

#include "dynamic_controls_within_list_controlDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cdynamic_controls_within_list_controlDoc

IMPLEMENT_DYNCREATE(Cdynamic_controls_within_list_controlDoc, CDocument)

BEGIN_MESSAGE_MAP(Cdynamic_controls_within_list_controlDoc, CDocument)
END_MESSAGE_MAP()


// Cdynamic_controls_within_list_controlDoc construction/destruction

Cdynamic_controls_within_list_controlDoc::Cdynamic_controls_within_list_controlDoc()
{
	// TODO: add one-time construction code here

}

Cdynamic_controls_within_list_controlDoc::~Cdynamic_controls_within_list_controlDoc()
{
}

BOOL Cdynamic_controls_within_list_controlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cdynamic_controls_within_list_controlDoc serialization

void Cdynamic_controls_within_list_controlDoc::Serialize(CArchive& ar)
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
void Cdynamic_controls_within_list_controlDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Cdynamic_controls_within_list_controlDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cdynamic_controls_within_list_controlDoc::SetSearchContent(const CString& value)
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

// Cdynamic_controls_within_list_controlDoc diagnostics

#ifdef _DEBUG
void Cdynamic_controls_within_list_controlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cdynamic_controls_within_list_controlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cdynamic_controls_within_list_controlDoc commands
