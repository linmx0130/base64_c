#include <stdio.h>
#include <string.h>
#include "base64.h"
#include <stdlib.h>

char num2char[64]={
	'A','B','C','D','E','F','G','H',
	'I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X',
	'Y','Z','a','b','c','d','e','f',
	'g','h','i','j','k','l','m','n',
	'o','p','q','r','s','t','u','v',
	'w','x','y','z','0','1','2','3',
	'4','5','6','7','8','9','+','-'
};

BYTE* encode_bytes(BYTE *data,int size){
	int i;
	if (size <1 || size>3) exit(2);
	BYTE *ret=malloc(size+1);
	for (i=0;i<=size;++i) ret[i]=0;
	if (size==1){
		ret[0]=(data[0]&(0xFC))>>2;
		ret[1]=(data[0]&(0x3))<<4;
		return ret;
	} else if (size==2){
		ret[0]=(data[0]&(0xFC)) >> 2;
		ret[1]=((data[0]&(0x3)) << 4 ) + ( (data[1]&(0xF0)) >> 4 );
		ret[2]=((data[1]&(0xF)) << 2);
		return ret;	
	} else if (size==3){
		ret[0]=(data[0]&(0xFC)) >> 2;
		ret[1]=((data[0]&(0x3)) << 4 ) + ( (data[1]&(0xF0)) >> 4 );
		ret[2]=((data[1]&(0xF)) << 2) + ( (data[2]&(0xC0)) >> 6);
		ret[3]=data[2]&(0x3F);
		return ret;	
	}
	return NULL;
}

void encode(FILE* in, FILE *out){
	BYTE d[3];
	memset(d,0,sizeof(d));
	int n;
	BYTE *code;
	char ans[4];
	while (n=fread(d,1,3,in)){
		code=encode_bytes(d,n);
		int i;
		for (i=0;i<=n;++i){
			ans[i]=num2char[code[i]];
		}
		if (n==1){
			ans[2]=ans[3]='=';
		}
		if (n==2){
			ans[3]='=';
		}
		for (i=0;i<4;++i){
			fputc(ans[i],out);
		}
		memset(d,0,sizeof(d));
		if (n!=3) break;
	}
}
