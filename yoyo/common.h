#include "yoyo.h"

int getCombos();
COMBO_YOYO * initCombo();
int staCombos(int *parray, int *pEnable,int *pNumber, COMBO_YOYO *pcombos, int n, ULONG *numbers);
int parseLottery(int pArray[MAX_HISTORY_NUM][3], TCHAR pLotteries[MAX_HISTORY_NUM][HISTORY_PATH]);
int saveLottery(int* pArray);
int prepareWeight(int combo_n);
int prepareHit(int combo_n);
int prepareLotteries();
int parseWeight(double pArray[COMBOS_N]);
int staWeight(int *pEnable, int *pNumber, COMBO_YOYO *pcombos, int n, ULONG *numbers);
int staHit(COMBO_YOYO *pcombos, int n);
int prepareMaxNoHit();
int saveMaxNoHit(int MaxNoHit);
int parseMaxNoHit();
COMBO_YOYO * initDanTuo(int *parray, ULONG *numbers5, ULONG *numbers6);
int getDanTuoCombos(int iMin, int iMax);
int staSpecialWeight(int *NumberFilter, COMBO_YOYO *combos, int icombos, COMBO_YOYO *combosAll, int icombosAll, ULONG *numbers5, ULONG *numbers6);
