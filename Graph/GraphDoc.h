
// GraphDoc.h : interface of the CGraphDoc class
//


#pragma once


class CGraphDoc : public CDocument
{
protected: // create from serialization only
	CGraphDoc();
	DECLARE_DYNCREATE(CGraphDoc)

// Attributes
public:
	CArray<int, int> m_intArray;
// Operations
public:
	void SetValue(int i0, int i1, int i2, int i3, int i4,
		int i5, int i6, int i7, int i8, int i9);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnGraphData1();
	afx_msg void OnUpdateGraphData1(CCmdUI *pCmdUI);
	afx_msg void OnGraphData2();
	afx_msg void OnUpdateGraphData2(CCmdUI *pCmdUI);
	afx_msg void OnGraphData3();
	afx_msg void OnUpdateGraphData3(CCmdUI *pCmdUI);
};
