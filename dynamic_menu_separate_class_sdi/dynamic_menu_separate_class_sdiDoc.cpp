
// dynamic_menu_separate_class_sdiDoc.cpp : implementation of the Cdynamic_menu_separate_class_sdiDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "dynamic_menu_separate_class_sdi.h"
#endif

#include "dynamic_menu_separate_class_sdiDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cdynamic_menu_separate_class_sdiDoc

IMPLEMENT_DYNCREATE(Cdynamic_menu_separate_class_sdiDoc, CDocument)

BEGIN_MESSAGE_MAP(Cdynamic_menu_separate_class_sdiDoc, CDocument)
END_MESSAGE_MAP()


// Cdynamic_menu_separate_class_sdiDoc construction/destruction

Cdynamic_menu_separate_class_sdiDoc::Cdynamic_menu_separate_class_sdiDoc()
{
	// TODO: add one-time construction code here

}

Cdynamic_menu_separate_class_sdiDoc::~Cdynamic_menu_separate_class_sdiDoc()
{
}

BOOL Cdynamic_menu_separate_class_sdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cdynamic_menu_separate_class_sdiDoc serialization

void Cdynamic_menu_separate_class_sdiDoc::Serialize(CArchive& ar)
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
void Cdynamic_menu_separate_class_sdiDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Cdynamic_menu_separate_class_sdiDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cdynamic_menu_separate_class_sdiDoc::SetSearchContent(const CString& value)
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

// Cdynamic_menu_separate_class_sdiDoc diagnostics

#ifdef _DEBUG
void Cdynamic_menu_separate_class_sdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cdynamic_menu_separate_class_sdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cdynamic_menu_separate_class_sdiDoc commands
