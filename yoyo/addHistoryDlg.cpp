#include "stdafx.h"
#include "stdio.h"
#include "yoyo.h"
#include "common.h"

int SaveEdittoFile(HWND hDlg)
{
	TCHAR   szString[2];
	int parray[3];
	GetDlgItemText(hDlg, IDC_EDIT1, szString, 2);
	parray[0] = _wtoi(szString);
	if(parray[0] >= NUMBER_TOTAL) return 0;
	GetDlgItemText(hDlg, IDC_EDIT2, szString, 2);
	parray[1] = _wtoi(szString);
	if(parray[1] >= NUMBER_TOTAL) return 0;
	GetDlgItemText(hDlg, IDC_EDIT3, szString, 2);
	parray[2] = _wtoi(szString);
	if(parray[2] >= NUMBER_TOTAL) return 0;
	/*char   *pFilePathName;  
        TCHAR   lpszFile[256];  
      _tcscpy(lpszFile,   _T("c://aa.dll"));  
   
      int   nLen   =   wcslen(wstr)+1;    
      WideCharToMultiByte(CP_ACP,   0,   lpszFile,   nLen,   pFilePathName,  
2*nLen,   NULL,   NULL);*/
	return saveLottery(parray);
}

INT_PTR CALLBACK AddHisDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					SaveEdittoFile(hDlg);
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				case IDCANCEL:
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
			}
			
			break;
			/*if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;*/
		
	}

	return FALSE;
}