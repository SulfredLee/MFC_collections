#pragma once


// CTextView view

class CTextView : public CView
{
	DECLARE_DYNCREATE(CTextView)

protected:
	CTextView();           // protected constructor used by dynamic creation
	virtual ~CTextView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


