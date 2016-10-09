// NewDoc.cpp : implementation file
//

#include "stdafx.h"
#include "Graph.h"
#include "NewDoc.h"


// CNewDoc

IMPLEMENT_DYNCREATE(CNewDoc, CDocument)

CNewDoc::CNewDoc()
{
}

BOOL CNewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CNewDoc::~CNewDoc()
{
}


BEGIN_MESSAGE_MAP(CNewDoc, CDocument)
END_MESSAGE_MAP()


// CNewDoc diagnostics

#ifdef _DEBUG
void CNewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CNewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CNewDoc serialization

void CNewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}
#endif


// CNewDoc commands
