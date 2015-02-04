#include "stdafx.h"
#include "stdio.h"
#include "yoyo.h"
#include "common.h"
#include <crtdbg.h>

extern HINSTANCE hInst;
int g_10[10] = {0};

static void HandleDan(HWND hDlg, int ctrl_ID)
{
	HWND hCheck = GetDlgItem(hDlg, ctrl_ID);
	int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);
	hCheck = GetDlgItem(hDlg, ctrl_ID + (IDC_TUO0-IDC_DAN0));
	if(nChecked == BST_CHECKED)
	{
		SendMessage(hCheck, BM_SETCHECK, 0, 0);
	}
	else
	{
		SendMessage(hCheck, BM_SETCHECK, 1, 0);
	}
	return;
}

static void HandleTuo(HWND hDlg, int ctrl_ID)
{
	HWND hCheck = GetDlgItem(hDlg, ctrl_ID);
	int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);
	hCheck = GetDlgItem(hDlg, ctrl_ID - (IDC_TUO0-IDC_DAN0));
	if(nChecked == BST_CHECKED)
	{
		SendMessage(hCheck, BM_SETCHECK, 0, 0);
	}
	else
	{
		SendMessage(hCheck, BM_SETCHECK, 1, 0);
	}
	return;
}

static int ShowResult(HWND hDlg)
{
	return 0;
}

static int ShowDanTuo(HWND hDlg)
{
	//Get Dan and Tuo and add a row into list
	int DanTuo[10] = {0};
	int nDanTuo = 0, nDan = 0, nTuo = 0;
	for(int i = 0;i<10;i++)
	{
		HWND hCheck = GetDlgItem(hDlg, IDC_DAN0+i);
		int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);		
		if(nChecked == BST_CHECKED)
		{
			DanTuo[nDanTuo] = i;
			nDanTuo ++;
			nDan ++;
		}
	}
	for(int i = 0;i<10;i++)
	{
		HWND hCheck = GetDlgItem(hDlg, IDC_TUO0+i);
		int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);		
		if(nChecked == BST_CHECKED)
		{
			DanTuo[nDanTuo] = i;
			nDanTuo ++;
			nTuo ++;
		}
	}
	if((nDan != 6) || (nTuo != 4))
	{
		MessageBox(hDlg, TEXT("請輸入統計條件！"), TEXT("警告"), MB_ICONWARNING | MB_OK);
		return 0;
	}

	TCHAR pLotteries[RESULT_PATH] = {0};
	HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
	swprintf(pLotteries,TEXT("%d %d %d %d %d %d|%d %d %d %d"),DanTuo[0],DanTuo[1],DanTuo[2],DanTuo[3],DanTuo[4],
				DanTuo[5],DanTuo[6],DanTuo[7],DanTuo[8],DanTuo[9]);
	SendMessage( hListBox, LB_INSERTSTRING, 0, (LPARAM)pLotteries);

	return nDanTuo;
}

static void ClearDanTuo(HWND hDlg)
{
	return;
}

INT_PTR CALLBACK AdvDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
			{
				RECT rectChild, rectParent;  
				int DlgWidth, DlgHeight;    // 以像素为单位的对话框宽度和高度  
				int NewPosX, NewPosY;  
	  
				// 设法使“关于”对话框居中显示  
				if (GetWindowRect(hDlg, &rectChild))   
				{  
					GetClientRect(GetParent(hDlg), &rectParent);  
					DlgWidth    = rectChild.right - rectChild.left;  
					DlgHeight   = rectChild.bottom - rectChild.top ;  
					NewPosX     = (DlgWidth) / 2;  
					NewPosY     = (DlgHeight) / 2;  
	                  
					// 如果“关于”框比实际屏幕大  
					if (NewPosX < 0) NewPosX = 0;  
					if (NewPosY < 0) NewPosY = 0;  
					SetWindowPos(hDlg, 0, NewPosX, NewPosY,  
						0, 0, SWP_NOZORDER | SWP_NOSIZE);  
				}
			}
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			/*if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			}
			break;*/
			switch(LOWORD(wParam))
			{
				case IDOK:
					{
					//HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
					//ShowResult(hListBox);
					SendMessage(hDlg, WM_CLOSE, 0, 0);
					}
					return TRUE;
				case IDC_ADDHIS:
					ShowDanTuo(hDlg);
					break;
				case IDC_STAT:
					ShowResult(hDlg);
					break;
				case IDC_CLEAR:
					ClearDanTuo(hDlg);						
					break;
				case IDC_DAN0:
				case IDC_DAN1:
				case IDC_DAN2:
				case IDC_DAN3:
				case IDC_DAN4:
				case IDC_DAN5:
				case IDC_DAN6:
				case IDC_DAN7:
				case IDC_DAN8:
				case IDC_DAN9:
					HandleDan(hDlg, LOWORD(wParam));
					break;
				case IDC_TUO0:
				case IDC_TUO1:
				case IDC_TUO2:
				case IDC_TUO3:
				case IDC_TUO4:
				case IDC_TUO5:
				case IDC_TUO6:
				case IDC_TUO7:
				case IDC_TUO8:
				case IDC_TUO9:
					HandleTuo(hDlg, LOWORD(wParam));
					break;
			}
			break;

		case WM_CLOSE:
			//if(MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"),
			//MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				//_CrtDumpMemoryLeaks();
				EndDialog(hDlg, LOWORD(wParam));
				//DestroyWindow(hDlg);
			}
			return TRUE;

		//case WM_DESTROY:
			//PostQuitMessage(0);
			//return TRUE;
	}

	return FALSE;
}