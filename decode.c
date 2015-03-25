#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "base64.h"

BYTE char2num[256];
void init_decode_table(){
	memset(char2num,0,sizeof(char2num));
	int i;
	// A-Z
	for (i=0;i<26;++i){
		char2num['A'+i]=i;
	}
	//a-z
	for (i=0;i<26;++i){
		char2num['a'+i]=26+i;
	}
	//0-9
	for (i=0;i<10;++i){
		char2num['0'+i]=52+i;
	}
	char2num['+']=62;
	char2num['-']=63;
}

int decode_chars(char *data, BYTE* ret){
	init_decode_table();
	BYTE* d;
	int i;
	if (data[2]=='=') {
		d = (BYTE *)malloc(2);
	}else if (data[3]=='='){
		d = (BYTE *)malloc(3);
	}else{
		d = (BYTE *)malloc(4);
	}
	memset(d,0,sizeof(d));
	int count=0;
	for (i=0;i<=3 && data[i]!='=';++i){
		d[i]=char2num[data[i]];
		count++;
	}
	ret[0] = (d[0]<<2) + ((d[1]&(0x30)) >>4);
	if (count==2) return 1;

	ret[1]=((d[1]&(0xF))<<4) + ((d[2]&(0x3C))>>2);
	if (count == 3) return 2;

	ret[2]=((d[2]&(0x3))<<6) + d[3];
	return 3;
}
void decode(FILE* in, FILE *out){
	char buf[80];
	int i,n,slen;
	BYTE d[3];
	while (fgets(buf,77,in)){
		slen=strlen(buf);
		if (buf[slen-1]=='\n') slen--;
		for (i=0;i<slen;i+=4){
			memset(d,0,sizeof(d));
			n=decode_chars(buf+i,d);
			fwrite(d,1,n,out);
		}
	}
}
