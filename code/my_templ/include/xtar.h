#ifndef XTAR_H
#define XTAR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Xtar{
    int title_len;
    int body_len;
    char* title;
    char* body;
}Xtar;

Xtar *make_xtar();
void xtar_add_title(Xtar* p, const char* f, int len);
void xtar_add_body(Xtar* p, const char* f, int len);
int xtar_from_file(Xtar* p, const char* f);
int xtar_dump_file(Xtar* p, const char* f);
void xtar_free(Xtar* p);

int xtar_get_len(Xtar* p);
void xtar_to_char(const Xtar* p, char* c);
void xtar_from_char(Xtar* p, const char* c, int len);

#ifdef __cplusplus
}
#endif

#endif