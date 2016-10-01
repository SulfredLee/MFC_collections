
// dynamic_controls_within_list_control.h : main header file for the dynamic_controls_within_list_control application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cdynamic_controls_within_list_controlApp:
// See dynamic_controls_within_list_control.cpp for the implementation of this class
//

class Cdynamic_controls_within_list_controlApp : public CWinAppEx
{
public:
	Cdynamic_controls_within_list_controlApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cdynamic_controls_within_list_controlApp theApp;
