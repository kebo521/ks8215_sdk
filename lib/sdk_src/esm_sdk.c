
#include<time.h>
#include<stdlib.h>
#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 







void OsGetRandom(unsigned char *Random,int RandomLen)
{
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<RandomLen;i++)
		Random[i]=(unsigned char)rand();
}




void OsSHA(int Mode, const void *Data, int DataLen, unsigned char*ShaOut)
{

}


void OsDES(const unsigned char *Input, unsigned char *Output, const unsigned char *DesKey, int KeyLen, int Mode)
{

}


void OsAES(const unsigned char *Input, unsigned char *Output, const unsigned char *AesKey, int KeyLen, int Mode)
{

}



int OsRSA(const unsigned char *Modulus, int ModulusLen, const unsigned char *Exp,int ExpLen, const unsigned char *DataIn, unsigned char *DataOut)
{
	return ERR_GEN_RANDOM;

}


int OsRSAKeyGen(unsigned char *Modulus, unsigned char *PriExp, int ModulusLen, const unsigned char * PubExp)
{
	return ERR_GEN_FAIL;
}








