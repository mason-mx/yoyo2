#include "stdafx.h"
#include "stdio.h"
#include "yoyo.h"
#include "common.h"
#include <crtdbg.h>

extern HINSTANCE hInst;

//COMBO_YOYO *combos;

INT_PTR CALLBACK AddHisDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

static int ShowResult(HWND hDlg)
{
	TCHAR pRel[NUMBER_TOTAL][RESULT_PATH] = {0};
	int lotteries[LOTTERIES_ROW][3] = {0};
	int total = 0, pEnable[MAX-MIN+1] = {0};

	HWND hListBox = GetDlgItem(hDlg, IDC_LIST2);

	SendMessage( hListBox, LB_RESETCONTENT, 0, 0);

	int rel = parseLottery(lotteries, NULL);

	if(rel <= 0)
	{
		MessageBox(hDlg, TEXT("請輸入歷史記錄！"), TEXT("警告"), MB_ICONWARNING | MB_OK);
		return 0;
	}

	for(int i = 0;i<(MAX-MIN+1);i++){
		HWND hCheck = GetDlgItem(hDlg, IDC_CHECK3 + i);
		int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);
		if(nChecked == BST_CHECKED)
		{
			pEnable[i] = 1;
			total ++;
		}
		//printf("%d : %d\r\n",IDC_CHECK3 + i,pEnable[i]);
    }

	if(total == 0)
	{
		MessageBox(hDlg, TEXT("請輸入統計條件！"), TEXT("警告"), MB_ICONWARNING | MB_OK);
		return 0;
	}

	int n = getCombos();

	//YOYO data
	ULONG *numbers = (ULONG *)malloc(sizeof(ULONG)*NUMBER_TOTAL);
	for(int i = 0;i<NUMBER_TOTAL;i++){
		numbers[i] = 0;
	}

	COMBO_YOYO *combos = initCombo();
	
	//int parray[10][3] = {{0,5,8},{0,5,8},{0,5,8},{0,5,8},{0,5,8},{0,5,8},{0,5,8},{0,5,8},{0,5,8},{0,5,8}};
	for(int i = 0; i < rel;i++)
	{
		//staCombos(parray[i], pEnable, combos, n, numbers);
		staCombos(lotteries[i], pEnable, combos, n, numbers);		
	}
	for(int i = 0;i<NUMBER_TOTAL;i++)
	{
		wsprintf(pRel[i], L"%d : %d", i, numbers[i]);
		SendMessage( hListBox, LB_INSERTSTRING, i, (LPARAM)pRel[i]);
	}

	for(int i = 0; i < n;i++)
	{
		free(combos[i].combo_array);
	}
	free(combos);
	free(numbers);
	return 1;
}

static void ShowLotteryHistory(HWND hListBox)
{
	int lotteries[LOTTERIES_ROW][3] = {0};
	TCHAR pLotteries[LOTTERIES_ROW][HISTORY_PATH] = {0};
	int rel = parseLottery(lotteries, pLotteries);
	if(rel > 0)
	{
		SendMessage( hListBox, LB_RESETCONTENT, 0, 0);

		for (int i = 0 ; i < rel ; i++)
		{
			SendMessage( hListBox, LB_INSERTSTRING, i, (LPARAM)pLotteries[i]);
		}
	}
}

static void ClearLotteryHistory(HWND hListBox)
{
	remove("lotteries.txt");
	SendMessage( hListBox, LB_RESETCONTENT, 0, 0);
}

INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
				//combos = initCombo();
				HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
				ShowLotteryHistory(hListBox);
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
					if ( IDOK == DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDHIS), hDlg, AddHisDlgProc))
					{
						HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
						ShowLotteryHistory(hListBox);
					}
					break;
				case IDC_STAT:
					ShowResult(hDlg);
					break;
				case IDC_CLEAR:
					//if ( IDOK == DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDHIS), hDlg, AddHisDlgProc))
					{
						HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
						ClearLotteryHistory(hListBox);						
					}
					break;
			}
			break;

		case WM_CLOSE:
			//if(MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"),
			//MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				_CrtDumpMemoryLeaks();
			DestroyWindow(hDlg);
			}
			return TRUE;

		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;
	}

	return FALSE;
}