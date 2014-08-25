#pragma once

#include "resource.h"

#define NUMBER_TOTAL 10
#define LOTTERIES_ROW 10
#define LOTTERIES_COL 3

#define HISTORY_PATH 10
#define HISTORY_NUM 20

#define RESULT_PATH 20

#define MIN 3
#define MAX 8

struct COMBO_YOYO
{
	int combo_n;
	int *combo_array;
	int weight;
};
