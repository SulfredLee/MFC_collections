// PenWidthsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "PenWidthsDlg.h"
#include "afxdialogex.h"


// CPenWidthsDlg dialog

IMPLEMENT_DYNAMIC(CPenWidthsDlg, CDialogEx)

CPenWidthsDlg::CPenWidthsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPenWidthsDlg::IDD, pParent)
	, m_nThickWidth(0)
	, m_nThinWidth(0)
{

}

CPenWidthsDlg::~CPenWidthsDlg()
{
}

void CPenWidthsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_THICK_PEN_WIDTH, m_nThickWidth);
	DDX_Text(pDX, IDC_THIN_PEN_WIDTH, m_nThinWidth);
	DDV_MinMaxInt(pDX, m_nThickWidth, 1, 20);
	DDV_MinMaxInt(pDX, m_nThinWidth, 1, 20);
}


BEGIN_MESSAGE_MAP(CPenWidthsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PEN_WIDTHS, &CPenWidthsDlg::OnBnClickedButtonPenWidths)
END_MESSAGE_MAP()


// CPenWidthsDlg message handlers


void CPenWidthsDlg::OnBnClickedButtonPenWidths()
{
	// TODO: Add your control notification handler code here
}
