#include "xtar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Xtar *make_xtar()
{
	Xtar *l = malloc(sizeof(Xtar));
	l->title_len = 0;
	l->body_len = 0;
	l->body = 0;
	l->title = 0;
	return l;
}

void xtar_add_title(Xtar* p, const char* f, int len)
{
    p->title_len = len;
    p->title = calloc(len+1, sizeof(char));
    memcpy(p->title, f, len);
}

void xtar_add_body(Xtar* p, const char* f, int len)
{
    p->body_len = len;
    p->body = calloc(len+1, sizeof(char));
    memcpy(p->body, f, len);
}

int xtar_from_file(Xtar* p, const char* f)
{
    xtar_add_title(p, f, strlen(f));

    FILE *fp = fopen(f, "rb");
	if (fp == NULL)
	{
		printf("file can't be open");
		return 2;
	}
	fseek(fp, 0L, SEEK_END);

	int flen = ftell(fp);
    fseek(fp, 0, SEEK_SET);   //SEEK_SET为文件头
	char * buf = (char *)malloc(flen);
    fread(buf, flen, 1, fp);
    xtar_add_body(p, buf, flen);
    fclose(fp);
}

int xtar_dump_file(Xtar* p, const char* f){
    FILE *fp = fopen(f, "wb");
    if(fp == NULL)
    {
        printf("fopen %s fail!\n", f);
        return -1;
    }
    if (p->body_len){
        fwrite(p->body, sizeof(char), p->body_len, fp);
    }
    fclose(fp);
    return 0;
}

void xtar_free(Xtar* p){
    free(p->body);
    free(p->title);
}


void xtar_from_char(Xtar* p, const char* c, int len)
{
    char *c2 = (char*)c;
    int title_len = *((int*) c2);
    c2 += sizeof(int);
    xtar_add_title(p, c2, title_len);

    c2 += title_len;
    int body_len = *((int*) c2);
    c2 += sizeof(int);
    xtar_add_body(p, c2, body_len);
}

int xtar_get_len(Xtar* p){
    return p->title_len + p->body_len + sizeof(int)*2;
}

void xtar_to_char(const Xtar* p, char* c)
{
    char *c2 = c;
    memcpy(c2, &p->title_len, sizeof(int));
    c2 += sizeof(int);
    memcpy(c2, p->title, p->title_len);
    c2 += p->title_len;
    memcpy(c2, &p->body_len, sizeof(int));
    c2 += sizeof(int);
    memcpy(c2, p->body, p->body_len);
}