
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "dynamic_menu_sdi.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
ON_WM_DRAWITEM()
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_NEW_APPLE, &CMainFrame::OnNewApple)
ON_UPDATE_COMMAND_UI(ID_NEW_APPLE, &CMainFrame::OnUpdateNewApple)
ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);

	std::map<CString, menu_element>::iterator it = m_map_menu_element_2.begin();
	m_map_menu_element_2.insert(it, std::pair<CString, menu_element>("1", { "Apple", (COLORREF) RGB(255, 0, 0), (COLORREF) ::GetSysColor(COLOR_BTNTEXT), 0 }));
	m_map_menu_element_2.insert(it, std::pair<CString, menu_element>("2", { "Orange", (COLORREF) ::GetSysColor(COLOR_MENU), (COLORREF) ::GetSysColor(COLOR_BTNTEXT), 0 }));
	m_map_menu_element_2.insert(it, std::pair<CString, menu_element>("3", { "Banana", (COLORREF) ::GetSysColor(COLOR_MENU), (COLORREF) ::GetSysColor(COLOR_BTNTEXT), 0 }));
	m_map_menu_element_2.insert(it, std::pair<CString, menu_element>("3_1", { "Alex", (COLORREF) ::GetSysColor(COLOR_MENU), (COLORREF) ::GetSysColor(COLOR_BTNTEXT), 0 }));
	m_map_menu_element_2.insert(it, std::pair<CString, menu_element>("3_2", { "Sulfred", (COLORREF) ::GetSysColor(COLOR_MENU), (COLORREF) ::GetSysColor(COLOR_BTNTEXT), 0 }));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Load menu item image (not placed on any standard toolbars):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create class view
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Class View window\n");
		return FALSE; // failed to create
	}

	// Create file view
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE; // failed to create
	}

	// Create output window
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE; // failed to create
	}

	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}





void CMainFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	if (lpDrawItemStruct->CtlType == ODT_MENU)
	{
		CDC*    pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		CRect   rect = lpDrawItemStruct->rcItem;
		int     nID = lpDrawItemStruct->itemID;
		bool    bSelected = (lpDrawItemStruct->itemState & ODS_SELECTED) ? true : false;
		bool    bDisabled = (lpDrawItemStruct->itemState & ODS_DISABLED) ? true : false;

		CString strKey;

		strKey.Format(TEXT("%d"), nID);
		std::map<CString, menu_element>::iterator it_on_draw_map = m_map_menu_on_draw.find(strKey);
		if (it_on_draw_map == m_map_menu_on_draw.end()) // if no need to draw
			return;

		menu_element menu_element_onDraw = it_on_draw_map->second;
		CString strItem = menu_element_onDraw.content;
		COLORREF clrText = menu_element_onDraw.text_color;
		COLORREF clrBG = 0;

		if (!bSelected && bDisabled) //draw etched effect for disabled text
		{
			pDC->SetTextColor((COLORREF)::GetSysColor(COLOR_3DHILIGHT));
			::TextOut(pDC->GetSafeHdc(), rect.left + 3, rect.top, strItem, strItem.GetLength());
		}

		if (bSelected && bDisabled)
		{
			pDC->SetTextColor((COLORREF)::GetSysColor(COLOR_3DSHADOW));
			clrBG = (COLORREF) ::GetSysColor(COLOR_HIGHLIGHT);
		}
		else if (bSelected && !bDisabled)
		{
			pDC->SetTextColor((COLORREF)::GetSysColor(COLOR_HIGHLIGHTTEXT));
			clrBG = (COLORREF) ::GetSysColor(COLOR_HIGHLIGHT);
		}
		else if (!bSelected && bDisabled)
		{
			pDC->SetTextColor((COLORREF)::GetSysColor(COLOR_3DSHADOW));
			clrBG = menu_element_onDraw.background_color;
		}
		else // case for !bSelected && !bDisabled
		{
			pDC->SetTextColor(clrText);
			clrBG = menu_element_onDraw.background_color;
		}
		pDC->FillSolidRect(&rect, clrBG);
		::TextOut(pDC->GetSafeHdc(), rect.left + 2, rect.top, strItem, strItem.GetLength());
	}

	CFrameWndEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMainFrame::build_dynamic_menu(const std::map<CString, menu_element>& map_name_menu, CMenu* const pProxyMenu, CMenu& dynamicMenu, CString preSearchKey)
{
	CString postSearchKey, searchKey;
	for (int i = 0; i < pProxyMenu->GetMenuItemCount(); i++)
	{
		int nID = pProxyMenu->GetMenuItemID(i);
		postSearchKey.Format("%d", i + 1);
		searchKey = preSearchKey + postSearchKey;

		std::map<CString, menu_element>::const_iterator it = map_name_menu.find(searchKey);
		VERIFY(it != map_name_menu.end());
		menu_element menu_element_temp = it->second;
		CString strLabel, str_item_ID;
		str_item_ID.Format("%d", nID);
		pProxyMenu->GetMenuString(nID, strLabel, NULL);

		std::map<CString, menu_element>::iterator it_on_draw = m_map_menu_on_draw.find(str_item_ID);

		if (nID == 0) // if this is a separator
		{
			dynamicMenu.AppendMenu(MF_BYPOSITION | MF_SEPARATOR, (UINT)nID);
		}
		else if (nID > 0) // if this is a menu string
		{
			strLabel = menu_element_temp.content;
			dynamicMenu.InsertMenu(i, MF_BYPOSITION | MF_OWNERDRAW, (UINT)nID, strLabel);
			m_map_menu_on_draw.insert(it_on_draw, std::pair<CString, menu_element>(str_item_ID, menu_element_temp));
		}
		else // if this is a pop up
		{
			CMenu* pProxySubMenu = pProxyMenu->GetSubMenu(i);
			VERIFY(pProxySubMenu != 0);
			CMenu dynamicSubMenu;
			dynamicSubMenu.CreatePopupMenu();

			build_dynamic_menu(map_name_menu, pProxySubMenu, dynamicSubMenu, searchKey + CString("_"));

			UINT uSubMenuID = (UINT)dynamicSubMenu.Detach();
			strLabel = menu_element_temp.content;
			dynamicMenu.InsertMenu(i, MF_BYPOSITION | MF_POPUP | MF_OWNERDRAW, uSubMenuID, strLabel);
			str_item_ID.Format("%d", uSubMenuID);
			m_map_menu_on_draw.insert(it_on_draw, std::pair<CString, menu_element>(str_item_ID, menu_element_temp));
			dynamicSubMenu.DestroyMenu();
		}
	}
}

