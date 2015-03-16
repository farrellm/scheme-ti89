#ifndef _PAIR_H_
#define _PAIR_H_

#include <stdlib.h>
#include "util.h"

typedef struct STATICPAIR_TAG{
	ID id;
	void (*print)(OBJECT);
	
	OBJECT car;
	OBJECT cdr;
} STATICPAIR;
typedef STATICPAIR* PAIR;

#define isPair( data )(((OBJECT)(data))->id == 3)
int isList( OBJECT data );
int pairEqv( OBJECT obj1, OBJECT obj2 );

#define newList() _NULL

OBJECT cons( OBJECT car, OBJECT cdr );
#define car( pair ) (((PAIR)pair)->car)
#define cdr( pair ) (((PAIR)pair)->cdr)
inline OBJECT carP( OBJECT pair );
inline OBJECT cdrP( OBJECT pair );

void append( OBJECT *pList, OBJECT data );
void appendSmart( OBJECT* pList, OBJECT data );
OBJECT map( OBJECT(*proc)(OBJECT), OBJECT lst );
OBJECT map2( OBJECT(*proc)(OBJECT,OBJECT), OBJECT lst1, OBJECT lst2 );
OBJECT foldRight( OBJECT(*proc)(OBJECT, OBJECT), OBJECT init, OBJECT lst );
int length( OBJECT lst );

OBJECT list( int n_args, ... );

void printPair( OBJECT pair );

#define caar( pair ) car(car(pair))
#define caadr( pair ) car(car(cdr(pair)))
#define cadr( pair ) car(cdr(pair))
#define caddr( pair ) car(cdr(cdr(pair)))
#define cadddr( pair ) car(cdr(cdr(cdr(pair))))
#define cdadr( pair ) cdr(car(cdr(pair)))
#define cddr( pair ) cdr(cdr(pair))

inline OBJECT first( OBJECT pair );
inline OBJECT second( OBJECT pair );
inline OBJECT third( OBJECT pair );
inline OBJECT fourth( OBJECT pair );

#define setcar( pair, data ) (((PAIR)pair)->car = data)
#define setcdr( pair, data ) (((PAIR)pair)->cdr = data)

OBJECT* next( OBJECT* pPair );

#endif //_PAIR_H_
