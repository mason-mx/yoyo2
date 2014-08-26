#include "stdafx.h"
#include "stdio.h"
#include "yoyo.h"

static int *dst_array/*=(int *)malloc(sizeof(int)*8)*/,top=0,count=0;//�м����飬����м������̣�count�������е���ϸ���

static bool hasSameinArray(int n,int *parray, int index, int size)
{
    int i;
	if(index > size) return false;
    for(i=0;i<(index-1);i++){
		if(n == parray[i]) return true;
        //printf("%d ",parray[i]);
    }
	return false;
}

static int cnm(int n, int m)//n>=m>=0
{
	int i,a;
	if(m+m>n) m=n-m;//be faster
	for(i=1,a=1;i<=m;i++,n--) a=a*n/i;
	return a;
}

static void assign_printA(int *parray,COMBO_YOYO* combos,int n)
{
    int i;
    for(i=0;i<n;i++){
		combos[count].combo_array[i] = parray[i];
        //printf("%d ",parray[i]);
    }
}

static void docombine(int *pArray, COMBO_YOYO* combos, int n, int m)
{
    if(n < m || m == 0)    return ;//���һ������������������
    docombine(pArray+1,combos,n-1,m);//���������������ǰԪ�ص����е����
    dst_array[top++]=pArray[0];//�������������ǰԪ��
    if(m == 1){//�����-1����ֹ����ǰԪ��
        assign_printA(dst_array,combos,top);
        count++;
        top--;
        return;
    }
    docombine(pArray+1,combos,n-1,m-1);//�����-2��������ǰԪ�ص���δ��ֹ
    top--;//����ǰ�ָ�topֵ
}

