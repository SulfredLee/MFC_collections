
// dynamic_menu_separate_class_sdiDoc.h : interface of the Cdynamic_menu_separate_class_sdiDoc class
//


#pragma once


class Cdynamic_menu_separate_class_sdiDoc : public CDocument
{
protected: // create from serialization only
	Cdynamic_menu_separate_class_sdiDoc();
	DECLARE_DYNCREATE(Cdynamic_menu_separate_class_sdiDoc)

// Attributes
public:

// Operations
public:

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
	virtual ~Cdynamic_menu_separate_class_sdiDoc();
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
};
