#include <stdio.h>
#include "string.h"


void _fileGen(const char* pfn){    
    FILE *fd;
    char bufferCh[99]={0};
    int i;
    fd = fopen(pfn, "wb"); // fwrite写入
    if (fd != NULL ) {
        for (i=0;i<4;i++){
            bufferCh[0] = '0'+i;
            bufferCh[1] = '0'+2*i;
            bufferCh[2] = '\n';
            fwrite(bufferCh, 3, sizeof(char), fd);
        }
        fclose (fd); // fwrite写入
    }    
};

void _fileGen2(const char* pfn){    
    char bufferCh[]="#!/bin/bash\nif [ -d \"build\" ]; then\n    echo \"exist\"\nelse\n    mkdir build\nfi\n\ncd build\ncmake ..\nmake\necho \"compile finished\";\n";
    FILE *fd = fopen(pfn, "wb"); // fwrite写入
    if (fd != NULL ) {
        fwrite(bufferCh, 126, sizeof(char), fd);
        fclose (fd); // fwrite写入
    }    
};


int fileIsEqual(const char*filename, const char*filenam2) 
{ 
	FILE *fp = fopen(filename, "rb");
	if(fp == NULL)
	{ 
		return -1; 
	} 
	FILE *fp2 = fopen(filenam2, "rb");
	if (fp2 == NULL)
	{ 
		return -1; 
	} 

	int NotEqal = 0;
	while(1) 
	{ 
        #define MAX_LEN (1024)
        char strLine[MAX_LEN];             //每行最大读取的字符数
        char strLin2[MAX_LEN];             //每行最大读取的字符数
        if (feof(fp) != feof(fp2)){
            NotEqal = 1;
            break;
        }
        if (feof(fp)){
            break;
        }
        int len = fread(strLine, 1, MAX_LEN, fp);
        int len2 = fread(strLin2, 1, MAX_LEN, fp2);
        if (len != len2){
            NotEqal = 1;
            break;
        }
        for (int i=0;i<len;i++){
            if (strLine[i]!=strLin2[i]){
                NotEqal = 1;
                break;
            }
        }
        if (NotEqal){
            break;
        }
	}

	fclose(fp);
	fclose(fp2);
	return NotEqal; 
}
