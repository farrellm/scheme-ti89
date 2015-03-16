#ifndef _TYPES_H_
#define _TYPES_H_

/* General */

int isEOF( char );
int isEOStr( char );

char sgetc( char ** pStr );

void newline();

char* copyString( const char* );
int strEqual( const char*, const char* );

typedef unsigned char ID;

typedef struct STATICOBJECT_TAG{
	ID id;
	void (*print)(struct STATICOBJECT_TAG*);
} STATICOBJECT;
typedef STATICOBJECT* OBJECT;

void printCStrList( OBJECT pair );

#endif //_TYPES_H_
