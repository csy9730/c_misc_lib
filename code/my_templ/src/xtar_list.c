#include "xtar_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


XtarList *make_xtarlist()
{
    return make_list();
}

int xtars_addfile(XtarList* l, const char* f){
    // Xtar *p = (Xtar *) malloc(sizeof(Xtar));

    Xtar *p = make_xtar();
    xtar_from_file(p, f);

    list_insert(l, p);
}

#define XTAR_MAGIC (0x20210302)

int xtars_dump(XtarList* l, const char* f)
{
    int cusum = 0, count=0, i=0, offset=0, wr=0;
    node *n = l->front;
    while(n){
        Xtar* p = n->val;
        cusum += xtar_get_len(p);
        n = n->next;
        count ++;
    }

    FILE *fp = fopen(f, "wb");
    if(fp == NULL)
    {
        printf("fopen %s fail!\n", f);
        return -1;
    }
    int magic = XTAR_MAGIC;
    fwrite(&magic, sizeof(int), 1, fp);
    fwrite(&count, sizeof(int), 1, fp);

    n = l->front;
    while(n){
        Xtar* p = n->val;

        printf("index=%d\n", i);
		wr = fwrite(&i, sizeof(int), 1, fp);

        // offset += xtar_get_len(p) + sizeof(int);
        // fwrite(&offset, sizeof(int), 1, fp);
		wr = fwrite(&p->title_len, sizeof(int), 1, fp);
		// printf("index=%d\n", wr, p->title_len);
		wr = fwrite(p->title, sizeof(char), p->title_len, fp);
		wr = fwrite(&p->body_len, sizeof(int), 1, fp);
		wr = fwrite(p->body, sizeof(char), p->body_len, fp);

        n = n->next;
        i++;
    }
    fclose(fp);
}


int xtars_load(XtarList* l, const char* f)
{
    FILE *fp = fopen(f, "rb");
    if(fp == NULL) {
        return -1;
    };
    fseek(fp, 0, SEEK_END);   //fp指向end,fseek(FILE *stream, long offset, int fromwhere);
    int model_len = ftell(fp);   //相对文件首偏移
    char * encrypted_model = (char*)malloc(model_len);
    fseek(fp, 0, SEEK_SET);   //SEEK_SET为文件头
    if(model_len != fread(encrypted_model, sizeof(char), model_len, fp))
    {
        printf("fread %s fail!\n", f);
        free(encrypted_model);
        return -1;
    }
    int ret = xtars_load_from_bytes(l, encrypted_model, model_len);

    fclose(fp);
    free(encrypted_model);
    return ret;
}


int xtars_load_from_bytes(XtarList* l, const char* buffer, int bLen)
{
    const char* p = buffer;
    int magic, len, i;
    magic = *(int*)p;
    p += sizeof(int);
    assert(magic == XTAR_MAGIC); 
    len = *(int*)p;
    p += sizeof(int);

    for (i=0;i<len;i++){
        int title_len, body_len, idx;
        Xtar *x = malloc(sizeof(Xtar));

        idx = *(int*)p;
        p += sizeof(int);

        title_len = *(int*)p;
        p += sizeof(int);
        xtar_add_title(x, p, title_len);
        p += title_len;

        body_len = *(int*)p;
        p += sizeof(int);
        xtar_add_body(x, p, body_len);
        p += body_len;

        list_insert(l, x);
    }
    return 0;
}

void xtars_printf(XtarList* l){
    int count=0;
    node *n = l->front;
    while(n){
        Xtar* p = n->val;
        printf("%d: %s, %d, %s\n", p->title_len, p->title, p->body_len, p->body);
        n = n->next;
        count ++;
    }
}


int xtars_find_by_title(XtarList* l, const char * title){
    int count=0;
    node *n = l->front;

    // char filename[150] = {0};
    
    while(n){
        Xtar* p = n->val;
        // strcpy(filename, p->title, p->title_len);
        if(strcmp(p->title, title)==0){
            return count;
        }
        n = n->next;
        count ++;
    }
    return -1;
}


void* xtars_get_by_index(XtarList* l, int index){
    int count=0;
    node *n = l->front;
    while(n){
        Xtar* p = n->val;
        if (count==index){
            return p;
        }        
        n = n->next;
        count++;
    }
}