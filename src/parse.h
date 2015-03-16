#ifndef _PARSE_H_
#define _PARSE_H_

#include "pair.h"

OBJECT file2strings( FILE* file );
OBJECT stream2strings( void* stream, 
				     char (*extract)(void*),
					 int (*isFinished)(char) );
OBJECT strings2tokens( OBJECT strList, OBJECT* pSymList );

#endif //_PARSE_H_