static int weightNumber(COMBO_YOYO &pcombos, ULONG *numbers, int hit)
{
	int combo_n = pcombos.combo_n;
	switch(combo_n)
	{
	case 3:
		{
			switch(hit)
			{
			case 0:
				pcombos.weight *= 2;
				break;
			case 1:
				pcombos.weight *= 1;
				break;
			case 2:
			case 3:
				pcombos.weight = 1;
				break;
			default:
				break;
			}
		}
		break;
	case 4:
		{
			switch(hit)
			{
			case 0:
			case 1:
				if(pcombos.weight < 8)
				{
					pcombos.weight *= 2;
				}
				else if(pcombos.weight >= 8)
				{
					pcombos.weight *= 1.5;
				}
				else if(pcombos.weight >= 1000)
				{
					pcombos.weight *= 1.3;
				}
				break;
			case 2:
			case 3:
				pcombos.weight  = 1.0;
				break;
			default:
				break;
			}
		}
		break;
	case 5:
		{
			switch(hit)
			{
			case 0:
			case 1:
				pcombos.weight *= 2;
			case 2:
			case 3:
				pcombos.weight  = 1;
				break;
			default:
				break;
			}
		}
		break;
	case 6:
	case 7:
		{
			switch(hit)
			{
			case 0:
			case 1:
				pcombos.weight *= 2;
				break;
			case 2:
				pcombos.weight *= 1;
				break;
			case 3:
				pcombos.weight = 1;
				break;
			default:
				break;
			}
		}
		break;
	case 8:
		{
			switch(hit)
			{
			case 0:
			case 1:
			case 2:
				pcombos.weight *= 2;
				break;
			case 3:
				pcombos.weight = 1;	
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;

	}
	for(int j = 0;j<combo_n;j ++)
	{
		numbers[pcombos.combo_array[j]] += pcombos.weight;
	}
	printf("%d hit %d | weight:%lf\n", combo_n, hit, pcombos.weight);
	return 0;
}

int getCombos()
{
	int icombos = 0, temp = 0;
	//Pre-combine to get combos
	for(int i = MIN;i <= MAX; i ++)
	{
		temp = cnm(NUMBER_TOTAL, i);
		icombos += temp;
		printf("=====C(%d, %d) = %d=====\r\n",NUMBER_TOTAL,i,temp);
	}
	printf("=====NUMBER_TOTALy %d=====\r\n",icombos);
	return icombos;
}

COMBO_YOYO * initCombo()
{
	int i, *parray;
	int l = 0, j = MIN, *combo_n = (int *)malloc(sizeof(int)*(MAX-MIN+1));
	int icombos = 0, temp = 0;

	top=0;
	count=0;
	dst_array=(int *)malloc(sizeof(int)*8);

    parray=(int *)malloc(sizeof(int)*NUMBER_TOTAL);
	//Pre-combine to get combos
	for(i = MIN;i <= MAX; i ++)
	{
		temp = cnm(NUMBER_TOTAL, i);
		combo_n[i - MIN] = temp;
		icombos += temp;
	}

	//Do combine to assign destnation array;
    COMBO_YOYO *combos=(COMBO_YOYO *)malloc(sizeof(COMBO_YOYO)*icombos);
	for(i = 0;i<icombos;i++){//��ʼ������
		if(combo_n[j-MIN] == l)
		{
			j ++;
			l = 0;
			//printf("%d, %d", i, j);
		}
		combos[i].combo_n = j;
		combos[i].combo_array = (int *)malloc(sizeof(int)*j);
		combos[i].weight = 1.0;
		l ++;
    }
	for(i = 0;i<NUMBER_TOTAL;i++){//��ʼ������
        parray[i] = i;
    }
	for(i = MIN;i <= MAX; i ++)
	{
		//precombine(3);
		docombine(parray, combos, NUMBER_TOTAL, i);//�������������������
	}
#if 0
	j = MIN;l = 0;
	for(i = 0;i<icombos;i++){//��ʼ������
		if(combo_n[j-MIN] == l)
		{
			j ++;
			l = 0;
			//printf("%d, %d", i, j);
		}
		for(int k=0;k<j;k++) printf("%d ",combos[i].combo_array[k]);
		printf("@ %d\n", combos[i].combo_n);
		l ++;		
    }
#endif
	free(parray);
	free(dst_array);
	free(combo_n);
	return combos;
}

int staCombos(int *parray, int *pEnable, int *pNumber, COMBO_YOYO *pcombos, int n, ULONG *numbers)
{
	int hit = 0;
	bool skip = false;
	
	for(int i = 0;i<n;i++)
	{
		if(pEnable[pcombos[i].combo_n - MIN] == 0)
		{
			//printf("[%3d]",i+1);
			//printf("skip this\r\n");
			continue;
		}
		printf("[%3d:",i+1);
		for(int k = 0;k<pcombos[i].combo_n;k++)
		{
			printf(" %d", pcombos[i].combo_array[k]);
			for(int l = 0;l<NUMBER_TOTAL;l++)
			{
				if((pNumber[l] == 0) && (l== pcombos[i].combo_array[k]))
				{
					//printf("%d ", l);
					skip = true;
					break;
				}
			}
		}
		printf("]");
		if(skip)
		{
			skip = false;
			printf("skip this\r\n");
			continue;
		}
		printf(" [");
		for(int j = 0;j<3;j ++)
		{
			printf(" %d", parray[j]);
		}
		printf("]");
		for(int k = 0;k<pcombos[i].combo_n;k++)
		{
			//printf("%d ", pcombos[i].combo_array[k]);
			
			for(int j = 0;j<3;j ++)
			{
				if(j == 1)
				{
					if(parray[j] == parray[0]) continue;
				}
				else if(j == 2)
				{
					if((parray[j] == parray[0]) || (parray[j] == parray[1])) continue;
				}
				if(parray[j] == pcombos[i].combo_array[k])
				{
					hit ++;
				}
			}
		}
		//printf("]");
		weightNumber(pcombos[i], numbers, hit);
		hit = 0;
    }
	printf("======Statics======\r\n");
	for(int i = 0;i<NUMBER_TOTAL;i++){
		printf("%d : %d\r\n",i,numbers[i]);
    }
	printf("======4/5======\r\n");
	for(int i = 0;i<NUMBER_TOTAL;i++){
		if(numbers[i] > 100)
		{
			if(50 <= (numbers[i] - (numbers[i]/100)*100))
				numbers[i] = (numbers[i]/100 + 1) * 100;
			else
				numbers[i] = (numbers[i]/100) * 100;
		}
		printf("%d : %d\r\n",i,numbers[i]);
    }
	return 0;
}

//Only support 0~9 chars
int parseStringtoArray(int* des, const char* src)
{
	int i, ret = 0, len = strlen(src);
	for(i=0; i<len; i++)
	{
		if('0' <= src[i] && '9' >= src[i])
		{
			des[ret++] = src[i]-'0';
		}
	}
	return ret;
}

#if (NUMBER_TOTAL > 10)
//support integer
int parseStringtoArrayEx(int* des, const char* src)
{
	int i, ret = 0, len = strlen(src);
	char tmp[4] = {0};
	int j = 0;
	for(i=0; i<len; i++)
	{
		if(' ' == src[i])
		{
			des[ret++] = atoi(tmp);
			j = 0;
			memset(tmp, 0, 4);
		}
		else
		{
			tmp[j++] = src[i];
		}
		if(i == len-1)
		{
			des[ret++] = atoi(tmp);
		}
	}
	return ret;
}
#endif

int parseLottery(int pArray[LOTTERIES_ROW][3], TCHAR pLotteries[LOTTERIES_ROW][HISTORY_PATH])
{
    FILE *fp1;
    char buf[HISTORY_PATH];
	int i = 0;

    if( (fp1=fopen("lotteries.txt","r"))==NULL )
    {
        printf("Cannot open the file");
		if ((fp1=fopen("lotteries.txt","w+"))==NULL)
		{
			printf("create the file failed.");
			//getch();
			return 0;
		}
    }

    while((!feof(fp1)) && (i<LOTTERIES_ROW))       //���ļ�ָ��fp1ָ���ļ�ĩβʱ��feof����0�����򷵻�1���þ�������ֻҪδ��ĩβ�����ѭ��
    {
        memset(buf, 0, HISTORY_PATH);       //buf�ַ�����0
        fgets(buf, HISTORY_PATH, fp1);      //��fp1�ļ���ǰָ���ȡһ�����ݵ�buf
		if(2 > strlen(buf)) break;
		if(pLotteries != NULL)
			MultiByteToWideChar(CP_THREAD_ACP,MB_USEGLYPHCHARS,buf,strlen(buf),pLotteries[i],HISTORY_PATH);   
        parseStringtoArray(pArray[i], buf);
		i ++;
    }

    fclose(fp1);

    return i;
}

//Only support 0~9 chars
int buildString(char* dest, int* pArray)
{
	int i;
	//Build a string like "0 1 2"
	for(i=0; i<LOTTERIES_COL; i++)
	{
		dest[2*i]=pArray[i]+'0';
		dest[2*i+1]=' ';
	}
	dest[2*LOTTERIES_COL - 1] = '\0';
	return 1;
}

#if (NUMBER_TOTAL > 10)
//support integer
int buildStringEx(char* dest, int* pArray)
{
	//char str[80];
	//int data[5]={4, 5, 13, 2, 5};
	int i,L = 0;
	//Build a string like "0 1 2 10 11 12"
	for (i=0;i<LOTTERIES_COL;i++) {
		if  (i<4) sprintf(dest+L,"%d ",pArray[i]);
		else sprintf(dest+L,"%d ",pArray[i]); 
		L = strlen(dest);
	};
	//printf("%s",str);
	return 1;
}
#endif

int saveLottery(int* pArray)
{
#if 0
	char buf[LOTTERY_PATH];
	FILE *fp;
	char ch;

	buildString(buf, pArray);
	printf(buf);
	
	if((fp=fopen("lotteries.txt","at+"))==NULL){
		printf("Cannot open file strike any key exit!\n");
		return 0;
	}
	fputc('\n',fp);
	fputs(buf,fp);
	rewind(fp);
	ch=fgetc(fp);

	while(ch!=EOF){
		putchar(ch);
		ch=fgetc(fp);
	}
	printf("Save a lottery successfully\n");
	fclose(fp);
    return 1;
#endif

	FILE *fp;
	char buff1[HISTORY_NUM][HISTORY_PATH];
	int i=0;
	char buf[HISTORY_PATH];

	buildString(buf, pArray);
	//printf(buf);

    //�򿪴洢�ļ�
	if ((fp=fopen("lotteries.txt","r"))==NULL)
	{
		//printf("Can not open the file");
		//getch();
		//return 0;
	} 
	else
	{
		ZeroMemory(buff1,sizeof(buff1));
		while ((!feof(fp)) && (i < HISTORY_NUM))
		{			
			fgets(buff1[i],sizeof(buff1[i]),fp);
			i++;
		}
	}
	fclose(fp);

    //�򿪴洢�ļ�,���ź������������д���ļ���
	if ((fp=fopen("lotteries.txt","w"))==NULL)
	{
		printf("Can not write the file");
		//getch();
		return 0;
	} 
	else
	{   		
		fputs(buf,fp);
		if(i > 0)
			fputc('\n',fp);
		//д���ı��ļ�
		int k=0;
		while(k<=i)
		{
			fputs(buff1[k],fp);
			//fprintf(fp,"%i\n",fScore[k]);
			k++;
		}
	}	
	fclose(fp);
	return 1;
}