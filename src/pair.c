#include <tigcclib.h>         // Include All Header Files

#include "pair.h"
#include "memgc.h"
#include "wrappers.h"

OBJECT cons( OBJECT car, OBJECT cdr ){
	PAIR pair = mallocGC( sizeof( STATICPAIR ) );
	pair->id = 3;
	pair->print = printPair;
	
	pair->car = car;
	pair->cdr = cdr;
	return (OBJECT)pair;
}

void appendSmart( OBJECT* pList, OBJECT data ){
	if( isNull( *pList ) ){
		if( isList(data) )	*pList = data;
		else				*pList = cons(data, _NULL);
	}
	else if( isNull( cdr(*pList) ) ){
		if( isList(data) )	cdr(*pList) = data;
		else 				cdr(*pList) = cons( data, _NULL );
	}
	else appendSmart( &cdr(*pList), data );
}
void append( OBJECT* pList, OBJECT data ){
	if( isNull( *pList ) ){
		*pList = cons(data, _NULL);
	}
	else if( isNull( cdr(*pList) ) ){
		cdr(*pList) = cons( data, _NULL );
	}
	else append( &cdr(*pList), data );
}

OBJECT map( OBJECT(*proc)(OBJECT), OBJECT lst ){
	if( isNull(lst) ) return lst;
	return cons( proc(car(lst)), map(proc, cdr(lst)) );
}
OBJECT map2( OBJECT(*proc)(OBJECT,OBJECT), OBJECT lst1, OBJECT lst2 ){
	if( isNull(lst1) ) return lst1;
	return cons(proc(car(lst1), car(lst2)), map2(proc, cdr(lst1), cdr(lst2)));
}
OBJECT foldRight( OBJECT(*proc)(OBJECT, OBJECT), OBJECT init, OBJECT lst ){
	if( isNull(lst) ) return init;
	return proc( car(lst), foldRight( proc, init, cdr(lst) ));
}
//OBJECT 
int length( OBJECT lst ){
	if( isNull(lst) ) return 0;
	return 1 + length(cdr(lst));
}
OBJECT list( int n_args, ... ){
	va_list ap;
	va_start(ap, n_args);
	OBJECT obj;
	OBJECT lst = _NULL;
	int i;
	
	for( i=0; i<n_args; ++i ){
		obj = va_arg( ap, OBJECT );
		append( &lst, obj );
	}
	return lst;
}

int isList( OBJECT data ){
	if( isNull( data ) )		return 1;
	else if( isPair( data ) )	return isList(cdr(data));
	else						return 0;
}

int pairEqv( OBJECT obj1, OBJECT obj2 ){
	return eqv(car(obj1), car(obj2)) && eqv(cdr(obj1), cdr(obj2));
}

void helpPrintPair( OBJECT pair ){
	OBJECT obj1 = car(pair),
		   obj2 = cdr(pair);
	printf( "(" );
	obj1->print(obj1);
	printf( " . " );
	obj2->print(obj2);
	printf( ")" );
}

void helpPrintList( OBJECT pair ){
	OBJECT obj1, obj2;
	if( !isNull( pair ) ){
		obj1 = car(pair);
		obj2 = cdr(pair);
		obj1->print(obj1);
		if( !isNull(obj2) )	{
			printf( " " );
			helpPrintList(obj2);
		}
	}
}

void printPair( OBJECT pair ){
	if( isList( pair ) ){
		printf( "(" );
		helpPrintList(pair);
		printf( ")" );
	}
	else helpPrintPair(pair);
}

OBJECT* next( OBJECT* pPair ){
	*pPair = cdr(*pPair);
	return pPair;
}

OBJECT carP( OBJECT pair ){
	return ((PAIR)pair)->car;
}
OBJECT cdrP( OBJECT pair ){
	return ((PAIR)pair)->cdr;
}

OBJECT first( OBJECT pair ){
	return car(pair);
}
OBJECT second( OBJECT pair ){
	return car(cdr(pair));
}
OBJECT third( OBJECT pair ){
	return car(cdr(cdr(pair)));
}
OBJECT fourth( OBJECT pair ){
	return car(cdr(cdr(cdr(pair))));
}
