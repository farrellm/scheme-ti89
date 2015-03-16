#include <tigcclib.h>         // Include All Header Files

#include "memgc.h"

typedef struct GCENTRY_TAG{
	void* ptr;
	struct GCENTRY_TAG* next;
} GCENTRY;

GCENTRY* g_gcList = NULL;

void* mallocGC( size_t size ){
	GCENTRY *newEntry = malloc( sizeof( GCENTRY ) );
	if( newEntry ){
		newEntry->ptr = malloc( size );
		newEntry->next = g_gcList;
		g_gcList = newEntry;
	}
//	printf("{%x}", newEntry);
	return newEntry->ptr;
}

void* callocGC( size_t nmemb, size_t size ){
	GCENTRY *newEntry = malloc( sizeof( GCENTRY ) );
	newEntry->ptr = calloc( nmemb, size );
	newEntry->next = g_gcList;
	g_gcList = newEntry;
	
	return newEntry->ptr;
}

void gcHelper( GCENTRY* );

void freeAllGC(){
	gcHelper( g_gcList );
}

void gcHelper( GCENTRY* pEntry ){
	if( pEntry ){ // != NULL
		gcHelper( pEntry->next );
		free( pEntry->ptr );
		free( pEntry );
	}
}
