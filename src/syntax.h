#ifndef _SYNTAX_H_
#define _SYNTAX_H_

//#include "expr.h"
#include "util.h"

int isTaggedList( OBJECT, const char* );

int isSelfEvaluating( OBJECT );

#define isQuoted(exp) isTaggedList(exp, "quote")
#define textOfQuotation(exp) cadr(exp)

int isVariable( OBJECT );
#define isAssignment(exp) isTaggedList(exp, "set!")
#define assignmentVariable(exp) cadr(exp)
#define assignmentValue(exp) caddr(exp)
#define makeAssignment(var, expr) list(3, newSymbol("set!"), var, expr)

int isDefinition( OBJECT );
OBJECT definitionVariable( OBJECT );
OBJECT definitionValue( OBJECT );
#define makeDefine(var, expr) list(3, newSymbol("define"), var, expr);

#define isLambda(exp) isTaggedList(exp, "lambda")
#define lambdaParameters(exp) cadr(exp)
#define lambdaBody(exp) cddr(exp)
#define makeLambda(parms, body) cons(newSymbol("lambda"), cons(parms, body))

#define isIf(exp) isTaggedList( exp, "if" )
#define ifPredicate(exp) cadr(exp)
#define ifConsequent(exp) caddr(exp)
#define ifAlternative(exp) cadddr(exp)
#define makeIf(pred, conseq, alt)list(4, newSymbol("if"), pred, conseq, alt);

#define isCond(exp) isTaggedList(exp, "cond")
#define condClauses(exp) cdr(exp)
#define firstCondClause car
#define restCondClauses cdr
#define makeCond(seq) cons(newSymbol("cond"), seq)

#define isLet(exp) isTaggedList(exp, "let")
#define letBoundVariables(exp) map( first, second(exp) )
#define letValues(exp) map( second, second(exp) )
#define letBody(exp) cddr(exp)
#define makeLet(bindings, body) cons( newSymbol("let"), cons(bindings, body) )

#define isBegin(exp) isTaggedList(exp, "begin")
#define beginActions(beginExp) cdr(beginExp)
#define isLastExp(seq) isNull(cdr(seq))
#define firstExp(seq) car(seq)
#define restExps(seq) cdr(seq)
#define makeBegin(exp) cons(newSymbol("begin"), exp)

int isApplication( OBJECT );
OBJECT operator( OBJECT );
OBJECT operands( OBJECT );
int noOperands( OBJECT );
OBJECT firstOperand( OBJECT );
OBJECT restOperands( OBJECT );
#define makeApplication( rator, rands ) cons(rator, rands)

#endif //_SYNTAX_H_
