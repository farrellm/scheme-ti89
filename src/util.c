#include <tigcclib.h>         // Include All Header Files

#include "util.h"
#include "pair.h"
#include "wrappers.h"
#include "memgc.h"

char sgetc( char** pStr ){
	char buf = **pStr;
	++(*pStr);
	return buf;
}

void newline(){
	printf( "\n" );
}

int isEOF( char c ){
	return c == EOF;
}
int isEOStr( char c ){
	return c == '\0';
}

char* copyString( const char* str ){
	char* newStr = callocGC( strlen(str)+1, sizeof(char) );
	strcpy( newStr, str );
	return newStr;
}

int strEqual( const char* str1, const char* str2 ){
	return strcmp( str1, str2 ) == 0;
}

void printCStrList( OBJECT pair ){
	printf( "[" );
	while( !isNull( pair ) ){
		printf( " %s", (char*)car(pair) );
		pair = cdr(pair);
	}
	printf( " ]" );
}
	
