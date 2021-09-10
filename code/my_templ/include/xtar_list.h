#ifndef XTAR_LIST_H
#define XTAR_LIST_H

#include "list.h"
#include "xtar.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef list XtarList;

XtarList *make_xtarlist();
int xtars_dump(XtarList* p, const char* f);
int xtars_load(XtarList* p, const char* f);
int xtars_addfile(XtarList* p, const char* f);
// int xtars_get_index_by_title(XtarList* p, const char* f);
void xtars_printf(XtarList* p);
int xtars_load_from_bytes(XtarList* l, const char* buffer, int bLen);


int xtars_find_by_title(XtarList* l, const char * title);
void* xtars_get_by_index(XtarList* l, int index);

#ifdef __cplusplus
}
#endif

#endif