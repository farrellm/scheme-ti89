#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_
#include "pair.h"

int findOrAddSymbol( OBJECT*, const char* );

char* getSymbolString( int id, OBJECT symList );
void printSymbolId( int id, OBJECT symList );
void printSymbolList( OBJECT );

#endif //_SYMBOLS_H_
