#include "stdafx.h"
#include "stdio.h"
#include "yoyo.h"
#include "common.h"
#include <crtdbg.h>

extern HINSTANCE hInst;
int icombosAll;
COMBO_YOYO *combosAll;
ULONG *numbers5, *numbers6;
extern int *NumberFilter;
extern int savedRectLeft;

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
	int nDanTuo = 0, nDan = 0, nTuo = 0;
	int Dan[10] = {0};
	int DanTuo[10] = {0};
	for(int i = 0;i<10;i++)
	{
		HWND hCheck = GetDlgItem(hDlg, IDC_DAN0+i);
		int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);		
		if(nChecked == BST_CHECKED)
		{
			Dan[i] = 1;
			DanTuo[nDanTuo] = i;
			nDanTuo ++;
			nDan ++;
		}
	}
	if(nDan == 6)
	{
		//Set Tuo
		for(int i = 0;i<10;i++)
		{
			if(0 == Dan[i])
			{
				HWND hCheck = GetDlgItem(hDlg, IDC_TUO0+i);
				SendMessage(hCheck, BM_SETCHECK, 1, 0);
				DanTuo[nDanTuo] = i;
				nDanTuo ++;
			}
		}
		
		TCHAR combosn[MAX_PATH] = {0};
		swprintf(combosn,TEXT("%d %d %d %d %d %d|%d %d %d %d"),DanTuo[0],DanTuo[1],DanTuo[2],DanTuo[3],DanTuo[4],
				DanTuo[5],DanTuo[6],DanTuo[7],DanTuo[8],DanTuo[9]);
		SetWindowText(GetDlgItem(hDlg, IDC_DANTUOTIPS), combosn);
		
	}
	else
	{
		SetWindowText(GetDlgItem(hDlg, IDC_DANTUOTIPS), L"");
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

	int nDanTuo = 0, nDan = 0, nTuo = 0;
	int Tuo[10] = {0};
	int DanTuo[10] = {0};
	for(int i = 0;i<10;i++)
	{
		HWND hCheck = GetDlgItem(hDlg, IDC_TUO0+i);
		int nChecked = SendMessage(hCheck, BM_GETCHECK, 0, 0);		
		if(nChecked == BST_CHECKED)
		{
			Tuo[i] = 1;
			DanTuo[nDanTuo] = i;
			nDanTuo ++;
			nTuo ++;
		}
	}
	if(nTuo == 4)
	{
		//Set Dan
		for(int i = 0;i<10;i++)
		{
			if(0 == Tuo[i])
			{
				HWND hCheck = GetDlgItem(hDlg, IDC_DAN0+i);
				SendMessage(hCheck, BM_SETCHECK, 1, 0);
				DanTuo[nDanTuo] = i;
				nDanTuo ++;
			}
		}
		TCHAR combosn[MAX_PATH] = {0};
		swprintf(combosn,TEXT("%d %d %d %d %d %d|%d %d %d %d"),DanTuo[4],DanTuo[5],DanTuo[6],DanTuo[7],DanTuo[8],
				DanTuo[9],DanTuo[0],DanTuo[1],DanTuo[2],DanTuo[3]);
		SetWindowText(GetDlgItem(hDlg, IDC_DANTUOTIPS), combosn);
	}
	else
	{
		SetWindowText(GetDlgItem(hDlg, IDC_DANTUOTIPS), L"");
	}
	return;
}

