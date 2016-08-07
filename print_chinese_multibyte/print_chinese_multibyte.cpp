// print_chinese_multibyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "print_chinese_multibyte.h"

#include <iostream>
#include <string>
#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	locale loc("cht");
	std::wcout.imbue(loc);
	std::wstring strTemp = L"text§A¦n";
	std::wcout << strTemp << std::endl;
	system("pause");

	return nRetCode;
}
