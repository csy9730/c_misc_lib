#ifndef __TEST_UTILS_H
#define __TEST_UTILS_H


#ifdef __cplusplus
extern "C" {
#endif

void _fileGen(const char* pfn);
void _fileGen2(const char* pfn);
int fileIsEqual(const char*filename, const char*filenam2);

#ifdef __cplusplus
}
#endif

#endif