static int ShowResult(HWND hDlg)
{
	TCHAR pRel[NUMBER_TOTAL][RESULT_PATH] = {0};
	int j = NUMBER_TOTAL, total = 0, pEnable[DANTUO_MAX-DANTUO_MIN+1] = {0};
	ULONG weight;
	
	HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);

	if(0 == SendMessage(hListBox, LB_GETCOUNT, 0, 0))
	{
		MessageBox(hDlg, TEXT("請添加膽拖組合！"), TEXT("警告"), MB_ICONWARNING | MB_OK);
		return 0;
	}

	hListBox = GetDlgItem(hDlg, IDC_LIST2);

	SendMessage( hListBox, LB_RESETCONTENT, 0, 0);

	for(int i = 0;i<(DANTUO_MAX-DANTUO_MIN+1);i++){
		HWND hCheck = GetDlgItem(hDlg, IDC_CHECK5 + i);
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

	for(int i = 9;i>=0;i--)
	{
		weight = 0;
		//j --;
		
		if(pEnable[0] == 1)
		{
			weight += numbers5[i];
		}
		if(pEnable[1] == 1)
		{
			weight += numbers6[i];
		}
		wsprintf(pRel[i], L"%d : %u", i, weight);
		SendMessage( hListBox, LB_INSERTSTRING, 0, (LPARAM)pRel[i]);
	}
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
	//for test
	//for(int i=0;i<10;i++) DanTuo[i] = i;

	TCHAR pLotteries[RESULT_PATH] = {0};
	HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
	swprintf(pLotteries,TEXT("%d %d %d %d %d %d|%d %d %d %d"),DanTuo[0],DanTuo[1],DanTuo[2],DanTuo[3],DanTuo[4],
				DanTuo[5],DanTuo[6],DanTuo[7],DanTuo[8],DanTuo[9]);
	SendMessage( hListBox, LB_INSERTSTRING, 0, (LPARAM)pLotteries);

	COMBO_YOYO *combosDanTuo;
	int icombosDanTuo = getDanTuoCombos(DANTUO_MIN, DANTUO_MAX);
	combosDanTuo = initDanTuo(DanTuo,numbers5, numbers6);
	
	staSpecialWeight(NumberFilter, combosDanTuo, icombosDanTuo, combosAll, icombosAll, numbers5, numbers6);
	
	for(int i = 0; i < icombosDanTuo;i++)
	{
		free(combosDanTuo[i].combo_array);
	}
	free(combosDanTuo);

	return nDanTuo;
}

static void ClearDanTuo(HWND hDlg)
{
	HWND hListBox = GetDlgItem(hDlg, IDC_LIST1);
	HWND hListBox2 = GetDlgItem(hDlg, IDC_LIST2);
	for(int i = 0;i<NUMBER_TOTAL;i++){
		numbers5[i] = 0;
	}

	for(int i = 0;i<NUMBER_TOTAL;i++){
		numbers6[i] = 0;
	}
	SetWindowText(GetDlgItem(hDlg, IDC_DANTUOTIPS), L"");
	SendMessage( hListBox, LB_RESETCONTENT, 0, 0);
	SendMessage( hListBox2, LB_RESETCONTENT, 0, 0);
	return;
}

INT_PTR CALLBACK AdvDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
			{
				RECT rectParent;
				int NewPosX, NewPosY;  
	  
				if (GetWindowRect(GetParent(hDlg), &rectParent))   
				{  
					NewPosX     = rectParent.right;
					NewPosY     = rectParent.top;
	                  
					SetWindowPos(hDlg, 0, NewPosX, NewPosY,  
						0, 0, SWP_NOZORDER | SWP_NOSIZE);  
				}
				HWND hCheck = GetDlgItem(hDlg, IDC_CHECK5);
				SendMessage(hCheck, BM_SETCHECK, 1, 0);
				
				numbers5 = (ULONG *)malloc(sizeof(ULONG)*NUMBER_TOTAL);
				for(int i = 0;i<NUMBER_TOTAL;i++){
					numbers5[i] = 0;
				}

				numbers6 = (ULONG *)malloc(sizeof(ULONG)*NUMBER_TOTAL);
				for(int i = 0;i<NUMBER_TOTAL;i++){
					numbers6[i] = 0;
				}

				//Get all combos and their weight
				icombosAll = getCombos();
				combosAll = initCombo();
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
				free(numbers5);
				free(numbers6);
				for(int i = 0; i < icombosAll;i++)
				{
					free(combosAll[i].combo_array);
				}
				free(combosAll);

				RECT rectParent;
				int NewPosX, NewPosY;  
	  
				if (GetWindowRect(GetParent(hDlg), &rectParent))   
				{  
					NewPosX     = savedRectLeft;
					NewPosY     = rectParent.top;
	                  
					SetWindowPos(GetParent(hDlg), 0, NewPosX, NewPosY,  
						0, 0, SWP_NOZORDER | SWP_NOSIZE);  
				}
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
