#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xtar_list.h"


int main(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc; i++)
        printf("Argument %d is %s\n", i, argv[i]);

	if( argc < 2)
	{
		printf("usage: ./zalunxtar input_file \n");
        printf("version 1.0\n");
		return -1;
	}

    XtarList *xt = make_xtarlist();
    xtars_load(xt, argv[1]);

    int count=0;
    node *n = xt->front;
    while(n){
        Xtar* p = n->val;

        printf("%d: %s, %d, %s\n", p->title_len, p->title, p->body_len, p->body);
		xtar_dump_file(p, p->title);

        n = n->next;
        count ++;
    }
}




