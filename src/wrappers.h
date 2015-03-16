#ifndef _WRAPPERS_H_
#define _WRAPPERS_H_

#include "util.h"

OBJECT error(const char* str, int n_args, ... );
OBJECT eqv( OBJECT obj1, OBJECT obj2 );

OBJECT newNull();
#define _NULL newNull()
#define isNull(obj) (((OBJECT)obj)->id == 0)

OBJECT newVoid();
#define _VOID newVoid()
#define isVoid(obj)(((OBJECT)obj)->id == 1)

OBJECT newUnspecified();
#define _UNSPECIFIED newUnspecified()
#define isUnspecified( obj ) (((OBJECT)obj)->id == 7)

OBJECT newTrue();
#define _TRUE newTrue()
#define isTrue( obj ) (((OBJECT)obj)->id == 8)
OBJECT newFalse();
#define _FALSE newFalse()
#define isFalse( obj ) (((OBJECT)obj)->id == 9)

#define isBoolean( obj ) (isTrue(obj) || isFalse(obj))
#define newBoolean(bool) (bool? newTrue(): newFalse())

typedef struct STATICSTRING_TAG{
	ID id;
	void (*print)(void*);
	
	char* str;
} STATICSTRING;
typedef STATICSTRING* STRING;

OBJECT newString( const char* str );
#define isString( obj ) (((OBJECT)obj)->id == 2)
#define getStringVal( obj ) (((STRING)obj)->str)
#define stringEqv(obj1, obj2) strEqual(getStringVal(obj1), getStringVal(obj2))

typedef struct STATICINT_TAG{
	ID id;
	void (*print)(void*);
	
	int val;
} STATICINT;
typedef STATICINT* _INT;

OBJECT newInt( int val );
#define isInt( obj ) (((OBJECT)obj)->id == 4)
#define getIntVal( obj ) (((_INT)obj)->val)
#define intEqv(obj1, obj2) (getIntVal(obj1) == getIntVal(obj2))

typedef struct STATICFLOAT_TAG{
	ID id;
	void (*print)(void*);
	
	double val;
} STATICFLOAT;
typedef STATICFLOAT* FLOAT;

OBJECT newFloat( double val );
#define isFloat( obj ) (((OBJECT)obj)->id == 5)
#define getFloatVal( obj ) (((FLOAT)obj)->val)
#define floatEqv(obj1, obj2) (getFloatVal(obj1) == getFloatVal(obj2))

#define isNumber( obj ) (isInt(obj) || isFloat(obj))
#define getNumber( obj ) (isInt(obj)? getIntVal(obj): getFloatVal(obj))

typedef struct STATICSYMBOL_TAG{
	ID id;
	void (*print)(void*);
	
	int val;
} STATICSYMBOL;
typedef STATICSYMBOL* SYMBOL;

OBJECT newSymbol( const char *str );
OBJECT newSymbolId( int id );
#define isSymbol( obj ) (((OBJECT)obj)->id == 6)
#define getSymbolID( obj ) (((SYMBOL)obj)->val)
#define symbolEq( sym1, sym2 ) (getSymbolID(sym1)==getSymbolID(sym2))
char* getSymbolStr( OBJECT sym );
#define symbolEqv symbolEq

#endif //_WRAPPERS_H_
