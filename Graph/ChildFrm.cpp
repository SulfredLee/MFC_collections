
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Graph.h"

#include "ChildFrm.h"
#include "BarView.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	// �����R�A���������ϡA��C�� 1�A�a�欰 2�C
	m_wndSplitter1.CreateStatic(this, 1, 2);

	// ���͵����Ϫ��Ĥ@�ӵ��f�]�и� 0,0�^�� view �����A�ĥ� CTextView�C
	m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CTextView),
		CSize(300, 0), pContext);

	// �b�W�@�ӵ��f�������R�A���������СA��C�� 2�A�a�欰 1�C
	m_wndSplitter2.CreateStatic(&m_wndSplitter1, 2, 1,
		WS_CHILD | WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0, 1));

	// ���͵����Ъ��Ĥ@�ӵ��f�]�и� 0,0�^�� view �����A�ĥ� CBarView�C
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CBarView),
		CSize(0, 150), pContext);

	// ���͵����Ъ��ĤG�ӵ��f�]�и� 1,0�^�� view �����A�ĥ� CGraphView�C
	m_wndSplitter2.CreateView(1, 0, pContext->m_pNewViewClass,
		CSize(0, 0), pContext);

	// �]�w active pane
	SetActiveView((CView*)m_wndSplitter1.GetPane(0, 0));
	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers
