
// dynamic_menu_separate_class_sdi.h : main header file for the dynamic_menu_separate_class_sdi application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cdynamic_menu_separate_class_sdiApp:
// See dynamic_menu_separate_class_sdi.cpp for the implementation of this class
//

class Cdynamic_menu_separate_class_sdiApp : public CWinAppEx
{
public:
	Cdynamic_menu_separate_class_sdiApp();


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

extern Cdynamic_menu_separate_class_sdiApp theApp;
