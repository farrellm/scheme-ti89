#include <tigcclib.h>         // Include All Header Files

#include "wrappers.h"
#include "pair.h"
#include "syntax.h"

int isTaggedList( OBJECT exp, const char *tag ){
	return isPair(exp) && isSymbol(car(exp)) &&
		   strEqual( getSymbolStr(car(exp)), tag );
}

int isSelfEvaluating( OBJECT exp ){
	return isNumber(exp) || isString(exp) || isBoolean(exp);
}

/**********************************************/

int isVariable( OBJECT exp ){
	return isSymbol( exp );
}

/*********************************************/

int isDefinition( OBJECT exp ){
	return isTaggedList( exp, "define" );
}
OBJECT definitionVariable( OBJECT exp ){
	if( isSymbol( cadr(exp)))
		return cadr(exp);
	else return caadr(exp);
}
OBJECT definitionValue( OBJECT exp ){
	if( isSymbol( cadr(exp)))
		return caddr(exp);
	else return makeLambda( cdadr(exp), cddr(exp));
}

/*********************************************/

int isApplication( OBJECT exp ){
	return isPair(exp);
}

OBJECT operator( OBJECT app ){
	return car(app);
}

OBJECT operands( OBJECT app ){
	return cdr(app);
}

int noOperands( OBJECT args ){
	return isNull(args);
}

OBJECT firstOperand( OBJECT list ){
	return car(list);
}

OBJECT restOperands( OBJECT list ){
	return cdr(list);
}
