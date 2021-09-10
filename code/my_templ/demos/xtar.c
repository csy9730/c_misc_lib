#include <stdio.h>
#include <stdlib.h>
#include "xtar_list.h"


int main(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc; i++)
        printf("Argument %d is %s\n", i, argv[i]);

	if( argc < 3)
	{
		printf("usage: ./zalxtar output_file <input file> \n");
        printf("version 1.0\n");
		return -1;
	}

    XtarList *xt = make_xtarlist();
    for (int i=2;i<argc;i++){
        xtars_addfile(xt, argv[i]);
    }
    xtars_dump(xt, argv[1]);

	return 0;
}
