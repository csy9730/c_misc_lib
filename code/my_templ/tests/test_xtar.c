#include <stdio.h>
#include "xtar_list.h"
#include "test_main.h"
#include "common/zal_tests.h"
#include "utils/test_utils.h"

int test_xtar_list(void){
    XtarList *xt = make_xtarlist();

    char *filename = "___built.sh";
    char *filename2 = "___xtar.bin";
    char *filename3 = "___buil2.sh";

    _fileGen2(filename);

    xtars_addfile(xt, filename);
    xtars_dump(xt, filename2);

    XtarList *xt2 = make_xtarlist();
    xtars_load(xt2, filename2);
    printf("len=%d\n", xt2->size);
    xtars_printf(xt2);

    int fd = xtars_find_by_title(xt2, filename);
    int f = 0;
    ZAL_TEST_TRUE(fd == 0, f);
    printf("find %d\n", fd);

    Xtar* px = (Xtar*) xtars_get_by_index(xt2, fd);
    printf("len=%d, %d, %s\n", px->title_len, px->body_len, px->title);

    ZAL_TEST_TRUE(px->title_len == 11, f);
    ZAL_TEST_TRUE(px->body_len == 126, f);

    xtar_dump_file(px, filename3);
    ZAL_TEST_TRUE(!fileIsEqual(filename, filename3), f);
    // ZAL_TEST_DISP2(f);
    ZAL_ASSERT(f==0);
    return f;
}