#include <tigcclib.h>         // Include All Header Files

#include "symbols.h"
#include "wrappers.h"
#include "memgc.h"
#include "util.h"

extern OBJECT g_symbolList;

OBJECT error(const char* str, int n_args, ... ){
	va_list ap;
	va_start(ap, n_args);
	OBJECT obj;
	int i;
	
	printf( "%s", str );
	
	for( i=0; i<n_args; ++i ){
		printf(" ");
		obj = va_arg( ap, OBJECT );
		obj->print(obj);
	}
	newline();
	return _NULL;
}

OBJECT eqv( OBJECT obj1, OBJECT obj2 ){
	if( obj1->id != obj2->id ) return newFalse();
	return newBoolean( (isString(obj1) && stringEqv(obj1, obj2))
					|| (isInt(obj1) && intEqv(obj1, obj2))
					|| (isFloat(obj1) && floatEqv(obj1, obj2))
					|| (isSymbol(obj1) && symbolEqv(obj1, obj2))
					|| (isPair(obj1) && pairEqv(obj1, obj2)) );
}

void printNull(OBJECT obj){
	printf( "()" );
}
OBJECT newNull(){
	static STATICOBJECT obj = { 0, printNull };
	return &obj;
}

void printVoid(OBJECT obj){}
OBJECT newVoid(){
	static STATICOBJECT obj = { 1, printVoid };
	return &obj;
}

void printString( STRING str ){
	printf( "\"%s\"", str->str );
}

OBJECT newString( const char* str ){
	STRING newStr = mallocGC( sizeof( STATICSTRING ) );
	newStr->id = 2;
	newStr->print = printString;
	newStr->str = copyString( str );
	return (OBJECT)newStr;
}

void printInt( _INT i ){
	printf( "%i", i->val );
}
OBJECT newInt( int val ){
	_INT newInt = mallocGC( sizeof( STATICINT ) );
	newInt->id = 4;
	newInt->print = printInt;
	newInt->val = val;
	return (OBJECT)newInt;
}

void printFloat( FLOAT f ){
	printf( "%f", f->val );
}
OBJECT newFloat( double val ){
	FLOAT newFloat = mallocGC( sizeof( STATICFLOAT ) );
	newFloat->id = 5;
	newFloat->print = printFloat;
	newFloat->val = val;
	return (OBJECT)newFloat;
}

void printSymbol( SYMBOL s ){
	printSymbolId( s->val, g_symbolList );
}
OBJECT newSymbol( const char *str ){
	SYMBOL newSym = mallocGC( sizeof( STATICSYMBOL ) );
	newSym->id = 6;
	newSym->print = printSymbol;
	newSym->val = findOrAddSymbol( &g_symbolList, str );
	return (OBJECT)newSym;
}
OBJECT newSymbolId( int id ){
	SYMBOL newSym = mallocGC( sizeof( STATICSYMBOL ) );
	newSym->id = 6;
	newSym->print = printSymbol;
	newSym->val = id;
	return (OBJECT)newSym;
}
char* getSymbolStr( OBJECT sym ){
	return getSymbolString( getSymbolID( sym ), g_symbolList );
}

void printUnspecified( OBJECT obj ){
	printf( "unspecified" );
}
OBJECT newUnspecified(){
	static STATICOBJECT obj = { 7, printUnspecified };
	return &obj;
}

void printTrue( OBJECT obj ){
	printf( "#t" );
}
OBJECT newTrue(){
	static STATICOBJECT obj = { 8, printTrue };
	return &obj;
}
void printFalse( OBJECT obj ){
	printf( "#f" );
}
OBJECT newFalse(){
	static STATICOBJECT obj = { 9, printFalse };
	return &obj;
}
