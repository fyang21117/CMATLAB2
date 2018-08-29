#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"
#define  BUFSIZE 40

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")
int  init_engine(Engine *p);
void handling(Engine *ep, char temp[]);
int hexstr2dec(char s[]);
double decdata[120];

int main()
{
	Engine *ep = engOpen(NULL);
	init_engine(ep);
	char input[] = { "AAAA007C060103012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903012539030125390301243903020303" };
	handling(ep, input);

	engClose(ep);
	getchar();
	while (1);
	return EXIT_SUCCESS;
}
int hexstr2dec(char s[])
{
	int i,j=0, m, temp = 0, n;
	m = strlen(s);
	for (i = 0; i<m - 1; i++)
	{
		if (s[i] >= 'A'&&s[i] <= 'F')
			n = s[i] - 'A' + 10;
		else if (s[i] >= 'a'&&s[i] <= 'f')
			n = s[i] - 'a' + 10;
		else
			n = s[i] - '0';
		temp = n;
		i++;
		if (s[i] >= 'A'&&s[i] <= 'F')
			n = s[i] - 'A' + 10;
		else if (s[i] >= 'a'&&s[i] <= 'f')
			n = s[i] - 'a' + 10;
		else
			n = s[i] - '0';
		temp = temp * 16 + n;
		printf("decdata[%d]=%d\n",j, temp);
		decdata[j++] = temp;
	}
	return temp;
}

int init_engine(Engine *p)
{
	if (!p)
	{
		printf("Can't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}
	engSetVisible(p, false);
	return 0;
}

void handling(Engine *ep, char temp[])
{
	int i = 0, j = 0;
	mxArray *testdata = NULL, *result = NULL;
	char  level[5], buffer[BUFSIZE + 1], data[241];
	level[4] = '\0';
	for (i = 14; i < 255; i++, j++)										//截取气味数据到数组
		data[j] = temp[i];
	data[240] = '\0';
	hexstr2dec(data);

	testdata = mxCreateDoubleMatrix(1,120,mxREAL);
	memcpy((double*)mxGetPr(testdata),(double*)decdata,120*sizeof(double));
	engPutVariable(ep, "input_data", testdata);							//将testdata传入Matlab工作空间，取名input_data	
	engEvalString(ep, "save ('data.mat','input_data');");				//生成路径D:\Program Files (x86)\SetupDir\MATLAB\R2016b

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);								//结果缓冲区buffer
	engEvalString(ep, "dectest");									// 调用"hextest.m"
	engOutputBuffer(ep, NULL, 0);

	if ((result = engGetVariable(ep, "level")) != NULL)
	{
//		for(i=0;i<30;i++)			printf("The  result of MATLAB is %c\n", buffer[i]);
		for (i = 0; i < 2; i++)
		{
			level[i] = buffer[i + 11];
			level[i + 2] = buffer[i + 27];					// 0x01(smoke),0x02(jinshuqi), 0x03(xibanshui);01-05level
		}
		printf("\nThe return is %s", level);
	}
	else
		printf("engGetVariable error !\n");
	mxDestroyArray(testdata);
	mxDestroyArray(result);
}

