#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 100

int main()
{
 
	Engine *ep;
	char level[5],buffer[BUFSIZE + 1],data[241];
	int i =0, j =0,flag =0;
	mxArray *testdata = NULL, *result = NULL;

	if (!(ep = engOpen("")))
	{
		printf("\nCan't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}	
	engSetVisible(ep,false);
	
//	char input[]= {"AAAA007C06010301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390303"};	
	char input[]={ "AAAA007C060102000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000D9"};
	char input[]={ "AAAA007C06010301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390301253903012539030124390303"};
	for (i = 14; i < 254; i++,j++)						//前面14位固定字符，后面连着气味数据120个(240位)是截取部分
		data[j] = input[i];
	data[240]='\0';

	testdata = mxCreateString(data);

	if(flag != engPutVariable(ep, "input_data", testdata))			//检查发数据情况，若出错输出f2ff
	{
		printf("f2ff\n");			
	}
	
	if(flag != engEvalString(ep, "save ('data.mat','input_data');"))	//检查存数据情况
	{
		printf("f3ff\n");
	}
	
	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);						
	if(flag != engEvalString(ep, "Mtest"))					 //检查算法文件执行，错误输出f4ff 
	{
		printf("f4ff\n");
	}
	
	if ((result = engGetVariable(ep, "level")) !=NULL)
	{
									
	   printf("the right buffer is  %s\n",buffer);
	   for (i = 0; i < 2; i++)
		{
		  level[i] = buffer[i + 14];					//kinds:0x01,0x02,0x03
		  level[i+2] = buffer[i+30];					//levels:0x01,0x02,0x03,0x04,0x05
		}
		level[4]='\0';
		printf("level:%s\n", level);					//输出结果：第一字节是分类结果，第二字节是分级结果
	}else
		 printf("engGetVariable error !\n" );
	
	mxDestroyArray(testdata);					
	mxDestroyArray(result);										
	engClose(ep);		
	return EXIT_SUCCESS;
}


