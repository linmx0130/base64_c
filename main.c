#include <stdio.h>
#include "base64.h"
#include <string.h>
int main(int argc, char* argv[]){
	if (argc!=3 && argc!=4){
		printf("USAGE: %s [-d] input_filename output_filename\n",argv[0]);
		return 1;
	}
	if (argc==3){
		FILE *fin = fopen(argv[1],"r");
		FILE *fout = fopen(argv[2],"w");
		encode(fin,fout);
		fclose(fin);
		fclose(fout);
	}
	if (argc==4){
		if (strcmp(argv[1],"-d")){
			printf("USAGE: %s [-d] input_filename output_filename\n",argv[0]);
			return 1;
		}
		FILE *fin = fopen(argv[2],"r");
		FILE *fout = fopen(argv[3],"w");
		decode(fin,fout);
		fclose(fin);
		fclose(fout);
	}
	return 0;
}
