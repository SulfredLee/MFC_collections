
// ScribbleDoc.h : interface of the CScribbleDoc class
//


#pragma once
#include "PenWidthsDlg.h"
/////////////////////////////////////////////////////////////////////////////
// class CStroke
//
// A stroke is a series of connected points in the scribble drawing.
// A scribble document may have multiple strokes.

class CStroke : public CObject
{
public:
	CStroke(UINT nPenWidth);

protected:
	CStroke();
	DECLARE_SERIAL(CStroke)

	// Attributes
protected:
	
public:
	UINT                   m_nPenWidth;    // one pen width applies to entire stroke
	CArray<CPoint, CPoint>  m_pointArray;   // series of connected points
	CRect					m_rectBounding; //smallest rect that surrounds all

	// Operations
public:
	BOOL DrawStroke(CDC* pDC);
	CRect& GetBoundingRect(){ return m_rectBounding; }
	void FinishStroke();

public:
	virtual void Serialize(CArchive& ar);
};

class CScribbleDoc : public CDocument
{
protected: // create from serialization only
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

	// Attributes
protected:
	// The document keeps track of the current pen width on
	// behalf of all views. We'd like the user interface of
	// Scribble to be such that if the user chooses the Draw
	// Thick Line command, it will apply to all views, not just
	// the view that currently has the focus.

	UINT            m_nPenWidth;        // current user-selected pen width
	BOOL            m_bThickPen;        // TRUE if current pen is thick
	UINT            m_nThinWidth;
	UINT            m_nThickWidth;
	CPen            m_penCur;           // pen created according to
	CSize			m_sizeDoc;
	// user-selected pen style (width)
public:
	CTypedPtrList<CObList, CStroke*>     m_strokeList;
	CPen*           GetCurrentPen() { return &m_penCur; }
	CSize			GetDocSize(){ return m_sizeDoc; }

	// Operations
public:
	CStroke* NewStroke();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void		InitDocument();
	void ReplacePen();
// Generated message map functions
protected:
	

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnPenThickOrThin();
	afx_msg void OnUpdatePenThickOrThin(CCmdUI *pCmdUI);
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPenWidths();
};
