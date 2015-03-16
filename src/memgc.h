#ifndef _MEMGC_H_
#define _MEMGC_H_

#include <stddef.h>

void* mallocGC( size_t size );
void* callocGC( size_t nmemb, size_t size );

void freeAllGC();

#endif //_MEMGC_H_
