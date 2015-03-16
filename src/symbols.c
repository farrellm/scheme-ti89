#include <tigcclib.h>         // Include All Header Files

#include "symbols.h"
#include "wrappers.h"
#include "memgc.h"
#include "util.h"

typedef struct STATICSYMBOLENTRY_TAG{
	int id;
	char *name;
} STATICSYMBOLENTRY;
typedef STATICSYMBOLENTRY* SYMBOLENTRY;

#define getSymbolEntryId(entry) (((SYMBOLENTRY)(entry))->id)
#define getSymbolEntryName(entry) (((SYMBOLENTRY)(entry))->name)
	
SYMBOLENTRY newSymbolEntry( const char* name ){
	static int id = 0;
	SYMBOLENTRY pEntry = mallocGC( sizeof( STATICSYMBOLENTRY ) );
		
	pEntry->name = copyString( name );
	pEntry->id = id++;
	
	return pEntry;
}

int findOrAddSymbol( OBJECT* pList, const char* name ){
	if( isNull( *pList ) ){
		*pList = cons( (OBJECT)newSymbolEntry( name ), _NULL );
		return getSymbolEntryId(car(*pList));
	}
	else if( strEqual( ((SYMBOLENTRY)car(*pList))->name, name ) )
		return getSymbolEntryId(car(*pList));
	else
		return findOrAddSymbol( &cdr(*pList), name );
}

char* getSymbolString( int id, OBJECT symList ){
	if(isNull(symList)) return NULL;
	else if( id == getSymbolEntryId(car(symList)) )
		return getSymbolEntryName(car(symList));
	else return getSymbolString( id, cdr(symList) );
}

void printSymbolEntry( SYMBOLENTRY entry ){
	printf( "%03i %s\n", getSymbolEntryId(entry), getSymbolEntryName(entry) );
}
void printSymbolList( OBJECT list ){
	if( !isNull( list )){
		printSymbolEntry( (SYMBOLENTRY)car( list ));
		printSymbolList( cdr( list ) );
	}
}

void printSymbolId( int id, OBJECT symList ){
	if( isNull( symList ) ) 
		printf( "\n*** Unknown Symbol ID (printSymbolId) ***\n" );
	else if( getSymbolEntryId( car(symList) ) == id )
		printf( "%s", getSymbolEntryName(car(symList)) );
	else
		printSymbolId( id, cdr(symList) );
}