void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	if (IDR_MY_MENU == 0)
		return;
	CMenu dynamicMenu, proxyMenu;
	if (dynamicMenu.GetSafeHmenu())
		dynamicMenu.DestroyMenu();
	// Create a new popup menu.
	if (dynamicMenu.CreatePopupMenu() == FALSE)
		return;

	if (proxyMenu.LoadMenu(IDR_MY_MENU) == FALSE)
		return;

	int nSubMenu = 1;
	CMenu* pProxyMenu = proxyMenu.GetSubMenu(nSubMenu);

	build_dynamic_menu(m_map_menu_element_2, pProxyMenu, dynamicMenu, CString(""));

	CPoint ptCurPos; // current cursor position
	GetCursorPos(&ptCurPos);
	dynamicMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, ptCurPos.x, ptCurPos.y, AfxGetMainWnd(), NULL);
}


void CMainFrame::OnNewApple()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnUpdateNewApple(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	if ((lpMeasureItemStruct->CtlType == ODT_MENU))
	{
		CClientDC dc(this);
		CMenu menu;
		CMenu* pMenu = NULL;
		CString strKey;
		CString strItem;
		int nID;

		// Get menu ID and create a lookup key.
		nID = lpMeasureItemStruct->itemID;
		strKey.Format(_T("%d"), nID);
		std::map<CString, menu_element>::iterator it_on_draw_map = m_map_menu_on_draw.find(strKey);
		if (it_on_draw_map == m_map_menu_on_draw.end()) // if no need to draw
			return;

		// Get menu string.
		strItem = it_on_draw_map->second.content;

		CSize sizeItem;
		sizeItem = dc.GetOutputTextExtent(strItem);
		
		lpMeasureItemStruct->itemWidth = sizeItem.cx + 60;
		lpMeasureItemStruct->itemHeight = sizeItem.cy + 1;

		return;
	}
	CFrameWndEx::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
