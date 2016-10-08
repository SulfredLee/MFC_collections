#pragma once


// CPenWidthsDlg dialog

class CPenWidthsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPenWidthsDlg)

public:
	int m_nThickWidth;
	int m_nThinWidth;

public:
	CPenWidthsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenWidthsDlg();

// Dialog Data
	enum { IDD = IDD_PEN_WIDTHS };

	afx_msg void OnBnClickedButtonPenWidths();
	DECLARE_MESSAGE_MAP()
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
};
