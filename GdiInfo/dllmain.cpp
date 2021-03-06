// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "MainDlg.h"


unsigned _stdcall ThreadProc(void* param)
{
  CMessageLoop theLoop;

  CMainDlg dlgMain;

  if(dlgMain.Create(NULL) == NULL)
  {
    ATLTRACE(_T("Main dialog creation failed!\n"));
    return 0;
  }

  dlgMain.ShowWindow(SW_SHOW);
  SetForegroundWindow(dlgMain.m_hWnd);

  int nRet = theLoop.Run();
  return nRet;
}

HANDLE handle = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
    handle = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, NULL, NULL);
    break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

