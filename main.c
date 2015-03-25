#include <stdio.h>
#include "base64.h"
#include <string.h>
int main(int argc, char* argv[]){
	if (argc!=2){
		printf("USAGE: %s [filename]\n",argv[0]);
		return 1;
	}
	FILE *fin = fopen(argv[1],"r");
	encode(fin,stdout);
	return 0;
}
